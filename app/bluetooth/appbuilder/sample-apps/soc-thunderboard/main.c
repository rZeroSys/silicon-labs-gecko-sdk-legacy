/***************************************************************************//**
 * @file
 * @brief main.c
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
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "appl_ver.h"

#include "retargetserial.h"

#include "ble-configuration.h"

#include "thunderboard/util.h"
#include "thunderboard/board.h"
#include "thunderboard/si7021.h"
#include "thunderboard/si1133.h"
#if !defined(BRD4184A)
#include "thunderboard/bap.h"
#include "thunderboard/ccs811.h"
#include "app_sound.h"
#endif
#if !defined(BRD4160A)
  #include "app_hall.h"
#endif

#include "app.h"
#include "radio_ble.h"
#include "app_supply.h"
#include "init_mcu.h"

static void     init(void);
static bool sensorInitState = false;

int main(void)
{
  /**************************************************************************/
  /* Device errata init                                                     */
  /**************************************************************************/
  initMcu();

  /**************************************************************************/
  /* Board init                                                             */
  /**************************************************************************/
  init();

  printf("\r\n\r\n#### Thunderboard BLE application - %d.%d.%d build %d ####\r\n",
         APP_VERSION_MAJOR,
         APP_VERSION_MINOR,
         APP_VERSION_PATCH,
         APP_VERSION_BUILD
         );

  /**************************************************************************/
  /* Application loop                                                       */
  /**************************************************************************/
  while (1) {
    struct gecko_cmd_packet* evt;
    /* Check for stack event. */
    evt = gecko_wait_event();
    /* Run application and event handler. */
    appHandleEvents(evt);
  }
}

void MAIN_initSensors()
{
  if (true == sensorInitState) {
    // nothing to do
    return;
  }
#if !defined(BRD4184A)
  uint32_t status;
  uint8_t bapDeviceId;

  BAP_init(&bapDeviceId);
  printf("Pressure sensor: %s detected\r\n",
         bapDeviceId == BAP_DEVICE_ID_BMP280 ? "BMP280" : "BMP180");
#endif
  SI7021_init();
  SI1133_init();

#if !defined(BRD4160A)
  HALL_sensorInit();
#endif
#if !defined(BRD4184A)
  if ( SUPPLY_isLowPower() == false ) {
    CCS811_init();
    status = CCS811_startApplication();
    if ( status == CCS811_OK ) {
      status = CCS811_setMeasureMode(CCS811_MEASURE_MODE_DRIVE_MODE_10SEC);
    }
    printf("CCS811 init status: %x\r\n", (unsigned int)status);
  }

  BOARD_rgbledSetRawColor(0, 0, 0);
  SOUND_Init();
#endif
  sensorInitState = true;
  return;
}

void MAIN_deInitSensors()
{
  if (false == sensorInitState) {
    // nothing to do
    return;
  }
  sensorInitState = false;
  SI7021_deInit();
#if !defined(BRD4160A)
  HALL_sensorDeinit();
#endif
  SI1133_deInit();
  BOARD_envSensEnable(false);
#if !defined(BRD4184A)
  BAP_deInit();
  if ( SUPPLY_isLowPower() == false ) {
    CCS811_deInit();
  }

  BOARD_ledSet(0);
  BOARD_rgbledSetRawColor(0, 0, 0);
  BOARD_rgbledEnable(false, 0xFF);
  SOUND_DeInit();
#endif
  return;
}

void init(void)
{
  uint8_t  supplyType;
  float    supplyVoltage;
  float    supplyIR;
#if defined(BRD4160A)
  uint8_t  major, minor, patch, hwRev;
  uint32_t id;
#endif
  /**************************************************************************/
  /* Module init                                                            */
  /**************************************************************************/
  UTIL_init();
  BOARD_init();
  RETARGET_SerialInit();

#if defined(BRD4160A)
  id = BOARD_picGetDeviceId();
  BOARD_picGetFwRevision(&major, &minor, &patch);
  hwRev = BOARD_picGetHwRevision();

  printf("\r\n");
  printf("PIC device id    : %08Xh '%c%c%c%c'\r\n", (unsigned int)id,
         (int)id, (int)(id >> 8), (int)(id >> 16), (int)(id >> 24));
  printf("PIC firmware rev : %dv%dp%d\r\n", major, minor, patch);
  printf("PIC hardware rev : %c%.2d\r\n", 'A' + (hwRev >> 4), (hwRev & 0xf));
#endif

  SUPPLY_probe();
  SUPPLY_getCharacteristics(&supplyType, &supplyVoltage, &supplyIR);

  printf("\r\n");
  printf("Supply voltage : %.3f\r\n", supplyVoltage);
  printf("Supply IR      : %.3f\r\n", supplyIR);
  printf("Supply type    : ");
  if ( supplyType == SUPPLY_TYPE_USB ) {
    printf("USB\r\n");
  } else if ( supplyType == SUPPLY_TYPE_AA ) {
    printf("Dual AA batteries\r\n");
  } else if ( supplyType == SUPPLY_TYPE_AAA ) {
    printf("Dual AAA batteries\r\n");
  } else if ( supplyType == SUPPLY_TYPE_CR2032 ) {
    printf("CR2032\r\n");
  } else {
    printf("Unknown\r\n");
  }

  /**************************************************************************/
  /* Initialize stack                                                       */
  /**************************************************************************/
  RADIO_bleStackInit();

  /* In low power mode, sensors are enabled and disabled when entering/leaving connected mode */
  if ( !SUPPLY_isLowPower() ) {
    MAIN_initSensors();
  }

  return;
}
