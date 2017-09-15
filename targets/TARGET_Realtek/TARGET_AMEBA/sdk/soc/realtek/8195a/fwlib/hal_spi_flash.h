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

#ifndef _HAL_SPIFLASH__
#define _HAL_SPIFLASH__

#define SPIC_CALIBRATION_IN_NVM         1   // if store the SPIC calibration data in the NVM
#ifndef CONFIG_IMAGE_SEPARATE               // Store SPIC Calibration only for seprated image
#undef SPIC_CALIBRATION_IN_NVM
#define SPIC_CALIBRATION_IN_NVM         0
#endif

//======================================================
// Definition
#define HAL_SPI_WRITE32(addr, value32)  HAL_WRITE32(SPI_FLASH_CTRL_BASE, addr, value32)
#define HAL_SPI_WRITE16(addr, value16)  HAL_WRITE16(SPI_FLASH_CTRL_BASE, addr, value16)
#define HAL_SPI_WRITE8(addr, value8)    HAL_WRITE8(SPI_FLASH_CTRL_BASE, addr, value8)
#define HAL_SPI_READ32(addr)            HAL_READ32(SPI_FLASH_CTRL_BASE, addr)
#define HAL_SPI_READ16(addr)            HAL_READ16(SPI_FLASH_CTRL_BASE, addr)
#define HAL_SPI_READ8(addr)             HAL_READ8(SPI_FLASH_CTRL_BASE, addr)

typedef struct _SPIC_PARA_MODE_ {
    u8 Valid:1;       // valid
    u8 CpuClk:3;      // CPU clock
    u8 BitMode:2;     // Bit mode
    u8 Reserved:2;    // reserved
} SPIC_PARA_MODE, *PSPIC_PARA_MODE;

typedef struct _SPIC_INIT_PARA_ {
    u8  BaudRate;
    u8  RdDummyCyle;
    u8  DelayLine;
    union {
        u8  Rsvd;
        u8  Valid;
        SPIC_PARA_MODE Mode;
    };
#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
    u8 id[3];
    u8 flashtype;
#endif
} SPIC_INIT_PARA, *PSPIC_INIT_PARA;

enum _SPIC_BIT_MODE_ {
    SpicOneBitMode = 0,
    SpicDualBitMode = 1,
    SpicQuadBitMode = 2,
};

//======================================================
// Flash type used
#define FLASH_OTHERS 0
#define FLASH_MXIC 1
#define FLASH_MXIC_4IO 2
#define FLASH_WINBOND 3
#define FLASH_MICRON 4
#define FLASH_EON 5

// The below parts are based on the flash characteristics
//====== Flash Command Definition  ======
/*Common command*/
#define FLASH_CMD_WREN      0x06            //write enable
#define FLASH_CMD_WRDI      0x04            //write disable
#define FLASH_CMD_WRSR      0x01            //write status register
#define FLASH_CMD_RDID      0x9F            //read idenfication
#define FLASH_CMD_RDSR      0x05            //read status register
#define FLASH_CMD_RDSFDP    0x5A            //Read SFDP
#define FLASH_CMD_READ      0x03            //read data
#define FLASH_CMD_FREAD     0x0B            //fast read data
#define FLASH_CMD_PP        0x02            //Page Program
#define FLASH_CMD_DREAD     0x3B            //Double Output Mode command 1-1-2
#define FLASH_CMD_2READ     0xBB            // 2 x I/O read  command 1-2-2
#define FLASH_CMD_QREAD     0x6B            // 1I / 4O read command 1-1-4
#define FLASH_CMD_4READ     0xEB            // 4 x I/O read  command 1-4-4
#define FLASH_CMD_DPP       0xA2            // 1-1-2
#define FLASH_CMD_2PP       0xD2            //  1-2-2
#define FLASH_CMD_QPP       0x32            //  1-1-4
#define FLASH_CMD_4PP       0x38            //quad page program 1-4-4
#define FLASH_CMD_SE        0x20            //Sector Erase
#define FLASH_CMD_BE        0xD8            //Block Erase(or 0x52)
#define FLASH_CMD_CE        0xC7            //Chip Erase(or 0xC7)
#define FLASH_CMD_DP        0xB9            //Deep Power Down
#define FLASH_CMD_RDP       0xAB            //Release from Deep Power-Down

