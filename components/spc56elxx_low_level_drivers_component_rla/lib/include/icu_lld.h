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
 * @file    icu_lld.h
 * @brief   SPC5xx ICU low level driver header.
 *
 * @addtogroup ICU
 * @{
 */

#ifndef _ICU_LLD_H_
#define _ICU_LLD_H_

#include "spc5_lld.h"
#include "lldconf.h"

#if (LLD_USE_ICU == TRUE) || defined(__DOXYGEN__)

#include "spc5_etimer.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Mode options
 * @{
 */

/**
 * @brief   Skip first capture cycle.
 * @details If set to @p TRUE the first capture cycle is skipped.
 * @note    The default is @p FALSE.
 */
#if !defined(ICU_JUMP_FIRST_CAPTURE) || defined(__DOXYGEN__)
#define ICU_SKIP_FIRST_CAPTURE              FALSE
#endif

#define SPC5_ETIMER_IP_BUS_CLK_DIV_1        0x18U
#define SPC5_ETIMER_IP_BUS_CLK_DIV_2        0x19U
#define SPC5_ETIMER_IP_BUS_CLK_DIV_4        0x1AU
#define SPC5_ETIMER_IP_BUS_CLK_DIV_8        0x1BU
#define SPC5_ETIMER_IP_BUS_CLK_DIV_16       0x1CU
#define SPC5_ETIMER_IP_BUS_CLK_DIV_32       0x1DU
#define SPC5_ETIMER_IP_BUS_CLK_DIV_64       0x1EU
#define SPC5_ETIMER_IP_BUS_CLK_DIV_128      0x1FU

#define SPC5_ETIMER_COUNTER_0_INPUT_PIN     0U
#define SPC5_ETIMER_COUNTER_1_INPUT_PIN     1U
#define SPC5_ETIMER_COUNTER_2_INPUT_PIN     2U
#define SPC5_ETIMER_COUNTER_3_INPUT_PIN     3U
#define SPC5_ETIMER_COUNTER_4_INPUT_PIN     4U
#define SPC5_ETIMER_COUNTER_5_INPUT_PIN     5U

#define SPC5_ETIMER_CNTMODE_NO_OPERATION    0U
#define SPC5_ETIMER_CNTMODE_RE              1U
#define SPC5_ETIMER_CNTMODE_RFE             2U
#define SPC5_ETIMER_CNTMODE_RFE_SIHA        3U
#define SPC5_ETIMER_CNTMODE_QUADRATURE      4U
#define SPC5_ETIMER_CNTMODE_RE_SSSD         5U
#define SPC5_ETIMER_CNTMODE_ESS_TRIGGER     6U
#define SPC5_ETIMER_CNTMODE_CASCADE         7U

#define SPC5_ETIMER_CPT1MODE_DISABLED       0U
#define SPC5_ETIMER_CPT1MODE_FALLING_EDGE   1U
#define SPC5_ETIMER_CPT1MODE_RISING_EDGE    2U
#define SPC5_ETIMER_CPT1MODE_ANY_EDGE       3U

#define SPC5_ETIMER_CPT2MODE_DISABLED       0U
#define SPC5_ETIMER_CPT2MODE_FALLING_EDGE   1U
#define SPC5_ETIMER_CPT2MODE_RISING_EDGE    2U
#define SPC5_ETIMER_CPT2MODE_ANY_EDGE       3U

#define SPC5_ETIMER_ROC_DO_NOT_RELOAD       0U
#define SPC5_ETIMER_ROC_REL_ON_CAP1         1U
#define SPC5_ETIMER_ROC_REL_ON_CAP2         2U
#define SPC5_ETIMER_ROC_REL_ON_CAP1_CAP2    3U
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   ICUD1 driver enable switch.
 * @details If set to @p TRUE the support for ICUD1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD0) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD0                  FALSE
#endif

/**
 * @brief   ICUD2 driver enable switch.
 * @details If set to @p TRUE the support for ICUD2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD1) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD1                  FALSE
#endif

/**
 * @brief   ICUD3 driver enable switch.
 * @details If set to @p TRUE the support for ICUD3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD2) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD2                  FALSE
#endif

/**
 * @brief   ICUD4 driver enable switch.
 * @details If set to @p TRUE the support for ICUD4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD3) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD3                  FALSE
#endif

/**
 * @brief   ICUD5 driver enable switch.
 * @details If set to @p TRUE the support for ICUD5 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD4) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD4                  FALSE
#endif

/**
 * @brief   ICUD6 driver enable switch.
 * @details If set to @p TRUE the support for ICUD6 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD5) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD5                  FALSE
#endif

/**
 * @brief   eTimer0 interrupt priority level setting.
 */
#if !defined(SPC5_ICU_ETIMER0_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER0_PRIORITY           7
#endif

/**
 * @brief   eTIMER0 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER0_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER0_START_PCTL         (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   eTIMER0 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER0_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER0_STOP_PCTL          (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#endif

/**
 * @brief   ICUD6 driver enable switch.
 * @details If set to @p TRUE the support for ICUD6 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD6) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD6                  FALSE
#endif

/**
 * @brief   ICUD7 driver enable switch.
 * @details If set to @p TRUE the support for ICUD7 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD7) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD7                  FALSE
#endif

/**
 * @brief   ICUD8 driver enable switch.
 * @details If set to @p TRUE the support for ICUD8 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD8) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD8                  FALSE
#endif

/**
 * @brief   ICUD9 driver enable switch.
 * @details If set to @p TRUE the support for ICUD9 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD9) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD9                  FALSE
#endif

/**
 * @brief   ICUD10 driver enable switch.
 * @details If set to @p TRUE the support for ICUD10 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD10) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD10                 FALSE
#endif

/**
 * @brief   ICUD11 driver enable switch.
 * @details If set to @p TRUE the support for ICUD11 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD11) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD11                 FALSE
#endif

/**
 * @brief   eTimer1 interrupt priority level setting.
 */
#if !defined(SPC5_ICU_ETIMER1_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER1_PRIORITY           7
#endif

/**
 * @brief   eTIMER1 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER1_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER1_START_PCTL         (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   eTIMER1 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER1_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER1_STOP_PCTL          (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#endif

/**
 * @brief   ICUD13 driver enable switch.
 * @details If set to @p TRUE the support for ICUD13 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD12) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD12                 FALSE
#endif

/**
 * @brief   ICUD14 driver enable switch.
 * @details If set to @p TRUE the support for ICUD14 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD13) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD13                 FALSE
#endif

/**
 * @brief   ICUD15 driver enable switch.
 * @details If set to @p TRUE the support for ICUD15 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD14) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD14                 FALSE
#endif

/**
 * @brief   ICUD16 driver enable switch.
 * @details If set to @p TRUE the support for ICUD16 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD15) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD15                 FALSE
#endif

/**
 * @brief   ICUD17 driver enable switch.
 * @details If set to @p TRUE the support for ICUD17 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD16) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD16                 FALSE
#endif

/**
 * @brief   ICUD18 driver enable switch.
 * @details If set to @p TRUE the support for ICUD18 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD17) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD17                 FALSE
#endif

/**
 * @brief   eTimer2 interrupt priority level setting.
 */
#if !defined(SPC5_ICU_ETIMER2_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER2_PRIORITY           7
#endif

/**
 * @brief   eTIMER2 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER2_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER2_START_PCTL         (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   eTIMER2 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER2_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER2_STOP_PCTL          (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#endif
/**
 * @brief   ICUD19 driver enable switch.
 * @details If set to @p TRUE the support for ICUD19 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD18) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD18                 FALSE
#endif

/**
 * @brief   ICUD20 driver enable switch.
 * @details If set to @p TRUE the support for ICUD20 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD19) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD19                 FALSE
#endif

/**
 * @brief   ICUD21 driver enable switch.
 * @details If set to @p TRUE the support for ICUD21 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD20) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD20                 FALSE
#endif

/**
 * @brief   ICUD22 driver enable switch.
 * @details If set to @p TRUE the support for ICUD22 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD21) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD21                 FALSE
#endif

/**
 * @brief   ICUD23 driver enable switch.
 * @details If set to @p TRUE the support for ICUD23 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD22) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD22                 FALSE
#endif

/**
 * @brief   ICUD24 driver enable switch.
 * @details If set to @p TRUE the support for ICUD24 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_SMOD23) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_SMOD23                 FALSE
#endif

/**
 * @brief   eTimer3 interrupt priority level setting.
 */
#if !defined(SPC5_ICU_ETIMER3_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER3_PRIORITY           7
#endif

/**
 * @brief   eTIMER3 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER3_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER3_START_PCTL         (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   eTIMER3 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode.
 */
#if !defined(SPC5_ICU_ETIMER3_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_ICU_ETIMER3_STOP_PCTL          (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if (SPC5_ICU_USE_SMOD0 == TRUE || SPC5_ICU_USE_SMOD1 == TRUE || \
     SPC5_ICU_USE_SMOD2 == TRUE || SPC5_ICU_USE_SMOD3 == TRUE || \
     SPC5_ICU_USE_SMOD4 == TRUE || SPC5_ICU_USE_SMOD5 == TRUE)
