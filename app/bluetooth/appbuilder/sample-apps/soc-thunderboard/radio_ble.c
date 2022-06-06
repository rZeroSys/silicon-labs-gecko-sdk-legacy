/***************************************************************************//**
 * @file
 * @brief radio_ble.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "hal-config-app-common.h"

#include "ble-configuration.h"

#include "em_core.h"
#include "em_system.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_prs.h"
#include "em_rtcc.h"

#include "thunderboard/util.h"
#include "thunderboard/si7021.h"
#include "thunderboard/si1133.h"
#include "thunderboard/board.h"
#include "thunderboard/imu/imu.h"
#if !defined(BRD4184A)
  #include "thunderboard/bap.h"
  #include "thunderboard/ccs811.h"
  #include "app_sound.h"
#endif

#include "main.h"

#include "aio.h"
#include "imus.h"

/* BG stack headers */
/*#include "bg_types.h"*/
#include "native_gecko.h"
#include "gatt_db.h"

/* application specific files */
#include "app.h"
#include "app_supply.h"
#include "app_ble_adv.h"
#include "radio.h"
#include "radio_ble.h"

#include "pti.h"

#if !defined(BRD4160A)
  #include "app_hall.h"
#endif

/* Each iteration is 100 ms  */
#define APP_ADV_SLEEP_TIMEOUT_ITERATIONS           300

#define APP_STATE_UNKNOWN     0
#define APP_STATE_ADVERTISING 1
#define APP_STATE_CONNECTED   2

#ifndef MAX_ADVERTISERS
#define MAX_ADVERTISERS 1
#endif

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 4
#endif

uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

/* Bluetooth stack configuration parameters (see "UG136: Silicon Labs Bluetooth C Application Developer's Guide" for details on each parameter) */
static gecko_configuration_t config = {
  .config_flags = 0,                                   /* Check flag options from UG136 */
  .sleep.flags = 0,                                    /* Sleep is disabled */
  .bluetooth.max_connections = MAX_CONNECTIONS,        /* Maximum number of simultaneous connections */
  .bluetooth.max_advertisers = MAX_ADVERTISERS,        /* Maximum number of advertisement sets */
  .bluetooth.heap = bluetooth_stack_heap,              /* Bluetooth stack memory for connection management */
  .bluetooth.heap_size = sizeof(bluetooth_stack_heap), /* Bluetooth stack memory for connection management */
  .bluetooth.sleep_clock_accuracy = 100,               /* Accuracy of the Low Frequency Crystal Oscillator in ppm. *
                                                       * Do not modify if you are using a module                  */
  .gattdb = &bg_gattdb_data,                           /* Pointer to GATT database */
  .ota.flags = 0,                                      /* Check flag options from UG136 */
  .ota.device_name_len = 3,                            /* Length of the device name in OTA DFU mode */
  .ota.device_name_ptr = "OTA",                        /* Device name in OTA DFU mode */
  .ota.antenna_defined = APP_RF_CONFIG_ANTENNA,
  .ota.antenna = APP_RF_ANTENNA,
  .pa.config_enable = 1,                               /* Set this to be a valid PA config */
#if defined(FEATURE_PA_INPUT_FROM_VBAT)
  .pa.input = GECKO_RADIO_PA_INPUT_VBAT,               /* Configure PA input to VBAT */
#else
  .pa.input = GECKO_RADIO_PA_INPUT_DCDC,               /* Configure PA input to DCDC */
#endif // defined(FEATURE_PA_INPUT_FROM_VBAT)
  .rf.flags = APP_RF_CONFIG_ANTENNA,                 /* Enable antenna configuration. */
  .rf.antenna = APP_RF_ANTENNA,                      /* Select antenna path! */
};

#if !defined(BRD4184A)
uint16_t RADIO_eco2 = 0;
uint16_t RADIO_tvoc = 0;
float    RADIO_pressure = 0;
#endif
uint32_t RADIO_rhData = 50000;
int32_t  RADIO_tempData = 25000;
uint8_t  RADIO_uvIndex = 0;
uint32_t RADIO_ambLight = 0;

static void advertisingIteration(uint32_t loopCount);
static void connectionActiveIteration(uint32_t loopCount);

static int blinkCount;

void advBlink(void);

void RADIO_bleStackInit(void)
{
  blinkCount = 0;

#if (HAL_PTI_ENABLE == 1) || defined(FEATURE_PTI_SUPPORT)
  configEnablePti();
#endif // HAL_PTI_ENABLE

  /* Put the SPI flash into Deep Power Down mode for those radio boards where it is available */
  BOARD_flashDeepPowerDown();

  /* Perform initialisation of the stack. */
  gecko_init(&config);

  return;
}

