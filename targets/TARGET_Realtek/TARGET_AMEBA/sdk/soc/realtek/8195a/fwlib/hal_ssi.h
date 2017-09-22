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

#ifndef _HAL_SSI_H_
#define _HAL_SSI_H_

#include "rtl8195a_ssi.h"

/**
 * LOG Configurations
 */

extern u32 SSI_DBG_CONFIG;

#define SSI_DBG_ENTRANCE(...) do {                                                    \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_ENTRANCE)) {                               \
        DBG_SSI_INFO(IDENT_FOUR_SPACE ANSI_COLOR_GREEN __VA_ARGS__ ANSI_COLOR_RESET); \
    }                                                                                 \
} while(0)

#define SSI_DBG_INIT(...) do {                           \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT)) {      \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_INIT_V(...) do {                         \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT_V)) {    \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_INIT_VV(...) do {                        \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT_VV)) {   \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_PINMUX(...) do {                         \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_PINMUX)) {    \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_ENDIS(...) do {                          \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_ENDIS))       \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_INT(...) do {                            \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT)) {       \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_INT_V(...) do {                          \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_V)) {     \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_INT_HNDLR(...) do {                      \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_HNDLR)) { \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_INT_READ(...) do {                       \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_READ)) {  \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_INT_WRITE(...) do {                      \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_WRITE)) { \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_STATUS(...)  do {                        \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_STATUS))      \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_FIFO(...) do {                           \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_FIFO)) {      \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_READ(...)  do {                          \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_READ)) {      \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_WRITE(...)  do {                         \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_WRITE)) {     \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

#define SSI_DBG_SLV_CTRL(...)  do {                      \
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_SLV_CTRL)) {  \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__);      \
    }                                                    \
} while(0)

enum _SSI_DBG_TYPE_LIST_ {
    DBG_TYPE_ENTRANCE  = 1 << 0,
    DBG_TYPE_INIT      = 1 << 1,
    DBG_TYPE_INIT_V    = 1 << 2,
    DBG_TYPE_INIT_VV   = 1 << 3,
    DBG_TYPE_PINMUX    = 1 << 4,
    DBG_TYPE_ENDIS     = 1 << 5,
    DBG_TYPE_INT       = 1 << 6,
    DBG_TYPE_INT_V     = 1 << 7,
    DBG_TYPE_INT_HNDLR = 1 << 8,
    DBG_TYPE_INT_READ  = 1 << 9,
    DBG_TYPE_INT_WRITE = 1 << 10,
    DBG_TYPE_STATUS    = 1 << 11,
    DBG_TYPE_FIFO      = 1 << 12,
    DBG_TYPE_READ      = 1 << 13,
    DBG_TYPE_WRITE     = 1 << 14,
    DBG_TYPE_SLV_CTRL  = 1 << 15
};
typedef uint32_t SSI_DBG_TYPE_LIST;
typedef uint32_t *PSSI_DBG_TYPE_LIST;

typedef struct _SSI_DMA_CONFIG_ {
    void *pHalGdmaOp;
    void *pTxHalGdmaAdapter;
    void *pRxHalGdmaAdapter;
    u8    RxDmaBurstSize;
    u8    TxDmaBurstSize;
    u8    RxDmaEnable;
    u8    TxDmaEnable;
    IRQ_HANDLE RxGdmaIrqHandle;
    IRQ_HANDLE TxGdmaIrqHandle;
} SSI_DMA_CONFIG, *PSSI_DMA_CONFIG;

#if CONFIG_GDMA_EN
typedef struct _HAL_SSI_DMA_MULTIBLK_ {
    volatile GDMA_CH_LLI_ELE GdmaChLli[16];
    struct GDMA_CH_LLI Lli[16];
    struct BLOCK_SIZE_LIST BlockSizeList[16];
} SSI_DMA_MULTIBLK, *PSSI_DMA_MULTIBLK;
#endif
/**
 *DesignWare SSI Configurations
 */
