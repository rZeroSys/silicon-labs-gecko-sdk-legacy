/***************************************************************************//**
 * @file
 * @brief Hall sensor application code
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "em_core.h"
#include "bspconfig.h"
#include "thunderboard/hall.h"
#include "bg_types.h"
#include "hallservice.h"

#include "app_hall.h"

#define HALL_THRESHOLD    3.0f
#define HALL_HYSTERESIS   0.5f

static float    sensorMagneticField = 0;
static volatile bool     sensorStateChanged = true;
static volatile uint8_t  sensorState = HALLS_STATE_OPEN;

#if defined(BOARD_HALL_OUTPUT_PIN)
static void HALL_stateCallback(bool pinHigh)
{
  sensorStateChanged = true;

  if ( pinHigh ) {
    sensorState = HALLS_STATE_CLOSED;
  } else {
    sensorState = HALLS_STATE_OPEN;
  }
}
#else
static void HALL_swFilter(void)
{
  float magFieldActual = fabsf(sensorMagneticField);
  float tamperLevel = HALL_getTamperLevel();

  if (((magFieldActual < (HALL_THRESHOLD - HALL_HYSTERESIS))
       || (magFieldActual > tamperLevel))
      && (sensorState == HALLS_STATE_CLOSED)) {
    sensorStateChanged = true;
    sensorState = HALLS_STATE_OPEN;
  } else if ((magFieldActual > (HALL_THRESHOLD + HALL_HYSTERESIS))
             && (sensorState == HALLS_STATE_OPEN)) {
    sensorStateChanged = true;
    sensorState = HALLS_STATE_CLOSED;
  }
}
#endif

void HALL_sensorInit(void)
{
  uint32_t status;
  HALL_Config hallConf;
  status = HALL_init();
  printf("HALL init status: %x\r\n", (unsigned int)status);

  if ( status == HALL_OK ) {
    hallConf.threshold    = HALL_THRESHOLD;
    hallConf.hysteresis   = HALL_HYSTERESIS;
    hallConf.polarity     = HALL_CONFIG_POLARITY_OMNIPOLAR;
    hallConf.outputInvert = false;
    HALL_configure(&hallConf);
  }
#if defined(BOARD_HALL_OUTPUT_PIN)
  HALL_registerCallback(HALL_stateCallback);
#endif
}

void HALL_sensorDeinit(void)
{
  HALL_deInit();
}

void HALL_task(void)
{
  static uint8_t lastHallState = HALLS_STATE_OPEN;
  uint8_t hallState;
  bool    hallStateChanged;

  /* Read magnetic field strength and set door state */
  HALL_measure(20000, &sensorMagneticField);

#if !defined(BOARD_HALL_OUTPUT_PIN)
  /* Perform filtering from SW if dedicated pin is not available */
  HALL_swFilter();
#endif

  hallServiceFieldUpdated(sensorMagneticField);

  /* Disable interrupts while reading/updating state variables */
  CORE_CRITICAL_IRQ_DISABLE();
  hallState = sensorState;
  hallStateChanged = sensorStateChanged;
  if ( sensorStateChanged ) {
    sensorStateChanged = false;
  }
  CORE_CRITICAL_IRQ_ENABLE();

  /* We need to use the field strength to discern between open and tamper states */
  if ( hallState == HALLS_STATE_OPEN ) {
    if ( fabsf(sensorMagneticField) >= HALL_getTamperLevel() ) {
      hallState = HALLS_STATE_TAMPER;
    } else {
      hallState = HALLS_STATE_OPEN;
    }
  }

  if ( lastHallState != hallState ) {
    hallStateChanged = true;
    lastHallState = hallState;
  }

  if ( hallStateChanged ) {
    hallServiceStateChanged(hallState);
  }
}
