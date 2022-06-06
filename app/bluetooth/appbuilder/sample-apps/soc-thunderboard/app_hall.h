/***************************************************************************//**
 * @file
 * @brief Hall sensor application interface
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

#ifndef APP_HALL_H_
#define APP_HALL_H_

void HALL_sensorInit(void);
void HALL_sensorDeinit(void);
void HALL_task(void);

#endif /* APP_HALL_H_ */
