/***************************************************************************//**
 * @file
 * @brief Silicon Labs Empty Example Project
 * This example demonstrates the bare minimum needed for a Blue Gecko C application
 * that allows Over-the-Air Device Firmware Upgrading (OTA DFU). The application
 * starts advertising after boot and restarts advertising after a connection is closed.
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

/* Board headers */
#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"
#include "ble-configuration.h"
#include "board_features.h"

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"

/* Libraries containing default Gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
#include "em_usart.h"

/* Device initialization header */
#include "hal-config.h"

#ifdef FEATURE_BOARD_DETECTED
#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif
#endif /* FEATURE_BOARD_DETECTED */

#include "dtm_timer.h"
#include "dtm_usart.h"
#include "dtm.h"

#if defined(CRYOTIMER_PRESENT)
#include "em_cryotimer.h"
#elif defined(BURTC_PRESENT)
#include "em_burtc.h"
#endif

/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app
 * @{
 **************************************************************************************************/

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 4
#endif
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

// Gecko configuration parameters (see gecko_configuration.h)
static const gecko_configuration_t config = {
  .config_flags = 0,
  .bluetooth.max_connections = MAX_CONNECTIONS,
  .bluetooth.heap = bluetooth_stack_heap,
  .bluetooth.heap_size = sizeof(bluetooth_stack_heap),
#if defined(FEATURE_LFXO)
  .bluetooth.sleep_clock_accuracy = 100, // ppm
#elif defined(PLFRCO_PRESENT)
  .bluetooth.sleep_clock_accuracy = 500, // ppm
#endif
  .gattdb = &bg_gattdb_data,
  .ota.flags = 0,
  .ota.device_name_len = 3,
  .ota.device_name_ptr = "OTA",
  .ota.antenna_defined = APP_RF_CONFIG_ANTENNA,
  .ota.antenna = APP_RF_ANTENNA,
  .pa.config_enable = 1, // Set this to be a valid PA config
#if defined(FEATURE_PA_INPUT_FROM_VBAT)
  .pa.input = GECKO_RADIO_PA_INPUT_VBAT, // Configure PA input to VBAT
#else
  .pa.input = GECKO_RADIO_PA_INPUT_DCDC,
#endif // defined(FEATURE_PA_INPUT_FROM_VBAT)
  .rf.flags = APP_RF_CONFIG_ANTENNA,                 /* Enable antenna configuration. */
  .rf.antenna = APP_RF_ANTENNA,                      /* Select antenna path! */
};

enum signal{
  signal_testmode_command_ready = 1,
};

#if defined(FEATURE_EXP_HEADER_USART3)
void USART3_RX_IRQHandler(void)
{
  testmode_process_command_byte(USART_Rx(USART3));
}

void USART3_Tx(uint8_t data)
{
  USART_Tx(USART3, data);
}

static const struct testmode_config testmode_config = {
  .write_response_byte = USART3_Tx,
  .get_ticks = DTM_TIMER_GET_TICKS,
  .ticks_per_second = 32768,
  .command_ready_signal = signal_testmode_command_ready,
};

#elif defined(FEATURE_EXP_HEADER_USART1)
void USART1_RX_IRQHandler(void)
{
  testmode_process_command_byte(USART_Rx(USART1));
}

void USART1_Tx(uint8_t data)
{
  USART_Tx(USART1, data);
}

static const struct testmode_config testmode_config = {
  .write_response_byte = USART1_Tx,
  .get_ticks = DTM_TIMER_GET_TICKS,
  .ticks_per_second = 32768,
  .command_ready_signal = signal_testmode_command_ready,
};

#else
void USART0_RX_IRQHandler(void)
{
  testmode_process_command_byte(USART_Rx(USART0));
}

void USART0_Tx(uint8_t data)
{
  USART_Tx(USART0, data);
}

static const struct testmode_config testmode_config = {
  .write_response_byte = USART0_Tx,
  .get_ticks = DTM_TIMER_GET_TICKS,
  .ticks_per_second = 32768,
  .command_ready_signal = signal_testmode_command_ready,
};

#endif // FEATURE_EXP_HEADER_USART3

static void dtmTimer_Init(void)
{
#if defined(CRYOTIMER_PRESENT)
  CRYOTIMER_Init_TypeDef init = CRYOTIMER_INIT_DEFAULT;
  init.osc = cryotimerOscLFXO;
  init.presc = cryotimerPresc_1;
  init.period = cryotimerPeriod_4096m;
  CRYOTIMER_Init(&init);
#elif defined(BURTC_PRESENT)
  BURTC_Init_TypeDef burtcInit = BURTC_INIT_DEFAULT;
  BURTC_Init(&burtcInit);
#endif
}

/**
 * @brief  Main function
 */
int main(void)
{
  // Initialize device
  initMcu();
  // Initialize board
  initBoard();
  // Initialize application
  initApp();
  initVcomEnable();
  dtmUsart_Init();

  // Initialize stack
  gecko_init(&config);

#if defined(FEATURE_EXP_HEADER_USART3)
  USART_IntEnable(USART3, USART_IF_RXDATAV);
  NVIC_EnableIRQ(USART3_RX_IRQn);
#elif defined(FEATURE_EXP_HEADER_USART1)
  USART_IntEnable(USART1, USART_IF_RXDATAV);
  NVIC_EnableIRQ(USART1_RX_IRQn);
#else
  USART_IntEnable(USART0, USART_IF_RXDATAV);
  NVIC_EnableIRQ(USART0_RX_IRQn);
#endif // FEATURE_EXP_HEADER_USART3

  dtmTimer_Init();
  testmode_init(&testmode_config);

  while (1) {
    // Event pointer for handling events
    struct gecko_cmd_packet* evt;

    // Check for stack event.
    evt = gecko_wait_event();

    testmode_handle_gecko_event(evt);
  }
}

/** @} (end addtogroup app) */
/** @} (end addtogroup Application) */
