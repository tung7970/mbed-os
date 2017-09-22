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
#ifndef _HAL_DAC_H_
#define _HAL_DAC_H_

#include "rtl8195a.h"
#include "hal_api.h"
#include "hal_gdma.h"

//================ DAC Configuration  =========================
#define DAC_INTR_OP_TYPE     1
#define DAC_DMA_OP_TYPE      1

// DAC SAL management macros
#define SAL_DAC_USER_CB_NUM  (sizeof(SAL_DAC_USER_CB) / sizeof(PSAL_DAC_USERCB_ADPT))

// DAC SAL used module.
// Please set the DAC module flag to 1 to enable the related DAC module functions.
#define DAC0_USED            1
#define DAC1_USED            1


//================ Debug MSG Definition =======================
#define DAC_PREFIX      "RTL8195A[dac]: "
#define DAC_PREFIX_LVL  "    [DAC_DBG]: "

enum _DAC_DBG_LVL_ {
    HAL_DAC_LVL  = 0x00,
    SAL_DAC_LVL  = 0x02,
    VERI_DAC_LVL = 0x04,
};
typedef uint32_t DAC_DBG_LVL;
typedef uint32_t * PDAC_DBG_LVL;

#if defined(CONFIG_DEBUG_LOG) && defined(CONFIG_DEBUG_LOG_DAC_HAL)
#  define DBG_8195A_DAC(...)                           \
     do {                                              \
        _DbgDump("\r"DAC_PREFIX __VA_ARGS__);          \
     } while(0)

#  define DACDBGLVL   0xFF
#  define DBG_8195A_DAC_LVL(LVL,...)                   \
     do {                                              \
         if (LVL&DACDBGLVL) {                          \
             _DbgDump("\r"DAC_PREFIX_LVL __VA_ARGS__); \
         }                                             \
    } while(0)
#else
#  define DBG_DAC_LOG_PERD    100
#  define DBG_8195A_DAC(...)
#  define DBG_8195A_DAC_LVL(...)
#endif


//================ DAC HAL Related Enumeration ==================
// DAC Module Selection
enum _DAC_MODULE_SEL_ {
    DAC0_SEL = 0x0,
    DAC1_SEL = 0x1,
};
typedef uint32_t DAC_MODULE_SEL;
typedef uint32_t *PDAC_MODULE_SEL;

// DAC module status
enum _DAC_MODULE_STATUS_ {
    DAC_DISABLE = 0x0,
    DAC_ENABLE  = 0x1,
};
typedef uint32_t DAC_MODULE_STATUS;
typedef uint32_t *PDAC_MODULE_STATUS;

// DAC Data Rate
enum _DAC_DATA_RATE_ {
    DAC_DATA_RATE_10K  = 0x0,
    DAC_DATA_RATE_250K = 0x1,
};
typedef uint32_t DAC_DATA_RATE;
typedef uint32_t *PDAC_DATA_RATE;

// DAC Data Endian
enum _DAC_DATA_ENDIAN_ {
    DAC_DATA_ENDIAN_LITTLE = 0x0,
    DAC_DATA_ENDIAN_BIG    = 0x1,
};
typedef uint32_t DAC_DATA_ENDIAN;
typedef uint32_t * PDAC_DATA_ENDIAN;

// DAC Debug Select
enum _DAC_DEBUG_SEL_ {
    DAC_DBG_SEL_DISABLE = 0x0,
    DAC_DBG_SEL_ENABLE  = 0x1,
};
typedef uint32_t DAC_DEBUG_SEL;
typedef uint32_t *PDAC_DEBUG_SEL;

// DAC Dsc Debug Select
enum _DAC_DSC_DEBUG_SEL_ {
    DAC_DSC_DBG_SEL_DISABLE = 0x0,
    DAC_DSC_DBG_SEL_ENABLE  = 0x1,
};
typedef uint32_t DAC_DSC_DEBUG_SEL;
typedef uint32_t *PDAC_DSC_DEBUG_SEL;

