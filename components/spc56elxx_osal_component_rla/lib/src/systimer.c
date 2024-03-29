/*
    SPC5 RLA - Copyright (C) 2015 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License").
    You may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    systimer.c
 * @brief   OSAL module code.
 *
 * @addtogroup OSAL
 * @{
 */

#include "systimer.h"
#include "systimer_cfg.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Configures and enables the System Timer (PIT0).
 *
 * @param[in] ticks_per_sec      number of ticks per second
 *
 * @notapi
 */
void sysTimeSetup(uint32_t ticks_per_sec)
{
  uint32_t reg;

  /* PIT channel 0 initialization for system ticks, the PIT is configured
     to run in DRUN,RUN0...RUN3 and HALT0 modes, the clock is gated in other
     modes.*/
  INTC_PSR(SPC_PIT_CH0_INT_NUMBER) = INTC_PSR_ENABLE(SPC5_SYSTIMER_CORE, SPC5_SYSTIMER_IRQ_PRIORITY);
  SPCSetPeripheralClockMode(SPC5_PIT_PCTL, SPC5_ME_PCTL_RUN(2) | SPC5_ME_PCTL_LP(2));
  reg = (((uint32_t)SPCGetPeripheralClock(SPC5_PERIPHERAL_PIT0)) / ticks_per_sec) - 1U;
  PIT.PITMCR.R      = 1;        /* PIT clock enabled, stop while debugging. */
  PIT.CHANNEL[0].LDVAL.R = reg;
  PIT.CHANNEL[0].CVAL.R  = reg;
  PIT.CHANNEL[0].TFLG.R  = 1;   /* Interrupt flag cleared.                  */
  PIT.CHANNEL[0].TCTRL.R = 3;   /* Timer active, interrupt enabled.         */
}

/**
 * @brief   Reset the System Timer (PIT0).
 *
 * @notapi
 */
void sysTimeReset(void)
{
  /* Resets the PIT channel 0 IRQ flag.*/
  if (PIT.CHANNEL[0].TFLG.R == 1UL) {
    PIT.CHANNEL[0].TFLG.R = 1;
  }
}

/*===========================================================================*/
/* Module interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/** @} */