/*Micron Special command*/
#define FLASH_CMD_DE        0xC4
#define FLASH_CMD_4PP2      0x12
#define FLASH_CMD_RFSR      0x70
#define FLASH_CMD_CFSR      0x50
#define FLASH_CMD_RNCR      0xB5
#define FLASH_CMD_WNCR      0xB1
#define FLASH_CMD_RVCR      0x85
#define FLASH_CMD_WVCR      0x81
#define FLASH_CMD_REVCR     0x65
#define FLASH_CMD_WEVCR     0x61
#define FLASH_CMD_REAR      0xC8
#define FLASH_CMD_WEAR      0xC5
#define FLASH_CMD_ENQUAD    0x35
#define FLASH_CMD_EXQUAD    0xF5

/*MXIC Special command*/
#define FLASH_CMD_RDCR      0x15        //read configurate register
#define FLASH_CMD_REMS2     0xEF            // read ID for 2x I/O mode
#define FLASH_CMD_REMS4     0xDF            // read ID for 4x I/O mode
#define FLASH_CMD_ENSO      0xB1            // enter secured OTP
#define FLASH_CMD_EXSO      0xC1            // exit secured OTP
#define FLASH_CMD_RDSCUR    0x2B            // read security register
#define FLASH_CMD_WRSCUR    0x2F            // write security register

// =====  Flash Parameter Definition  =====
#define FLASH_DM_CYCLE_2O   0x08 // 1-1-2
#define FLASH_DM_CYCLE_2IO  0x04 // 1-2-2
#define FLASH_DM_CYCLE_4O   0x08 // 1-1-4
#define FLASH_DM_CYCLE_4IO  0x08 // 1-4-4
#define FLASH_VLD_DUAL_CMDS  (BIT_WR_BLOCKING | BIT_RD_DUAL_I)  // 1-1-2
#define FLASH_VLD_QUAD_CMDS  (BIT_WR_BLOCKING | BIT_RD_QUAD_IO) // 1-4-4
#define FLASH_VLD_QUAD_CMDS2 (BIT_WR_BLOCKING | BIT_RD_QUAD_O)  // 1-1-4

//======================================================
// ROM Function prototype
_LONG_CALL_ void SpiFlashAppV02(void *Data);
_LONG_CALL_ROM_ void SpicInitRtl8195AV02(u8 InitBaudRate, u8 SpicBitMode);
_LONG_CALL_ROM_ void SpicEraseFlashRtl8195AV02(void);
_LONG_CALL_ROM_ void SpicLoadInitParaFromClockRtl8195AV02(u8 CpuClkMode, u8 BaudRate, PSPIC_INIT_PARA pSpicInitPara);

void SpicBlockEraseFlashRtl8195A(u32 Address);
void SpicSectorEraseFlashRtl8195A(u32 Address);
void SpicDieEraseFlashRtl8195A(u32 Address);
void SpicWriteProtectFlashRtl8195A(u32 Protect);
void SpicWaitWipDoneRefinedRtl8195A(SPIC_INIT_PARA SpicInitPara);
void SpicWaitOperationDoneRtl8195A(SPIC_INIT_PARA SpicInitPara);
void SpicRxCmdRefinedRtl8195A(u8 cmd,SPIC_INIT_PARA SpicInitPara);
u8 SpicGetFlashStatusRefinedRtl8195A(SPIC_INIT_PARA SpicInitPara);
void SpicInitRefinedRtl8195A(u8 InitBaudRate,u8 SpicBitMode);
u32 SpicWaitWipRtl8195A(void);
u32 SpicOneBitCalibrationRtl8195A(u8 SysCpuClk);
void SpicDisableRtl8195A(void);
void SpicDeepPowerDownFlashRtl8195A(void);
void SpicUserProgramRtl8195A(u8 * data, SPIC_INIT_PARA SpicInitPara, u32 addr, u32 * LengthInfo);
void SpicUserReadRtl8195A(u32 Length, u32 addr, u8 * data, u8 BitMode);
void SpicUserReadFourByteRtl8195A(u32 Length, u32 addr, u32 * data, u8 BitMode);
void SpicReadIDRtl8195A(void);
void SpicSetFlashStatusRefinedRtl8195A(u32 data, SPIC_INIT_PARA SpicInitPara);
void SpicSetExtendAddrRtl8195A(u32 data, SPIC_INIT_PARA SpicInitPara);
u8 SpicGetExtendAddrRtl8195A(SPIC_INIT_PARA SpicInitPara);
#if SPIC_CALIBRATION_IN_NVM
void SpicNVMCalLoad(u8 BitMode, u8 CpuClk);
void SpicNVMCalLoadAll(void);
void SpicNVMCalStore(u8 BitMode, u8 CpuClk);
#endif

#endif //_HAL_SPIFLASH__
