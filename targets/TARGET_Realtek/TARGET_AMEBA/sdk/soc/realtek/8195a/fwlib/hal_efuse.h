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
#ifndef _HAL_EFUSE_H_
#define _HAL_EFUSE_H_

extern _LONG_CALL_ROM_ void HalEFUSEPowerSwitch8195AROM(u8 bWrite, u8 PwrState, u8 L25OutVoltage);
extern u32 HALEFUSEOneByteReadRAM(u32 CtrlSetting, u16 Addr, u8 *Data, u8 L25OutVoltage);
extern u32 HALEFUSEOneByteWriteRAM(u32 CtrlSetting, u16 Addr, u8 Data, u8 L25OutVoltage);

#define EFUSERead8     HALEFUSEOneByteReadRAM
#define EFUSEWrite8    HALEFUSEOneByteWriteRAM

#define L25EOUTVOLTAGE    7
#endif
