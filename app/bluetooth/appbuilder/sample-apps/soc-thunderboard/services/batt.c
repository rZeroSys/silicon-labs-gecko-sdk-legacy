/***************************************************************************//**
 * @file
 * @brief Battery Service
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

/* standard library headers */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* BG stack headers */
#include "bg_types.h"
#include "gatt_db.h"
#include "native_gecko.h"
#include "infrastructure.h"

/* plugin headers */
#include "app_timer.h"
#include "connection.h"

/* Supply voltage measurement */
#include "app_supply.h"

/* Own header*/
#include "batt.h"

/***********************************************************************************************//**
 * @addtogroup Features
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup batt
 * @{
 **************************************************************************************************/

/***************************************************************************************************
 * Local Macros and Definitions
 **************************************************************************************************/

/** Temperature measurement period in ms. */
#define BATT_IND_TIMEOUT                10000

/** Indicates currently there is no active connection using this service. */
#define BATT_NO_CONNECTION                   0xFF

/***************************************************************************************************
 * Local Type Definitions
 **************************************************************************************************/

typedef struct {
  float         voltage;
  uint8_t       capacity;
} VoltageCapacityPair;

/*******************************************************************************
 * Local Variables
 ******************************************************************************/

static VoltageCapacityPair battCR2032Model[] =
{ { 3.0, 100 }, { 2.9, 80 }, { 2.8, 60 }, { 2.7, 40 }, { 2.6, 30 },
  { 2.5, 20 }, { 2.4, 10 }, { 2.0, 0 } };

static uint8_t battBatteryLevel; /* Battery Level */

/***************************************************************************************************
 * Static Function Declarations
 **************************************************************************************************/
static uint8_t appHwReadBatteryLevel(void);

static uint8_t calculateLevel(float voltage, VoltageCapacityPair *model, uint8_t modelEntryCount)
{
  uint8_t res = 0;

  if (voltage >= model[0].voltage) {
    /* Return with max capacity if voltage is greater than the max voltage in the model */
    res = model[0].capacity;
  } else if (voltage <= model[modelEntryCount - 1].voltage) {
    /* Return with min capacity if voltage is smaller than the min voltage in the model */
    res = model[modelEntryCount - 1].capacity;
  } else {
    uint8_t i;
    /* Otherwise find the 2 points in the model where the voltage level fits in between,
       and do linear interpolation to get the estimated capacity value */
    for (i = 0; i < (modelEntryCount - 1); i++) {
      if ((voltage < model[i].voltage) && (voltage >= model[i + 1].voltage)) {
        res = (uint8_t)((voltage - model[i + 1].voltage)
                        * (model[i].capacity - model[i + 1].capacity)
                        / (model[i].voltage - model[i + 1].voltage));
        res += model[i + 1].capacity;
        break;
      }
    }
  }

  return res;
}

/***************************************************************************************************
 * Public Variable Definitions
 **************************************************************************************************/

/***************************************************************************************************
 * Public Function Definitions
 **************************************************************************************************/
void battInit(void)
{
  struct gecko_msg_hardware_set_soft_timer_rsp_t* ghsstrsp = NULL;
  ghsstrsp = gecko_cmd_hardware_set_soft_timer(TIMER_STOP, BATT_SERVICE_TIMER, false);
  APP_ASSERT_DBG(!ghsstrsp->result, ghsstrsp->result);
}

void battCharStatusChange(uint8_t connection, uint16_t clientConfig)
{
  struct gecko_msg_hardware_set_soft_timer_rsp_t* ghsstrsp = NULL;
  /* if the new value of CCC is not 0 (either indication or notification enabled)
   *  start battery level measurement */
  if (clientConfig) {
    battMeasure(); /* make an initial measurement */
    ghsstrsp = gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(BATT_IND_TIMEOUT), BATT_SERVICE_TIMER, false);
    APP_ASSERT_DBG(!ghsstrsp->result, ghsstrsp->result);
  } else {
    ghsstrsp = gecko_cmd_hardware_set_soft_timer(TIMER_STOP, BATT_SERVICE_TIMER, false);
    APP_ASSERT_DBG(!ghsstrsp->result, ghsstrsp->result);
  }
}

static uint8_t appHwReadBatteryLevel(void)
{
  float voltage = SUPPLY_measureVoltage(1);
  uint8_t level = calculateLevel(voltage, battCR2032Model, sizeof(battCR2032Model) / sizeof(VoltageCapacityPair));

  return level;
}

void battMeasure(void)
{
  struct gecko_msg_gatt_server_send_characteristic_notification_rsp_t* gsscnrsp = NULL;
  /* Update battery level based on battery level sensor */
  battBatteryLevel = appHwReadBatteryLevel();

  /* Send notification */
  gsscnrsp = gecko_cmd_gatt_server_send_characteristic_notification(
    conGetConnectionId(), gattdb_batt_measurement, sizeof(battBatteryLevel), &battBatteryLevel);
  APP_ASSERT_DBG(!gsscnrsp->result, gsscnrsp->result);
}

void battRead(void)
{
  struct gecko_msg_gatt_server_send_user_read_response_rsp_t* gssurrrsp = NULL;
  /* Update battery level based on battery level sensor */
  battBatteryLevel = appHwReadBatteryLevel();
  printf("Battery level = %d\r\n", battBatteryLevel);
  /* Send response to read request */
  gssurrrsp = gecko_cmd_gatt_server_send_user_read_response(conGetConnectionId(), gattdb_batt_measurement, 0,
                                                            sizeof(battBatteryLevel), &battBatteryLevel);
  APP_ASSERT_DBG(!gssurrrsp->result, gssurrrsp->result);
}

/** @} (end addtogroup batt) */
/** @} (end addtogroup Features) */
