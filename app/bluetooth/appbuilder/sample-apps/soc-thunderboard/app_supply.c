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

#include <stdio.h>

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_emu.h"
#if defined(ADC_PRESENT)
#include "em_adc.h"
#elif defined(IADC_PRESENT)
#include "em_iadc.h"
#endif
#include "em_cmu.h"
#include "em_prs.h"

#include "thunderboard/board.h"
#include "thunderboard/si7021.h"
#include "thunderboard/util.h"

#include "app_supply.h"

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

#if defined(ADC_PRESENT)
/* 5V reference voltage, no attenuation on AVDD, 12 bit ADC data */
  #define ADC_SCALE_FACTOR   (5.0 / 4095.0)
#elif defined(IADC_PRESENT)
/* 1.21V reference voltage, AVDD attenuated by a factor of 4, 12 bit ADC data */
  #define ADC_SCALE_FACTOR   (4.84 / 4095.0)
#endif

static float   measureSupplyIR           (uint8_t loadSetting);

float UTIL_supplyVoltage;  /**< Loaded supply voltage                */
float UTIL_supplyIR;       /**< Internal resistance of the supply    */
uint8_t UTIL_supplyType;   /**< Type of the connected supply         */

/** @endcond */

/***************************************************************************//**
 * @brief
 *    Initializes the A/D converter
 *
 * @return
 *    None
 ******************************************************************************/
static void adcInit(void)
{
#if defined(ADC_PRESENT)
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

  CMU_ClockEnable(cmuClock_ADC0, true);
  CMU_ClockEnable(cmuClock_PRS, true);

  /* Only configure the ADC if it is not already running */
  if ( ADC0->CTRL == _ADC_CTRL_RESETVALUE ) {
    init.timebase = ADC_TimebaseCalc(0);
    init.prescale = ADC_PrescaleCalc(1000000, 0);
    ADC_Init(ADC0, &init);
  }

  initSingle.acqTime = adcAcqTime16;
  initSingle.reference = adcRef5VDIFF;
  initSingle.posSel = adcPosSelAVDD;
  initSingle.negSel = adcNegSelVSS;
  initSingle.prsEnable = true;
  initSingle.prsSel = adcPRSSELCh4;

  ADC_InitSingle(ADC0, &initSingle);
#elif defined(IADC_PRESENT)
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t allConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;
  IADC_SingleInput_t input = IADC_SINGLEINPUT_DEFAULT;

  CMU_ClockEnable(cmuClock_IADC0, true);
  CMU_ClockEnable(cmuClock_PRS, true);

  /* Only configure the ADC if it is not already running */
  if ( IADC0->CTRL == _IADC_CTRL_RESETVALUE ) {
    IADC_init(IADC0, &init, &allConfigs);
  }

  input.posInput = iadcPosInputAvdd;

  IADC_initSingle(IADC0, &initSingle, &input);
  IADC_enableInt(IADC0, IADC_IEN_SINGLEDONE);
#endif
  return;
}

/***************************************************************************//**
 * @brief
 *    Initiates an A/D conversion and reads the sample when done
 *
 * @return
 *    The output of the A/D conversion
 ******************************************************************************/
static uint16_t getAdcSample(void)
{
#if defined(ADC_PRESENT)
  ADC_Start(ADC0, adcStartSingle);
  while ( !(ADC_IntGet(ADC0) & ADC_IF_SINGLE) )
    ;

  return ADC_DataSingleGet(ADC0);
#elif defined(IADC_PRESENT)
  /* Clear single done interrupt */
  IADC_clearInt(IADC0, IADC_IF_SINGLEDONE);

  /* Start conversion and wait for result */
  IADC_command(IADC0, IADC_CMD_SINGLESTART);
  while ( !(IADC_getInt(IADC0) & IADC_IF_SINGLEDONE) ) ;

  return IADC_readSingleData(IADC0);
#endif
}

/***************************************************************************//**
 * @brief
 *    Measures the supply voltage by averaging multiple readings
 *
 * @param[in] avg
 *    Number of measurements to average
 *
 * @return
 *    The measured voltage
 ******************************************************************************/
