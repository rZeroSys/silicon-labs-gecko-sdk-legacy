/***************************************************************************//**
 * @file
 * @brief Sound level meter application interface
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

#ifndef APP_SOUND_H_
#define APP_SOUND_H_

void SOUND_Init(void);
void SOUND_DeInit(void);
void SOUND_Task(void);

extern float    RADIO_soundLevel;
extern uint32_t RADIO_soundLevelBufferCount;
extern float    RADIO_soundLevelAccumulated;

#endif /* APP_SOUND_H_ */