#define SPC5_ICU_USE_ETIMER0                TRUE
#else
#define SPC5_ICU_USE_ETIMER0                FALSE
#endif

#if (SPC5_ICU_USE_SMOD6  == TRUE || SPC5_ICU_USE_SMOD7  == TRUE || \
     SPC5_ICU_USE_SMOD8  == TRUE || SPC5_ICU_USE_SMOD9  == TRUE || \
     SPC5_ICU_USE_SMOD10 == TRUE || SPC5_ICU_USE_SMOD11 == TRUE)
#define SPC5_ICU_USE_ETIMER1                TRUE
#else
#define SPC5_ICU_USE_ETIMER1                FALSE
#endif

#if (SPC5_ICU_USE_SMOD12 == TRUE || SPC5_ICU_USE_SMOD13 == TRUE || \
     SPC5_ICU_USE_SMOD14 == TRUE || SPC5_ICU_USE_SMOD15 == TRUE || \
     SPC5_ICU_USE_SMOD16 == TRUE || SPC5_ICU_USE_SMOD17 == TRUE)
#define SPC5_ICU_USE_ETIMER2                TRUE
#else
#define SPC5_ICU_USE_ETIMER2                FALSE
#endif

#if (SPC5_ICU_USE_SMOD18 == TRUE || SPC5_ICU_USE_SMOD19 == TRUE || \
     SPC5_ICU_USE_SMOD20 == TRUE || SPC5_ICU_USE_SMOD21 == TRUE || \
     SPC5_ICU_USE_SMOD22 == TRUE || SPC5_ICU_USE_SMOD23 == TRUE)
