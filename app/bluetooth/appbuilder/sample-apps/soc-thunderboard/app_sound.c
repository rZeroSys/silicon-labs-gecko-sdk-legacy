/***************************************************************************//**
 * @file
 * @brief Sound level meter application code
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

#include "ble-configuration.h"
#include "mic.h"

#if defined(BRD4160A)
  #define MIC_SAMPLE_RATE            1000
  #define MIC_SAMPLE_BUFFER_SIZE     512
  #define MIC_CONSTANT               101.33f
typedef uint16_t micSample_t;
#elif defined(BRD4166A)
  #define MIC_SAMPLE_RATE            8000
  #define MIC_SAMPLE_BUFFER_SIZE     2048
  #define MIC_CONSTANT               120.0f
typedef uint16_t micSample_t;
#endif

static micSample_t micSampleBuffer[MIC_SAMPLE_BUFFER_SIZE];

float    RADIO_soundLevel            = -60;
uint32_t RADIO_soundLevelBufferCount = 0;
float    RADIO_soundLevelAccumulated = 0;

void SOUND_Init(void)
{
  MIC_init(MIC_SAMPLE_RATE, micSampleBuffer, MIC_SAMPLE_BUFFER_SIZE);
}

void SOUND_DeInit(void)
{
  MIC_deInit();
}

void SOUND_Task(void)
{
  float micSoundLevel;

  /* If sampling is completed */
  if ( !MIC_isBusy() ) {
    /* If there are actual samples in the buffer (sample count is non-zero) */
    if ( MIC_getSampleCount() ) {
      micSoundLevel = MIC_getSoundLevel(NULL) + MIC_CONSTANT;
      MIC_start(MIC_SAMPLE_BUFFER_SIZE);

      RADIO_soundLevelAccumulated += micSoundLevel;
      RADIO_soundLevelBufferCount++;

      RADIO_soundLevel = RADIO_soundLevelAccumulated / RADIO_soundLevelBufferCount;
    } else {
      /* Sampling was never requested, start mic for the first time */
      MIC_start(MIC_SAMPLE_BUFFER_SIZE);
    }
  }
}