// DAC Bypass Dsc Debug Select
enum _DAC_BYPASS_DSC_SEL_ {
    DAC_BYPASS_DSC_SEL_DISABLE = 0x0,
    DAC_BYPASS_DSC_SEL_ENABLE  = 0x1,
};
typedef uint32_t DAC_BYPASS_DSC_SEL;
typedef uint32_t *PDAC_BYPASS_DSC_SEL;

// DAC feature status
enum _DAC_FEATURE_STATUS_ {
    DAC_FEATURE_DISABLED = 0,
    DAC_FEATURE_ENABLED  = 1,
};
typedef uint32_t DAC_FEATURE_STATUS;
typedef uint32_t * PDAC_FEATURE_STATUS;

// DAC operation type
enum _DAC_OP_TYPE_ {
    DAC_POLL_TYPE = 0x0,
    DAC_DMA_TYPE  = 0x1,
    DAC_INTR_TYPE = 0x2,
};
typedef uint32_t DAC_OP_TYPE;
typedef uint32_t *PDAC_OP_TYPE;

// DAC device status
enum _DAC_Device_STATUS_ {
    DAC_STS_UNINITIAL   = 0x00,
    DAC_STS_INITIALIZED = 0x01,
    DAC_STS_IDLE        = 0x02,
    DAC_STS_TX_READY    = 0x03,
    DAC_STS_TX_ING      = 0x04,
    DAC_STS_RX_READY    = 0x05,
    DAC_STS_RX_ING      = 0x06,
    DAC_STS_ERROR       = 0x07,
};
typedef uint32_t DAC_Device_STATUS;
typedef uint32_t * PDAC_Device_STATUS;

//DAC device error type
enum _DAC_ERR_TYPE_ {
    DAC_ERR_FIFO_OVER      = 0x04,  //DAC FIFO overflow.
    DAC_ERR_FIFO_STOP      = 0x08,  //DAC FIFO is completely empty and stopped.
    DAC_ERR_FIFO_WRFAIL    = 0x10,  //When DAC is NOT enabled, a write access to DAC register.
    DAC_ERR_FIFO_DSC_OVER0 = 0x20,
    DAC_ERR_FIFO_DSC_OVER1 = 0x40,
};
typedef uint32_t DAC_ERR_TYPE;
typedef uint32_t * PDAC_ERR_TYPE;

// DAC data input method
enum _DAC_INPUT_TYPE_{
    DAC_INPUT_SINGLE_WR  = 0x1,    //DAC input by using single register write
    DAC_INPUT_DMA_ONEBLK = 0x2,    //DAC input by using single DMA block
    DAC_INPUT_DMA_LLP    = 0x3,    //DAC input by using DMA linked list mode
};
typedef uint32_t DAC_INPUT_TYPE;
typedef uint32_t * PDAC_INPUT_TYPE;

//======================================================
// DAC HAL initial data structure
typedef struct _HAL_DAC_INIT_DAT_ {
    u8  DACIdx;         //DAC index used
    u8  DACEn;          //DAC module enable
    u8  DACDataRate;    //DAC data rate, 1'b0:10KHz, 1'b1:250KHz
    u8  DACEndian;      //DAC endian selection,
                        //but actually it's for 32-bit DAC data swap control
                        //1'b0: no swap,
                        //1'b1: swap the upper 16-bit and the lower 16-bit
    u8  DACFilterSet;   //DAC filter settle
    u8  DACBurstSz;     //DAC burst size
    u8  DACDbgSel;      //DAC debug sel
    u8  DACDscDbgSel;   //DAC debug dsc sel
    u8  DACBPDsc;       //DAC bypass delta sigma for loopback
    u8  DACDeltaSig;    //DAC bypass value of delta sigma
    u16 RSVD1;
    u32 *DACData;       //DAC data pointer
    u32 DACPWCtrl;      //DAC0 and DAC1 power control
    u32 DACAnaCtrl0;    //DAC anapar_da control 0
    u32 DACAnaCtrl1;    //DAC anapar_da control 1
    u32 DACIntrMSK;     //DAC Interrupt Mask
} HAL_DAC_INIT_DAT,*PHAL_DAC_INIT_DAT;

