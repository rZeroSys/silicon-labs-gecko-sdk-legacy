/***************************************************************************//**
 * @file
 * @brief Power Supply Related Utility Functions
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

#ifndef APP_SUPPLY_H_
#define APP_SUPPLY_H_

#include <stdint.h>
#include <stdbool.h>

#define SUPPLY_TYPE_UNKNOWN    0 /**< Unknown power supply type                */
#define SUPPLY_TYPE_USB        1 /**< The board powered from the USB connector */
#define SUPPLY_TYPE_AA         2 /**< The board powered from AA batteries      */
#define SUPPLY_TYPE_AAA        3 /**< The board powered from AAA batteries     */
#define SUPPLY_TYPE_CR2032     4 /**< The board powered from a CR2032 battery  */

void     SUPPLY_probe                (void);
void     SUPPLY_getCharacteristics   (uint8_t *type, float *voltage, float *ir);
uint8_t  SUPPLY_getType              (void);
bool     SUPPLY_isLowPower           (void);
float    SUPPLY_measureVoltage       (unsigned int avg);

#endif /* APP_SUPPLY_H_ */
