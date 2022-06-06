/***************************************************************************//**
 * @file
 * @brief rtos_description.h
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

/*
 *********************************************************************************************************
 *
 *                                           RTOS DESCRIPTION
 *
 *                                      CONFIGURATION TEMPLATE FILE
 *
 * File : rtos_description.h
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *********************************************************************************************************
 *                                               MODULE
 *********************************************************************************************************
 *********************************************************************************************************
 */

#ifndef  _RTOS_DESCRIPTION_H_
#define  _RTOS_DESCRIPTION_H_

/*
 *********************************************************************************************************
 *********************************************************************************************************
 *                                             INCLUDE FILES
 *********************************************************************************************************
 *********************************************************************************************************
 */

#include  <common/include/rtos_opt_def.h>

/*
 *********************************************************************************************************
 *********************************************************************************************************
 *                                       ENVIRONMENT DESCRIPTION
 *********************************************************************************************************
 *********************************************************************************************************
 */

#define  RTOS_CPU_SEL                                       RTOS_CPU_SEL_SILABS_GECKO_AUTO

#define  RTOS_TOOLCHAIN_SEL                                 RTOS_TOOLCHAIN_AUTO

#define  RTOS_INT_CONTROLLER_SEL                            RTOS_INT_CONTROLLER_AUTO

/*
 *********************************************************************************************************
 *********************************************************************************************************
 *                                       RTOS MODULES DESCRIPTION
 *********************************************************************************************************
 *********************************************************************************************************
 */

/* ---------------------- KERNEL ---------------------- */
#define  RTOS_MODULE_KERNEL_AVAIL

/* ---------------------- COMMON ---------------------- */
#define  RTOS_MODULE_COMMON_CLK_AVAIL
#define  RTOS_MODULE_COMMON_SHELL_AVAIL

/*
 *********************************************************************************************************
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 *********************************************************************************************************
 */

#endif /* End of rtos_description.h module include.            */