#define SPC5_ICU_USE_ETIMER3                TRUE
#else
#define SPC5_ICU_USE_ETIMER3                FALSE
#endif
											 
#if (SPC5_HAS_ETIMER0 == FALSE && SPC5_ICU_USE_ETIMER0 == TRUE)
#error "ETIMER0 not present in the selected device"
#endif

#if (SPC5_HAS_ETIMER1 == FALSE && SPC5_ICU_USE_ETIMER1 == TRUE)
#error "ETIMER1 not present in the selected device"
#endif

#if (SPC5_HAS_ETIMER2 == FALSE && SPC5_ICU_USE_ETIMER2 == TRUE)
#error "ETIMER2 not present in the selected device"
#endif

#if (SPC5_HAS_ETIMER3 == FALSE && SPC5_ICU_USE_ETIMER3 == TRUE)
#error "ETIMER3 not present in the selected device"
#endif

#if (SPC5_ICU_USE_ETIMER0 == FALSE && SPC5_ICU_USE_ETIMER1 == FALSE && \
     SPC5_ICU_USE_ETIMER2 == FALSE && SPC5_ICU_USE_ETIMER3 == FALSE)
#error "ICU driver activated but no SMOD peripheral assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing an ICU driver.
 */
typedef struct ICUDriver ICUDriver;

/**
 * @brief   ICU notification callback type.
 *
 * @param[in] icup      pointer to a @p ICUDriver object
 */
typedef void (*icucallback_t)(ICUDriver *icup);

/**
 * @brief ICU driver mode.
 */
typedef enum {
  ICU_INPUT_ACTIVE_HIGH = 0, /**< Trigger on rising edge.            */
  ICU_INPUT_ACTIVE_LOW = 1   /**< Trigger on falling edge.           */
} icumode_t;

/**
 * @brief   ICU frequency type.
 */
typedef uint32_t icufreq_t;

/**
 * @brief   ICU channel.
 */
typedef enum {
  ICU_CHANNEL_1 = 0, /**< Use SMODxCH1.      */
  ICU_CHANNEL_2 = 1, /**< Use SMODxCH2.      */
  ICU_CHANNEL_3 = 2, /**< Use SMODxCH3.      */
  ICU_CHANNEL_4 = 3, /**< Use SMODxCH4.      */
  ICU_CHANNEL_5 = 4, /**< Use SMODxCH5.      */
  ICU_CHANNEL_6 = 5  /**< Use SMODxCH6.      */
} icuchannel_t;