typedef struct _HAL_SSI_ADAPTOR_ {
    SSI_DMA_CONFIG DmaConfig;
    IRQ_HANDLE IrqHandle;
    //
    void (*RxCompCallback)(void *Para);
    void *RxCompCbPara;
    void *RxData;
    void (*TxCompCallback)(void *Para);
    void *TxCompCbPara;
    void *TxData;
    u32  DmaRxDataLevel;
    u32  DmaTxDataLevel;
    u32  InterruptPriority;
    u32  RxLength;
    u32  RxLengthRemainder;
    u32  RxThresholdLevel;
    u32  TxLength;
    u32  TxThresholdLevel;
    u32  SlaveSelectEnable;
    //
    u16  ClockDivider;
    u16  DataFrameNumber;
    //
    u8   ControlFrameSize;
    u8   DataFrameFormat;
    u8   DataFrameSize;
    u8   DmaControl;
    u8   Index;
    u8   InterruptMask;
    u8   MicrowireDirection;
    u8   MicrowireHandshaking;
    u8   MicrowireTransferMode;
    u8   PinmuxSelect;
    u8   Role;
    u8   SclkPhase;
    u8   SclkPolarity;
    u8   SlaveOutputEnable;
    u8   TransferMode;
    u8   TransferMechanism;

    // Extend
    u8 Reserve;
    u8 HaveTxChannel;
    u8 HaveRxChannel;
    u8 DefaultRxThresholdLevel;
    #if CONFIG_GDMA_EN
    SSI_DMA_MULTIBLK DmaTxMultiBlk, DmaRxMultiBlk;
    #endif
    u32 ReservedDummy;
    void (*TxIdleCallback)(void *Para);
    void *TxIdleCbPara;
} HAL_SSI_ADAPTOR, *PHAL_SSI_ADAPTOR;

typedef struct _HAL_SSI_OP_ {
    HAL_Status (*HalSsiPinmuxEnable)(void *Adaptor);
    HAL_Status (*HalSsiPinmuxDisable)(void *Adaptor);
    HAL_Status (*HalSsiEnable)(void *Adaptor);
    HAL_Status (*HalSsiDisable)(void *Adaptor);
    HAL_Status (*HalSsiInit)(void *Adaptor);
    HAL_Status (*HalSsiSetSclkPolarity)(void *Adaptor);
    HAL_Status (*HalSsiSetSclkPhase)(void *Adaptor);
    HAL_Status (*HalSsiWrite)(void *Adaptor, u32 value);
    HAL_Status (*HalSsiLoadSetting)(void *Adaptor, void *Setting);
    HAL_Status (*HalSsiSetInterruptMask)(void *Adaptor);
    HAL_Status (*HalSsiSetDeviceRole)(void *Adaptor, u32 Role);
    HAL_Status (*HalSsiInterruptEnable)(void *Adaptor);
    HAL_Status (*HalSsiInterruptDisable)(void *Adaptor);
    HAL_Status (*HalSsiReadInterrupt)(void *Adaptor, void *RxData, u32 Length);
    HAL_Status (*HalSsiSetRxFifoThresholdLevel)(void *Adaptor);
    HAL_Status (*HalSsiSetTxFifoThresholdLevel)(void *Adaptor);
    HAL_Status (*HalSsiWriteInterrupt)(void *Adaptor, u8 *TxData, u32 Length);
    HAL_Status (*HalSsiSetSlaveEnableRegister)(void *Adaptor, u32 SlaveIndex);
    u32  (*HalSsiBusy)(void *Adaptor);
    u32  (*HalSsiReadable)(void *Adaptor);
    u32  (*HalSsiWriteable)(void *Adaptor);
    u32  (*HalSsiGetInterruptMask)(void *Adaptor);
    u32  (*HalSsiGetRxFifoLevel)(void *Adaptor);
    u32  (*HalSsiGetTxFifoLevel)(void *Adaptor);
    u32  (*HalSsiGetStatus)(void *Adaptor);
    u32  (*HalSsiGetInterruptStatus)(void *Adaptor);
    u32  (*HalSsiRead)(void *Adaptor);
    u32  (*HalSsiGetRawInterruptStatus)(void *Adaptor);
    u32  (*HalSsiGetSlaveEnableRegister)(void *Adaptor);
} HAL_SSI_OP, *PHAL_SSI_OP;

