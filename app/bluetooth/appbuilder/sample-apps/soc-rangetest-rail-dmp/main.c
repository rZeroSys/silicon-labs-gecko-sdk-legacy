/***************************************************************************//**
 * @file
 * @brief A minimal project structure, used as a starting point for custom
 * Dynamic-Multiprotocol applications. The project has the basic
 * functionality enabling peripheral connectivity, without GATT
 * services. It runs on top of Micrium OS RTOS and multiprotocol RAIL.
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

#include "bsp/siliconlabs/generic/include/bsp_os.h"

#include <common/include/common.h>
#include <common/include/logging.h>
#include <common/include/lib_def.h>
#include <common/include/rtos_utils.h>
#include <common/include/toolchains.h>
#include <common/include/rtos_prio.h>
#include <cpu/include/cpu.h>
#include <kernel/include/os.h>
#if (OS_CFG_TRACE_EN == DEF_ENABLED)
#include <kernel/include/os_trace.h>
#endif

#include "hal-config.h"
#include "bsphalconfig.h"
#include "bsp.h"

#include "em_core.h"
#include "em_cmu.h"
#include "sleep.h"

#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"

#include "graphics.h"

#include "rangeTest.h"
#include "bluetooth.h"
#include "infrastructure.h"

// Ex Main Start task
#define EX_MAIN_START_TASK_PRIO           21u
#define EX_MAIN_START_TASK_STK_SIZE       512u
static CPU_STK exMainStartTaskStk[EX_MAIN_START_TASK_STK_SIZE];
static OS_TCB  exMainStartTaskTCB;
static void    exMainStartTask(void *p_arg);

// Bluetooth Application task
#define BLUETOOTH_APP_TASK_PRIO           5u
#define BLUETOOTH_APP_TASK_STACK_SIZE     (1024 / sizeof(CPU_STK))
static CPU_STK bluetoothAppTaskStk[BLUETOOTH_APP_TASK_STACK_SIZE];
static OS_TCB  bluetoothAppTaskTCB;

// Proprietary Application task
#define PROPRIETARY_APP_TASK_PRIO         6u
#define PROPRIETARY_APP_TASK_STACK_SIZE   (1000 / sizeof(CPU_STK))
static CPU_STK proprietaryAppTaskStk[PROPRIETARY_APP_TASK_STACK_SIZE];
static OS_TCB  proprietaryAppTaskTCB;

// Logging task
//#define LOGGING_TASK_PRIO                 20u
//#define LOGGING_TASK_STACK_SIZE           (1000 / sizeof(CPU_STK))
//static CPU_STK loggingTaskStk[LOGGING_TASK_STACK_SIZE];
//static OS_TCB  loggingTaskTCB;

/**************************************************************************//**
 * Main.
 *
 * @returns Returns 1.
 *
 * This is the standard entry point for C applications. It is assumed that your
 * code will call main() once you have performed all necessary initialization.
 *****************************************************************************/
int main(void)
{
  RTOS_ERR err;
  CORE_DECLARE_IRQ_STATE;

  // Initialize device.
  initMcu();
  // Initialize board.
  initBoard();
  // Initialize application.
  initApp();
  initVcomEnable();

  // GRAPHICS_Init() needs to come before OSInit().
  // Udelay module in GRAPHICS_Init() disables the RTCC interrupt.
  // sl_sleetimer_init() in OSInit() depends on and sets up RTCC interrupt correctly.
  GRAPHICS_Init();

  // Initialize the Kernel.
  OSInit(&err);
  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));

  CORE_ENTER_ATOMIC();
  // Don't allow EM3, since we use LF clocks.
#if OS_CFG_DYN_TICK_EN == DEF_ENABLED
  SLEEP_SleepBlockBegin(sleepEM3);
#else
  SLEEP_SleepBlockBegin(sleepEM2);
#endif
  CORE_EXIT_ATOMIC();

  // Create the Ex Main Start task
  OSTaskCreate(&exMainStartTaskTCB,
               "Ex Main Start Task",
               exMainStartTask,
               DEF_NULL,
               EX_MAIN_START_TASK_PRIO,
               &exMainStartTaskStk[0],
               (EX_MAIN_START_TASK_STK_SIZE / 10u),
               EX_MAIN_START_TASK_STK_SIZE,
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CLR),
               &err);
  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));
  // Start the kernel.
  OSStart(&err);
  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));

  return (1);
}

/***************************************************************************//**
 * This is the idle hook.
 *
 * This will be called by the Micrium OS idle task when there is no other task
 * ready to run. We just enter the lowest possible energy mode.
 ******************************************************************************/
void SleepAndSyncProtimer(void);
void OSIdleContextHook(void)
{
  while (1) {
    /* Put MCU in the lowest sleep mode available, usually EM2 */
    SleepAndSyncProtimer();
  }
}

/**************************************************************************//**
 * Task to initialise Bluetooth and Proprietary tasks.
 *
 * @param p_arg Pointer to an optional data area which can pass parameters to
 *              the task when the task executes.
 *
 * This is the task that will be called by from main() when all services are
 * initialized successfully.
 *****************************************************************************/
static void exMainStartTask(void *p_arg)
{
  PP_UNUSED_PARAM(p_arg);
  RTOS_ERR err;

#ifdef CPU_CFG_INT_DIS_MEAS_EN
  // Initialize interrupts disabled measurement.
  CPU_IntDisMeasMaxCurReset();
#endif

  // Initialise common module
  Common_Init(&err);
  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));

#if (OS_CFG_TRACE_EN == DEF_ENABLED)
  // Initialize the Trace recorder.
  OS_TRACE_INIT();
#endif

  // Create the Bluetooth Application task
  OSTaskCreate(&bluetoothAppTaskTCB,
               "Bluetooth App Task",
               bluetoothAppTask,
               0u,
               BLUETOOTH_APP_TASK_PRIO,
               &bluetoothAppTaskStk[0u],
               (BLUETOOTH_APP_TASK_STACK_SIZE / 10u),
               BLUETOOTH_APP_TASK_STACK_SIZE,
               0u,
               0u,
               0u,
               (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
               &err);
  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));

  // Create the Proprietary Application task
  OSTaskCreate(&proprietaryAppTaskTCB,
               "Proprietary App Task",
               proprietaryAppTask,
               0u,
               PROPRIETARY_APP_TASK_PRIO,
               &proprietaryAppTaskStk[0u],
               (PROPRIETARY_APP_TASK_STACK_SIZE / 10u),
               PROPRIETARY_APP_TASK_STACK_SIZE,
               0u,
               0u,
               0u,
               (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
               &err);
  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));

//  // Create the Logging task
//  OSTaskCreate(&loggingTaskTCB,
//               "Logging Task",
//               loggingTask,
//               0u,
//               LOGGING_TASK_PRIO,
//               &loggingTaskStk[0u],
//               (LOGGING_TASK_STACK_SIZE / 10u),
//               LOGGING_TASK_STACK_SIZE,
//               0u,
//               0u,
//               0u,
//               (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
//               &err);
//  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));

  // Done starting everyone else so let's exit.
  OSTaskDel((OS_TCB *)0, &err);
  APP_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), RTOS_ERR_CODE_GET(err));
}