void RADIO_bleStackLoopIteration(void)
{
  static uint32_t loopCount = 0;
  static uint8_t appState = APP_STATE_UNKNOWN;
  bool imuIntIsActive = false;

  ++loopCount;

  if ( IMU_isDataReadyFlag() ) {
    IMU_clearDataReadyFlag();
    imuIntIsActive = true;
  }

  if ( appBleAdvIsActive() ) {
    if (appState != APP_STATE_ADVERTISING ) {
      if ( SUPPLY_isLowPower() ) {
        MAIN_deInitSensors();
      }
      appState = APP_STATE_ADVERTISING;
    }

    advertisingIteration(loopCount);
  } else {
    if ( appState != APP_STATE_CONNECTED ) {
      if ( SUPPLY_isLowPower() ) {
        MAIN_initSensors();
      }
      appState = APP_STATE_CONNECTED;
      BOARD_ledSet(0);
    }
    connectionActiveIteration(loopCount);
  }

  RADIO_readImuData(imuIntIsActive);
}

void advertisingIteration(uint32_t loopCount)
{
  uint32_t sleepTimeout;
  static uint32_t previousAdvLC = 0;
  static uint32_t advStartedLC = 0;

  if ( previousAdvLC + 1 != loopCount ) {
    advStartedLC = loopCount;
  }
  previousAdvLC = loopCount;

  sleepTimeout = APP_ADV_SLEEP_TIMEOUT_ITERATIONS;

  advBlink();

#ifndef DEBUG
  if ( (loopCount - advStartedLC) > sleepTimeout ) {
    /* printf("\r\nSleep! %u %u", loopCount, advStartedLC); */
    if ( !SUPPLY_isLowPower() ) {
      MAIN_deInitSensors();
    }
    BOARD_imuClearIRQ();
#if !defined(BRD4184A)
    BOARD_gasSensorClearIRQ();
#endif
    BOARD_alsClearIRQ();
    BOARD_ledSet(0x00);
    UTIL_shutdown();
  }
#endif

  return;
}

#define RADIO_BLE_ADV_ON_COUNT  (1)
#define RADIO_BLE_ADV_OFF_COUNT (10)
void advBlink(void)
{
  int onCount = RADIO_BLE_ADV_ON_COUNT;
  int offCount = RADIO_BLE_ADV_OFF_COUNT;

  if ( blinkCount == onCount ) {
    BOARD_ledSet(0x00);
  } else if ( blinkCount >= offCount || blinkCount == 0 ) {
    BOARD_ledSet(0x01);
    blinkCount = 0;
  }
  blinkCount++;

  return;
}

void connectionActiveIteration(uint32_t loopCount)
{
  static bool expectAlsData = false;
  static uint8_t buttonState = 0;
  uint8_t irqStatus = 0;
  uint8_t state;
  float   lux = 0;
  float   uv = 0;

  blinkCount = 0;

  /* Check if the button state has changed */
  state = BOARD_pushButtonGetState();
  if ( state != buttonState ) {
    buttonState = state;
    aioDigitalInUpdate();
  }

  /* RH / T sensor read */
  if ( (loopCount % 30) == 0 ) {
    /* Measure the environmental temp and RH */
    /* If there is an error during the measurement use 25C and 50% RH */
    if ( SI7021_measure(&RADIO_rhData, &RADIO_tempData) != SI7021_OK ) {
      RADIO_tempData = 25000;
      RADIO_rhData = 50000;
    }

#if !defined(BRD4184A)
    if ( BAP_getPressure(&RADIO_pressure) != BAP_OK) {
      RADIO_pressure = 0;
    }

    /* Perform CCS811 measurement if not gated by supply */
    if ( SUPPLY_isLowPower() == false ) {
      if ( CCS811_isDataAvailable() ) {
        CCS811_getMeasurement(&RADIO_eco2, &RADIO_tvoc);
        CCS811_setEnvData(RADIO_tempData, RADIO_rhData);
      }
    }

    SOUND_Task();
#endif

    /* Start an ALS measurement */
    SI1133_measurementForce();
    expectAlsData = true;

    printf("\r\n.");
  }

  if ( expectAlsData ) {
    /* Check if the conversion finished on all channels */
    SI1133_getIrqStatus(&irqStatus);
    if (irqStatus == 0x0F) {
      expectAlsData = false;
      SI1133_getMeasurement(&lux, &uv);
      RADIO_ambLight = (uint32_t)(lux * 100);
      RADIO_uvIndex = (uint8_t)uv;
    }
  }

#if !defined(BRD4160A)
  HALL_task();
#endif
  return;
}

void RADIO_readImuData(bool imuIntIsActive)
{
  if ( IMU_isDataReadyFlag() ) {
    IMU_clearDataReadyFlag();
    imuIntIsActive = true;
  }

  if ( imuIsAccelerationNotification() || imuIsOrientationNotification() ) {
    if ( imuIntIsActive ) {
      if ( IMU_isDataReady() ) {
        IMU_update();
      }
    }
  }
}