float SUPPLY_measureVoltage(unsigned int avg)
{
  uint16_t adcData;
  float supplyVoltage;
  int i;

  adcInit();

  supplyVoltage = 0;

  for ( i = 0; i < avg; i++ ) {
    adcData = getAdcSample();
    supplyVoltage += (float) adcData * ADC_SCALE_FACTOR;
  }

  supplyVoltage = supplyVoltage / (float) avg;

  return supplyVoltage;
}

/***************************************************************************//**
 * @brief
 *    Measures the unloaded and loaded supply voltage and calculates the internal
 *    resistance of the connected supply. The load is provided by the heater
 *    element built in the Si7021.
 *
 * @param[in] loadSetting
 *    Heater current setting of the Si7021
 *
 * @return
 *    The measured internal resistance of the connected supply
 ******************************************************************************/
static float measureSupplyIR(uint8_t loadSetting)
{
  float supplyVoltage;
  float supplyVoltageLoad;
  float i, r;

  uint8_t cmd;
  uint8_t data;

  UTIL_delay(250);
  supplyVoltage = SUPPLY_measureVoltage(16);

  /* Enable heater in Si7021 - 9.81 mA */
  cmd = SI7021_CMD_WRITE_HEATER_CTRL;
  data = loadSetting;
  SI7021_cmdWrite(&cmd, 1, &data, 1);

  cmd = SI7021_CMD_WRITE_USER_REG1;
  data = 0x04;
  SI7021_cmdWrite(&cmd, 1, &data, 1);

  /* Wait for battery voltage to settle */
  UTIL_delay(250);
  supplyVoltageLoad = SUPPLY_measureVoltage(16);

  /* Turn off heater */
  cmd = SI7021_CMD_WRITE_USER_REG1;
  data = 0x00;
  SI7021_cmdWrite(&cmd, 1, &data, 1);

  i = 0.006074 * loadSetting + 0.00309;
  r = (supplyVoltage - supplyVoltageLoad) / i;

  printf(" sv = %.3f  svl = %.3f   i = %.3f   r = %.3f\r\n",
         supplyVoltage, supplyVoltageLoad, i, r);

  return r;
}

/***************************************************************************//**
 * @brief
 *    Probes the connected supply and determines its type. The results are
 *    stored in global variables.
 *
 * @return
 *    None
 ******************************************************************************/
void SUPPLY_probe(void)
{
  SI7021_init();

  uint8_t type;
  float r, v;

  type = SUPPLY_TYPE_UNKNOWN;

  /* Try to measure using 9.18 mA first */
  v = SUPPLY_measureVoltage(16);
  r = measureSupplyIR(0x00);
  if ( r > 5.0 ) {
    type = SUPPLY_TYPE_CR2032;
  } else if (r > 0.5) {
    type = SUPPLY_TYPE_AAA;
  } else {
    type = SUPPLY_TYPE_USB;
  }

  UTIL_supplyVoltage = v;
  UTIL_supplyIR = r;
  UTIL_supplyType = type;

  SI7021_deInit();

  return;
}

/***************************************************************************//**
 * @brief
 *    Retrieves the supply characteristic variables
 *
 * @param[in] type
 *    Supply type
 *
 * @param[in] voltage
 *    Loaded supply voltage
 *
 * @param[in] ir
 *    Internal resistance of the supply
 *
 * @return
 *    None
 ******************************************************************************/
void SUPPLY_getCharacteristics(uint8_t *type, float *voltage, float *ir)
{
  *type    = UTIL_supplyType;
  *voltage = UTIL_supplyVoltage;
  *ir      = UTIL_supplyIR;

  return;
}

/***************************************************************************//**
 * @brief
 *    Returns the type of the power supply
 *
 * @return
 *    The type of the supply
 ******************************************************************************/
uint8_t SUPPLY_getType(void)
{
  return UTIL_supplyType;
}

/***************************************************************************//**
 * @brief
 *    Checks if the current power supply has low power capability
 *
 * @return
 *    True if the supply is low power type, false otherwise
 ******************************************************************************/
bool SUPPLY_isLowPower(void)
{
  bool lp;

  if ( (UTIL_supplyType != SUPPLY_TYPE_CR2032) && (UTIL_supplyType != SUPPLY_TYPE_UNKNOWN) ) {
    lp = false;
  } else {
    lp = true;
  }

  return lp;
}
