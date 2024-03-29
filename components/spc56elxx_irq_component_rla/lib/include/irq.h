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
 * @file    irq.h
 * @brief   IRQ module header.
 *
 * @addtogroup IRQ
 * @{
 */

#ifndef _IRQ_H_
#define _IRQ_H_

#include "vectors.h"
#include "irq_cfg.h"
#include "platform.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   IRQ prologue code.
 * @details This macro must be inserted at the start of all IRQ handlers.
 */
#define IRQ_PROLOGUE()

/**
 * @brief   IRQ epilogue code.
 * @details This macro must be inserted at the end of all IRQ handlers.
 */
#define IRQ_EPILOGUE()

/**
 * @brief   IRQ handler function declaration.
 * @details This macro hides the details of an ISR function declaration.
 *
 * @param[in] id        a vector name as defined in @p vectors.s
 */
#define IRQ_HANDLER(id) void id(void)

/*===========================================================================*/
/* Inline functions.                                                            */
/*===========================================================================*/

/**
 * @brief   Globally enables interrupts.
 *
 * @special
 */
static inline
void irqIsrEnable(void) {
#ifdef __ghs__
  asm ("wrteei  1");
#else
  asm volatile("wrteei  1" : : : "memory");
#endif
}

/**
 * @brief   Globally disables interrupts.
 *
 * @special
 */
static inline
void irqIsrDisable(void) {

#ifdef __ghs__
  asm ("wrteei  0");
#else
  asm volatile ("wrteei  0" : : : "memory");
#endif
}

/**
 * @brief   Returns the value of the Machine State Register (MSR).
 *
 * @special
 */
#ifdef __ghs__
static inline __asm uint32_t irqGetMsr(void) {

  mfmsr r3
}
#else
static inline uint32_t irqGetMsr(void) {

  uint32_t msr = 0UL;

  asm volatile("mfmsr %0" : "=r" (msr) :);

  return msr;
}
#endif

/**
 * @brief   Returns the value of the External Interrupt Enable (MSR[EE]) bit.
 *
 * @special
 */
static inline
uint32_t irqGetExtIntEnable(void) {

  uint32_t msr;

  msr = irqGetMsr();

  return (0x1UL & (msr >> 15U));
}

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void irqInit(void);
  void irqSysHalt(void);
#ifdef __cplusplus
}
#endif

#endif /* _IRQ_H_ */

/** @} */
