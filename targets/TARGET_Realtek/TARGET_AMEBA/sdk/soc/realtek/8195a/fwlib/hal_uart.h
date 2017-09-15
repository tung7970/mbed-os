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

#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#include "rtl8195a_uart.h"

/**
 * RUART Configurations
 */
#define UART_WAIT_FOREVER       0xffffffff

#define UART_DMA_MBLK_NUM       16      // maximum block number for each DMA transfer, it must <= 16
#define UART_DMA_BLOCK_SIZE     4092    // the block size of multiple block DMA, it cann0t over 4095

typedef struct _HAL_UART_DMA_MULTIBLK_ {
    volatile GDMA_CH_LLI_ELE GdmaChLli[UART_DMA_MBLK_NUM];
    struct GDMA_CH_LLI Lli[UART_DMA_MBLK_NUM];
    struct BLOCK_SIZE_LIST BlockSizeList[UART_DMA_MBLK_NUM];
} UART_DMA_MULTIBLK, *PUART_DMA_MULTIBLK;

typedef struct _UART_DMA_CONFIG_ {
    u8 TxDmaEnable;
    u8 RxDmaEnable;
    u8 TxDmaBurstSize;
    u8 RxDmaBurstSize;
    void *pHalGdmaOp;
    void *pTxHalGdmaAdapter;
    void *pRxHalGdmaAdapter;
    IRQ_HANDLE TxGdmaIrqHandle;
    IRQ_HANDLE RxGdmaIrqHandle;
#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
    UART_DMA_MULTIBLK *pTxDmaBlkList;       // point to multi-block list
    UART_DMA_MULTIBLK *pRxDmaBlkList;       // point to multi-block list
    u8 TxDmaMBChnl;     // is using DMA multiple block channel
    u8 RxDmaMBChnl;     // is using DMA multiple block channel
#endif
} UART_DMA_CONFIG, *PUART_DMA_CONFIG;

typedef struct _HAL_RUART_ADAPTER_ {
    u32 BaudRate;
    u32 FlowControl;
    u32 FifoControl;
    u32 Interrupts;
    u32 TxCount;     // how many byte to TX
    u32 RxCount;     // how many bytes to RX
    u8 *pTxBuf;
    u8 *pRxBuf;
    HAL_UART_State State;       // UART state
    u8 Status;      // Transfer Status
    u8 Locked;      // is UART locked for operation
    u8 UartIndex;
    u8 WordLen;     // word length select: 0 -> 7 bits, 1 -> 8 bits
    u8 StopBit;     // word length select: 0 -> 1 stop bit, 1 -> 2 stop bit
    u8 Parity;      // parity check enable
    u8 ParityType;  // parity check type
    u8 StickParity;
    u8 ModemStatus; // the modem status
    u8 DmaEnable;
    u8 TestCaseNumber;
    u8 PinmuxSelect;
    BOOL PullMode;
    IRQ_HANDLE IrqHandle;
    PUART_DMA_CONFIG DmaConfig;
    void (*ModemStatusInd)(void *pAdapter);    // modem status indication interrupt handler
    void (*TxTDCallback)(void *pAdapter);      // User Tx Done callback function
    void (*RxDRCallback)(void *pAdapter);      // User Rx Data ready callback function
    void (*TxCompCallback)(void *para);    // User Tx complete callback function
    void (*RxCompCallback)(void *para);    // User Rx complete callback function
    void *TxTDCbPara;   // the pointer agrument for TxTDCallback
    void *RxDRCbPara;   // the pointer agrument for RxDRCallback
    void *TxCompCbPara; // the pointer argument for TxCompCbPara
    void *RxCompCbPara; // the pointer argument for RxCompCallback
    void (*EnterCritical)(void);
    void (*ExitCritical)(void);

#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
    //1 New member only can be added below: members above must be fixed for ROM code
    u32 *pDefaultBaudRateTbl;      // point to the table of pre-defined baud rate
    u8 *pDefaultOvsrRTbl;         // point to the table of OVSR for pre-defined baud rate
    u16 *pDefaultDivTbl;           // point to the table of DIV for pre-defined baud rate
    u8  *pDefOvsrAdjBitTbl_10;     // point to the table of OVSR-Adj bits for 10 bits
    u8  *pDefOvsrAdjBitTbl_9;     // point to the table of OVSR-Adj bits for 9 bits
    u8  *pDefOvsrAdjBitTbl_8;     // point to the table of OVSR-Adj bits for 8 bits
    u16 *pDefOvsrAdjTbl_10;       // point to the table of OVSR-Adj for pre-defined baud rate
    u16 *pDefOvsrAdjTbl_9;       // point to the table of OVSR-Adj for pre-defined baud rate
    u16 *pDefOvsrAdjTbl_8;       // point to the table of OVSR-Adj for pre-defined baud rate
    PUART_DMA_MULTIBLK pTxDMAMBlk;  // point to the Link List Table of the DMA Multiple Block
    PUART_DMA_MULTIBLK pRxDMAMBlk;  // point to the Link List Table of the DMA Multiple Block
    u32 BaudRateUsing;             // Current using Baud-Rate
    u8 WordLenUsing;             // Current using Word Length
    u8 ParityUsing;             // Current using Parity check
    u8 RTSCtrl;               // Software RTS Control
#endif
} HAL_RUART_ADAPTER, *PHAL_RUART_ADAPTER;

