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
 * @file    typedefs.h
 * @brief   Dummy typedefs file.
 */

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*
 * Derived generic types.
 */
typedef volatile int8_t     vint8_t;        /**< Volatile signed 8 bits.    */
typedef volatile uint8_t    vuint8_t;       /**< Volatile unsigned 8 bits.  */
typedef volatile int16_t    vint16_t;       /**< Volatile signed 16 bits.   */
typedef volatile uint16_t   vuint16_t;      /**< Volatile unsigned 16 bits. */
typedef volatile int32_t    vint32_t;       /**< Volatile signed 32 bits.   */
typedef volatile uint32_t   vuint32_t;      /**< Volatile unsigned 32 bits. */
typedef volatile uint64_t   vuint64_t;      /**< Volatile unsigned 64 bits. */

/*
 * Special-purpose register (SPRs) interface
 */ 
#ifdef __ghs__
/*
 * Green Hills compiler part
 */
#include <ppc_ghs.h>
/* Write to SPR registers */
#define wrspr(spr_id,value) __MTSPR(spr_id, value)
/* Read from SPR registers */
#define rdspr(spr_id,value) value = __MFSPR(spr_id)
/* Full sync */
#define fsync() __ISYNC()

#else
/*
 * FreeGCC and Hightec compilers part
 */
#define from2str(s) str2val(s)
#define str2val(s) #s

/* Write to SPR registers */
#define wrspr(spr_id, value) asm volatile("mtspr " str2val(spr_id) ",%0" : : "r" (value))

/* Read from SPR registers */
#define rdspr(spr_id, value) asm volatile("mfspr %0," str2val(spr_id) : "=r" (value))

/* Full sync */
#define fsync()	asm volatile("msync \n\t isync \n\t": : : "memory")

#endif /* __ghs__ */

#endif /* _TYPEDEFS_H_ */
