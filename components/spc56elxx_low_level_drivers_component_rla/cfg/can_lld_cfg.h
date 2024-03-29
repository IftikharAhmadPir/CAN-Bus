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
 * @file    can_lld_cfg.h
 * @brief   CAN Driver configuration macros and structures.
 *
 * @addtogroup CAN
 * @{
 */

#ifndef _CAN_LLD_CFG_H_
#define _CAN_LLD_CFG_H_

#include "spc5_lld.h"
#include "can_lld.h"

#if (LLD_USE_CAN == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/* List of the CANConfig structures defined in can_lld_cfg.c.*/
extern const CANConfig can_config_cfg0;

#ifdef __cplusplus
extern "C" {
#endif
  /* List of the callback functions referenced from the CANConfig
     structures in can_lld_cfg.c.*/
void can_receive(void);
void cfg0_errorcb(CANDriver *canp, uint32_t esr,uint8_t rx_err_counter, uint8_t tx_err_counter);
#ifdef __cplusplus
}
#endif

#endif /* LLD_USE_CAN */

#endif /* _CAN_LLD_CFG_H_ */

/** @} */