typedef struct _DW_SSI_DEFAULT_SETTING_ {
    void (*RxCompCallback)(void *Para);
    void *RxCompCbPara;
    void *RxData;
    void (*TxCompCallback)(void *Para);
    void *TxCompCbPara;
    void *TxData;
    u32  DmaRxDataLevel;
    u32  DmaTxDataLevel;
    u32  InterruptPriority;
    u32  RxLength;
    u32  RxLengthRemainder;
    u32  RxThresholdLevel;
    u32  TxLength;
    u32  TxThresholdLevel;
    u32  SlaveSelectEnable;
    //
    u16  ClockDivider;
    u16  DataFrameNumber;
    //
    u8   ControlFrameSize;
    u8   DataFrameFormat;
    u8   DataFrameSize;
    u8   DmaControl;
    //u8   Index;
    u8   InterruptMask;
    u8   MicrowireDirection;
    u8   MicrowireHandshaking;
    u8   MicrowireTransferMode;
    //u8   PinmuxSelect;
    //u8   Role;
    u8   SclkPhase;
    u8   SclkPolarity;
    u8   SlaveOutputEnable;
    u8   TransferMode;
    u8   TransferMechanism;
} DW_SSI_DEFAULT_SETTING, *PDW_SSI_DEFAULT_SETTING;


struct spi_s {
    HAL_SSI_ADAPTOR spi_adp;
    HAL_SSI_OP      spi_op;
    u32 irq_handler;
    u32 irq_id;
    u32 dma_en;
    volatile u32 state;
    u8 sclk;
#if CONFIG_GDMA_EN
    HAL_GDMA_ADAPTER spi_gdma_adp_tx;
    HAL_GDMA_ADAPTER spi_gdma_adp_rx;
#endif
    u32 bus_tx_done_handler;
    u32 bus_tx_done_irq_id;
};

extern void HalSsiOpInit(void *Adaptor);

static __inline__ void HalSsiSetSclk(PHAL_SSI_ADAPTOR pHalSsiAdapter, u32 ClkRate)
{
    HalSsiSetSclkRtl8195a((void*)pHalSsiAdapter, ClkRate);
}

HAL_Status HalSsiInit(void *Data);
HAL_Status HalSsiDeInit(void *Data);
HAL_Status HalSsiEnable(void *Data);
HAL_Status HalSsiDisable(void *Data);
HAL_Status HalSsiEnterCritical(void *Data);
HAL_Status HalSsiExitCritical(void *Data);
HAL_Status HalSsiTimeout(u32 StartCount, u32 TimeoutCnt);
HAL_Status HalSsiStopRecv(void *Data);
HAL_Status HalSsiSetFormat(void *Data);
void HalSsiClearFIFO(void *Data);
#if CONFIG_GDMA_EN
HAL_Status HalSsiTxGdmaInit(PHAL_SSI_OP pHalSsiOp, PHAL_SSI_ADAPTOR pHalSsiAdapter);
void HalSsiTxGdmaDeInit(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_Status HalSsiRxGdmaInit(PHAL_SSI_OP pHalSsiOp, PHAL_SSI_ADAPTOR pHalSsiAdapter);
void HalSsiRxGdmaDeInit(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_Status HalSsiRxMultiBlkChnl(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_Status HalSsiDmaRecv(void *Adapter, u8 *pRxData, u32 Length);
HAL_Status HalSsiDmaSend(void *Adapter, u8 *pTxData, u32 Length);

static __inline__ void HalSsiDmaInit(PHAL_SSI_ADAPTOR pHalSsiAdapter)
{
#if CONFIG_CHIP_E_CUT
    HalSsiDmaInitRtl8195a_V04((void *)pHalSsiAdapter);
#else
    HalSsiDmaInitRtl8195a((void *)pHalSsiAdapter);
#endif
}
#endif

#endif