// DAC HAL Operations
typedef struct _HAL_DAC_OP_ {
    RTK_STATUS  (*HalDACInit)       (void *Data);   //HAL DAC initialization
    RTK_STATUS  (*HalDACDeInit)     (void *Data);   //HAL DAC de-initialization
    RTK_STATUS  (*HalDACEnable)     (void *Data);   //HAL DAC de-initialization
    u8          (*HalDACSend)       (void *Data);   //HAL DAC receive
    RTK_STATUS  (*HalDACIntrCtrl)   (void *Data);   //HAL DAC interrupt control
    u32         (*HalDACReadReg)    (void *Data, u8 DACReg);//HAL DAC read register
} HAL_DAC_OP, *PHAL_DAC_OP;

// DAC user callback adapter
typedef struct _SAL_DAC_USERCB_ADPT_ {
    void (*USERCB) (void *Data);
    u32  USERData;
}SAL_DAC_USERCB_ADPT, *PSAL_DAC_USERCB_ADPT;

// DAC user callback structure
typedef struct _SAL_DAC_USER_CB_ {
    PSAL_DAC_USERCB_ADPT    pTXCB;          //DAC Transmit Callback
    PSAL_DAC_USERCB_ADPT    pTXCCB;         //DAC Transmit Complete Callback
    PSAL_DAC_USERCB_ADPT    pRXCB;          //DAC Receive Callback
    PSAL_DAC_USERCB_ADPT    pRXCCB;         //DAC Receive Complete Callback
    PSAL_DAC_USERCB_ADPT    pRDREQCB;       //DAC Read Request Callback
    PSAL_DAC_USERCB_ADPT    pERRCB;         //DAC Error Callback
    PSAL_DAC_USERCB_ADPT    pDMATXCB;       //DAC DMA Transmit Callback
    PSAL_DAC_USERCB_ADPT    pDMATXCCB;      //DAC DMA Transmit Complete Callback
    PSAL_DAC_USERCB_ADPT    pDMARXCB;       //DAC DMA Receive Callback
    PSAL_DAC_USERCB_ADPT    pDMARXCCB;      //DAC DMA Receive Complete Callback
}SAL_DAC_USER_CB, *PSAL_DAC_USER_CB;

// DAC Transmit Buffer
typedef struct _SAL_DAC_TRANSFER_BUF_ {
    u32     DataLen;                        //DAC Transmfer Length
    u32     *pDataBuf;                      //DAC Transfer Buffer Pointer
    u32     RSVD;                           //
} SAL_DAC_TRANSFER_BUF,*PSAL_DAC_TRANSFER_BUF;

typedef struct _SAL_DAC_DMA_USER_DEF_ {
    u8      TxDatSrcWdth;
    u8      TxDatDstWdth;
    u8      TxDatSrcBstSz;
    u8      TxDatDstBstSz;

    u8      TxChNo;
    u8      LlpCtrl;
    u16     RSVD0;

    u32     MaxMultiBlk;
    u32     pLlix;
    u32     pBlockSizeList;
} SAL_DAC_DMA_USER_DEF, *PSAL_DAC_DMA_USER_DEF;