/**
 * @brief   ICU counter type.
 */
typedef uint16_t icucnt_t;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
  /**
   * @brief   Driver mode.
   */
  icumode_t mode;
  /**
   * @brief   Timer clock in Hz.
   */
  icufreq_t frequency;
  /**
   * @brief   Callback for pulse width measurement.
   */
  icucallback_t width_cb;
  /**
   * @brief   Callback for cycle period measurement.
   */
  icucallback_t period_cb;
  /**
   * @brief   Callback for timer overflow.
   */
  icucallback_t overflow_cb;
  /* End of the mandatory fields.*/
} ICUConfig;

/**
 * @brief   Structure representing an ICU driver.
 */
struct ICUDriver {
  /**
   * @brief Current configuration data.
   */
  const ICUConfig           *config;
#if defined(ICU_DRIVER_EXT_FIELDS)
  ICU_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Clock value for this unit.
   */
  uint32_t                  clock;
  /**
   * @brief eTimer submodule number.
   */
  uint32_t                  smod_number;
  /**
   * @brief Pointer to the eTimerx registers block.
   */
  volatile struct spc5_etimer *etimerp;
  /**
   * @brief CCR register used for width capture.
   */
  volatile vuint16_t        *wccrp;
  /**
   * @brief CCR register used for period capture.
   */
  volatile vuint16_t        *pccrp;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Returns the width of the latest pulse.
 * @details The pulse width is defined as number of ticks between the start
 *          edge and the stop edge.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 * @return              The number of ticks.
 *
 * @notapi
 */
#define icu_lld_get_width(icup) (*((icup)->wccrp) + 1)

/**
 * @brief   Returns the width of the latest cycle.
 * @details The cycle width is defined as number of ticks between a start
 *          edge and the next start edge.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 * @return              The number of ticks.
 *
 * @notapi
 */
#define icu_lld_get_period(icup) (*((icup)->pccrp) + 1)

/**
 * @name    Low Level driver helper macros
 * @{
 */
/**
 * @brief   Common ISR code, ICU width event.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @notapi
 */
#define _icu_isr_invoke_width_cb(icup) {                                    \
  (icup)->config->width_cb(icup);                                           \
}

/**
 * @brief   Common ISR code, ICU period event.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @notapi
 */
#define _icu_isr_invoke_period_cb(icup) {                                   \
  (icup)->config->period_cb(icup);                                          \
}

/**
 * @brief   Common ISR code, ICU timer overflow event.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @notapi
 */
#define _icu_isr_invoke_overflow_cb(icup) {                                 \
  (icup)->config->overflow_cb(icup);                                        \
}
/** @} */

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/

