/*******************************************************************************
 * Copyright (c) 2013-2016 Realtek Semiconductor Corp, All Rights Reserved
 *
 * SPDX-License-Identifier: LicenseRef-PBL
 *
 * Licensed under the Permissive Binary License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at https://www.mbed.com/licenses/PBL-1.0
 *
 * See the License for the specific language governing permissions and limitations
 * under the License.
 *******************************************************************************
 */

#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_
#include "basic_types.h"
#include "hal_platform.h"
#include "rtl8195a_timer.h"

#define GTIMER_CLK_HZ           (32768)
#define GTIMER_TICK_US          (1000000/GTIMER_CLK_HZ)

enum _TIMER_MODE_ {
    FREE_RUN_MODE = 0,
    USER_DEFINED = 1
};
typedef uint32_t TIMER_MODE;
typedef uint32_t *PTIMER_MODE;

typedef struct _TIMER_ADAPTER_ {
    u32         TimerLoadValueUs;
    u32         TimerIrqPriority;
    TIMER_MODE  TimerMode;
    IRQ_HANDLE  IrqHandle;
    u8          TimerId;
    u8          IrqDis;
} TIMER_ADAPTER, *PTIMER_ADAPTER;

typedef struct _HAL_TIMER_OP_ {
    u32  (*HalGetTimerId)(u32 *TimerId);
    BOOL (*HalTimerInit)(void *Data);
    u32  (*HalTimerReadCount)(u32 TimerId);
    void (*HalTimerIrqClear)(u32 TimerId);
    void (*HalTimerDis)(u32 TimerId);
    void (*HalTimerEn)(u32 TimerId);
    void (*HalTimerDumpReg)(u32 TimerId);
} HAL_TIMER_OP, *PHAL_TIMER_OP;

typedef struct _HAL_TIMER_OP_EXT_ {
    PHAL_TIMER_OP phal_timer_op_rom;
    void (*HalTimerIrqEn)(u32 TimerId);
    void (*HalTimerReLoad)(u32 TimerId, u32 LoadUs);
    void (*HalTimerSync)(u32 TimerId);
} HAL_TIMER_OP_EXT, *PHAL_TIMER_OP_EXT;

#ifdef CONFIG_TIMER_MODULE
// This variable declared in ROM code
extern HAL_TIMER_OP HalTimerOp;
extern HAL_TIMER_OP_EXT HalTimerOpExt;
#endif

void HalTimerOpInit_Patch(void *Data);

//======================================================
// ROM Function prototype
_LONG_CALL_ void HalTimerOpInitV02(void *Data);

#ifdef CONFIG_RELEASE_BUILD_LIBRARIES
void HalTimerOpInit(void *Data);
HAL_Status HalTimerInit(void *Data);
void HalTimerEnable(uint32_t TimerId);
void HalTimerDisable(uint32_t TimerId);
void HalTimerReLoad(uint32_t TimerId, uint32_t LoadUs);
void HalTimerDeInit(void *Data);
#else
#define HalTimerOpInit      HalTimerOpInit_Patch
#endif

#endif