// Software API Level DAC Handler
typedef struct _SAL_DAC_HND_ {
    u8                      DevNum;             //DAC device number
    u8                      PinMux;             //DAC pin mux seletion
    u8                      OpType;             //DAC operation type selection
    volatile u8             DevSts;             //DAC device status

    u8                      DACInType;          //DAC input type
    u8                      RSVD0;
    u16                     RSVD1;

    u32                     DACExd;             //DAC extended options:
                                                //bit 0: example
                                                //bit 31~bit 1: Reserved
    u32                     ErrType;            //
    u32                     TimeOut;            //DAC IO Timeout count

    PHAL_DAC_INIT_DAT       pInitDat;           //Pointer to DAC initial data struct
    PSAL_DAC_TRANSFER_BUF   pTXBuf;             //Pointer to DAC TX buffer
    PSAL_DAC_USER_CB        pUserCB;            //Pointer to DAC User Callback
    PSAL_DAC_DMA_USER_DEF   pDMAConf;           //Pointer to DAC User Define DMA Config
} SAL_DAC_HND, *PSAL_DAC_HND;

// DAC SAL handle private
typedef struct _SAL_DAC_HND_PRIV_ {
    void            **ppSalDACHnd;              //Pointer to SAL_DAC_HND pointer
    SAL_DAC_HND     SalDACHndPriv;              //Private SAL_DAC_HND
} SAL_DAC_HND_PRIV, *PSAL_DAC_HND_PRIV;

//DAC SAL management adapter
typedef struct _SAL_DAC_MNGT_ADPT_ {
    PSAL_DAC_HND_PRIV       pSalHndPriv;  //Pointer to SAL_DAC_HND
    PHAL_DAC_INIT_DAT       pHalInitDat;  //Pointer to HAL DAC initial data( HAL_I2C_INIT_DAT )
    PHAL_DAC_OP             pHalOp;               //Pointer to HAL DAC operation( HAL_DAC_OP )
    void                    (*pHalOpInit)(void*); //Pointer to HAL DAC initialize function
    PIRQ_HANDLE             pIrqHnd;  //Pointer to IRQ handler in SAL layer( IRQ_HANDLE )
    PSAL_DAC_USER_CB        pUserCB;  //Pointer to SAL user callbacks (SAL_DAC_USER_CB )
    void                    (*pSalIrqFunc)(void*);    //Used for SAL DAC interrupt function
    PSAL_DAC_DMA_USER_DEF   pDMAConf;                 //Pointer to DAC User Define DMA config
    PHAL_GDMA_ADAPTER       pHalGdmaAdp;
    PHAL_GDMA_OP            pHalGdmaOp;
    void                    (*pHalGdmaOpInit)(void*); //Pointer to HAL DAC initialize function
    PIRQ_HANDLE             pIrqGdmaHnd;
    void                    (*pSalDMAIrqFunc)(void*); //Used for SAL DAC interrupt function
} SAL_DAC_MNGT_ADPT, *PSAL_DAC_MNGT_ADPT;

//================ DAC HAL Function Prototype ===================
// DAC HAL inline function
// For checking DAC input index valid or not
static inline RTK_STATUS RtkDACIdxChk(u8 DACIdx)
{
#if !DAC0_USED
    if (DACIdx == DAC0_SEL)
        return _EXIT_FAILURE;
#endif

#if !DAC1_USED
    if (DACIdx == DAC1_SEL)
        return _EXIT_FAILURE;
#endif
    DACIdx = DACIdx;
    return _EXIT_SUCCESS;
}

void HalDACOpInit(void *Data);
RTK_STATUS RtkDACLoadDefault(void *Data);
RTK_STATUS RtkDACInit(void *Data);
RTK_STATUS RtkDACDeInit(void *Data);
RTK_STATUS RtkDACSend(void *Data);
PSAL_DAC_HND RtkDACGetSalHnd(u8 DACIdx);
RTK_STATUS RtkDACFreeSalHnd(PSAL_DAC_HND pSalDACHND);
PSAL_DAC_MNGT_ADPT RtkDACGetMngtAdpt(u8 DACIdx);
RTK_STATUS RtkDACFreeMngtAdpt(PSAL_DAC_MNGT_ADPT pSalDACMngtAdpt);
#endif