typedef struct _HAL_RUART_OP_ {
    void (*HalRuartAdapterLoadDef)(void *pAdp, u8 UartIdx);    // Load UART adapter default setting
    void (*HalRuartTxGdmaLoadDef)(void *pAdp, void *pCfg);     // Load TX GDMA default setting
    void (*HalRuartRxGdmaLoadDef)(void *pAdp, void *pCfg);     // Load RX GDMA default setting
    HAL_Status (*HalRuartResetRxFifo)(void *Data);
    HAL_Status (*HalRuartInit)(void *Data);
    void (*HalRuartDeInit)(void *Data);
    HAL_Status (*HalRuartPutC)(void *Data, u8 TxData);
    u32  (*HalRuartSend)(void *Data, u8 *pTxData, u32 Length, u32 Timeout);
    HAL_Status  (*HalRuartIntSend)(void *Data, u8 *pTxData, u32 Length);
    HAL_Status  (*HalRuartDmaSend)(void *Data, u8 *pTxData, u32 Length);
    HAL_Status  (*HalRuartStopSend)(void *Data);
    HAL_Status (*HalRuartGetC)(void *Data, u8 *pRxByte);
    u32  (*HalRuartRecv)(void *Data, u8  *pRxData, u32 Length, u32 Timeout);
    HAL_Status  (*HalRuartIntRecv)(void *Data, u8  *pRxData, u32 Length);
    HAL_Status  (*HalRuartDmaRecv)(void *Data, u8  *pRxData, u32 Length);
    HAL_Status  (*HalRuartStopRecv)(void *Data);
    u8   (*HalRuartGetIMR)(void *Data);
    void (*HalRuartSetIMR)(void *Data);
    u32  (*HalRuartGetDebugValue)(void *Data, u32 DbgSel);
    void (*HalRuartDmaInit)(void *Data);
    void (*HalRuartRTSCtrl)(void *Data, BOOLEAN RtsCtrl);
    void (*HalRuartRegIrq)(void *Data);
    void (*HalRuartIntEnable)(void *Data);
    void (*HalRuartIntDisable)(void *Data);
} HAL_RUART_OP, *PHAL_RUART_OP;

typedef struct _RUART_DATA_ {
    PHAL_RUART_ADAPTER pHalRuartAdapter;
    BOOL PullMode;
    u8   BinaryData;
    u8   SendBuffer;
    u8   RecvBuffer;
} RUART_DATA, *PRUART_DATA;

typedef struct _RUART_ADAPTER_ {
    PHAL_RUART_OP      pHalRuartOp;
    PHAL_RUART_ADAPTER pHalRuartAdapter;
    PUART_DMA_CONFIG   pHalRuartDmaCfg;
} RUART_ADAPTER, *PRUART_ADAPTER;

extern void HalRuartOpInit(void *Data);

extern HAL_Status
HalRuartTxGdmaInit(
    PHAL_RUART_ADAPTER pHalRuartAdapter,
    PUART_DMA_CONFIG pUartGdmaConfig,
    u8 IsMultiBlk
);

extern void HalRuartTxGdmaDeInit(PUART_DMA_CONFIG pUartGdmaConfig);
extern HAL_Status
HalRuartRxGdmaInit(
    PHAL_RUART_ADAPTER pHalRuartAdapter,
    PUART_DMA_CONFIG pUartGdmaConfig,
    u8 IsMultiBlk
);

extern void HalRuartRxGdmaDeInit(PUART_DMA_CONFIG pUartGdmaConfig);
extern HAL_Status HalRuartResetTxFifo(void *Data);
extern HAL_Status HalRuartResetRxFifo(void *Data);
HAL_Status HalRuartResetTRxFifo(void *Data);
extern HAL_Status HalRuartSetBaudRate(void *Data);
extern HAL_Status HalRuartInit(void *Data);
extern void HalRuartDeInit(void *Data);
extern HAL_Status HalRuartDisable(void *Data);
extern HAL_Status HalRuartEnable(void *Data);
HAL_Status HalRuartFlowCtrl(void *Data);
void HalRuartEnterCritical(void *Data);
void HalRuartExitCritical(void *Data);
HAL_Status HalRuartDmaSend(void *Data, u8 *pTxBuf, u32 Length);
HAL_Status HalRuartDmaRecv(void *Data, u8 *pRxBuf, u32 Length);

extern const HAL_RUART_OP _HalRuartOp;
extern HAL_Status RuartLock (PHAL_RUART_ADAPTER pHalRuartAdapter);
extern void RuartUnLock (PHAL_RUART_ADAPTER pHalRuartAdapter);

#endif