#if (SPC5_ICU_USE_SMOD0 == TRUE)
IRQ_HANDLER(SPC5_ETIMER0_TC0IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD0 */

#if (SPC5_ICU_USE_SMOD1 == TRUE)
IRQ_HANDLER(SPC5_ETIMER0_TC1IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD1 */

#if (SPC5_ICU_USE_SMOD2 == TRUE)
IRQ_HANDLER(SPC5_ETIMER0_TC2IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD2 */

#if (SPC5_ICU_USE_SMOD3 == TRUE)
IRQ_HANDLER(SPC5_ETIMER0_TC3IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD3 */

#if (SPC5_ICU_USE_SMOD4 == TRUE)
IRQ_HANDLER(SPC5_ETIMER0_TC4IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD4 */

#if (SPC5_ICU_USE_SMOD5 == TRUE)
IRQ_HANDLER(SPC5_ETIMER0_TC5IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD5 */

#if (SPC5_ICU_USE_SMOD6 == TRUE)
IRQ_HANDLER(SPC5_ETIMER1_TC0IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD6 */

#if (SPC5_ICU_USE_SMOD7 == TRUE)
IRQ_HANDLER(SPC5_ETIMER1_TC1IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD7 */

#if (SPC5_ICU_USE_SMOD8 == TRUE)
IRQ_HANDLER(SPC5_ETIMER1_TC2IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD8 */

#if (SPC5_ICU_USE_SMOD9 == TRUE)
IRQ_HANDLER(SPC5_ETIMER1_TC3IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD9 */

#if (SPC5_ICU_USE_SMOD10 == TRUE)
IRQ_HANDLER(SPC5_ETIMER1_TC4IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD10 */

#if (SPC5_ICU_USE_SMOD11 == TRUE)
IRQ_HANDLER(SPC5_ETIMER1_TC5IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD11 */

#if (SPC5_ICU_USE_SMOD12 == TRUE)
IRQ_HANDLER(SPC5_ETIMER2_TC0IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD12 */

#if (SPC5_ICU_USE_SMOD13 == TRUE)
IRQ_HANDLER(SPC5_ETIMER2_TC1IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD13 */

#if (SPC5_ICU_USE_SMOD14 == TRUE)
IRQ_HANDLER(SPC5_ETIMER2_TC2IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD14 */

#if (SPC5_ICU_USE_SMOD15 == TRUE)
IRQ_HANDLER(SPC5_ETIMER2_TC3IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD15 */

#if (SPC5_ICU_USE_SMOD16 == TRUE)
IRQ_HANDLER(SPC5_ETIMER2_TC4IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD16 */

#if (SPC5_ICU_USE_SMOD17 == TRUE)
IRQ_HANDLER(SPC5_ETIMER2_TC5IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD17 */

#if (SPC5_ICU_USE_SMOD18 == TRUE)
IRQ_HANDLER(SPC5_ETIMER3_TC0IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD18 */

#if (SPC5_ICU_USE_SMOD19 == TRUE)
IRQ_HANDLER(SPC5_ETIMER3_TC1IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD19 */

#if (SPC5_ICU_USE_SMOD20 == TRUE)
IRQ_HANDLER(SPC5_ETIMER3_TC2IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD20 */

#if (SPC5_ICU_USE_SMOD21 == TRUE)
IRQ_HANDLER(SPC5_ETIMER3_TC3IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD21 */

#if (SPC5_ICU_USE_SMOD22 == TRUE)
IRQ_HANDLER(SPC5_ETIMER3_TC4IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD22 */

#if (SPC5_ICU_USE_SMOD23 == TRUE)
IRQ_HANDLER(SPC5_ETIMER3_TC5IR_HANDLER);
#endif /* SPC5_ICU_USE_SMOD23 */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (SPC5_ICU_USE_SMOD0 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD1;
#endif

#if (SPC5_ICU_USE_SMOD1 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD2;
#endif

#if (SPC5_ICU_USE_SMOD2 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD3;
#endif

#if (SPC5_ICU_USE_SMOD3 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD4;
#endif

#if (SPC5_ICU_USE_SMOD4 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD5;
#endif

#if (SPC5_ICU_USE_SMOD5 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD6;
#endif

#if (SPC5_ICU_USE_SMOD6 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD7;
#endif

#if (SPC5_ICU_USE_SMOD7 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD8;
#endif

#if (SPC5_ICU_USE_SMOD8 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD9;
#endif

#if (SPC5_ICU_USE_SMOD9 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD10;
#endif

#if (SPC5_ICU_USE_SMOD10 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD11;
#endif

#if (SPC5_ICU_USE_SMOD11 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD12;
#endif

#if (SPC5_ICU_USE_SMOD12 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD13;
#endif

#if (SPC5_ICU_USE_SMOD13 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD14;
#endif

#if (SPC5_ICU_USE_SMOD14 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD15;
#endif

#if (SPC5_ICU_USE_SMOD15 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD16;
#endif

#if (SPC5_ICU_USE_SMOD16 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD17;
#endif

#if (SPC5_ICU_USE_SMOD17 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD18;
#endif

#if (SPC5_ICU_USE_SMOD18 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD19;
#endif

#if (SPC5_ICU_USE_SMOD19 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD20;
#endif

#if (SPC5_ICU_USE_SMOD20 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD21;
#endif

#if (SPC5_ICU_USE_SMOD21 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD22;
#endif

#if (SPC5_ICU_USE_SMOD22 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD23;
#endif

#if (SPC5_ICU_USE_SMOD23 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD24;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void icu_lld_init(void);
  void icu_lld_start(ICUDriver *icup, const ICUConfig *config);
  void icu_lld_stop(ICUDriver *icup);
  void icu_lld_enable(ICUDriver *icup);
  void icu_lld_disable(ICUDriver *icup);
#ifdef __cplusplus
}
#endif

#endif /* LLD_USE_ICU */

#endif /* _ICU_LLD_H_ */

/** @} */
