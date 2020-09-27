#include <stdio.h>
#include "sci_adapt.h"

SCI_TRANSPORT_RX* pSciTransportRx = NULL;
SCI_TRANSPORT_TX* pSciTransportTx = NULL;

void U16_TO_U8(void* d, void* s)
{
#if (0)
    *((Uint16*)d) = *((Uint16*)s);
    *((Uint16*)d + 1) = *((Uint16*)s + 1);
#endif

#if(LSB_FIRST_SEND)
    *((Uint16*)d) = (*((Uint16*)s)) & 0x00ff;
    *((Uint16*)d + 1) = (*((Uint16*)s)) >> 8;
#endif

#if(MSB_FIRST_SEND)
    *((Uint16*)d + 1) = (*((Uint16*)s)) >> 8;
    *((Uint16*)d) = (*((Uint16*)s)) & 0x00ff;
#endif
}

void U32_TO_U8(void* d, void* s)
{
#if(0)
    *((Uint16*)d) = *((Uint16*)s);
    *((Uint16*)d + 1) = *((Uint16*)s + 1);
    *((Uint16*)d + 2) = *((Uint16*)s + 2);
    *((Uint16*)d + 3) = *((Uint16*)s + 3);
#endif

#if(LSB_FIRST_SEND)
    *((Uint16*)d) = (*((Uint32*)s)) & 0x000000ff;
    *((Uint16*)d + 1) = (*((Uint32*)s)) >> 8;
    *((Uint16*)d + 2) = (*((Uint32*)s)) >> 16;
    *((Uint16*)d + 3) = (*((Uint32*)s)) >> 24;
#endif

#if(MSB_FIRST_SEND)
    *((Uint16*)d + 3) = (*((Uint32*)s)) >> 24;
    *((Uint16*)d + 2) = (*((Uint32*)s)) >> 16;
    *((Uint16*)d + 1) = (*((Uint32*)s)) >> 8;
    *((Uint16*)d) = (*((Uint32*)s)) & 0x000000ff;
#endif
}
/***********************************************************************************
███████  ██████ ██      █████  ██████   █████  ██████  ████████     ██████  ██   ██ 
██      ██      ██     ██   ██ ██   ██ ██   ██ ██   ██    ██        ██   ██  ██ ██  
███████ ██      ██     ███████ ██   ██ ███████ ██████     ██        ██████    ███   
     ██ ██      ██     ██   ██ ██   ██ ██   ██ ██         ██        ██   ██  ██ ██  
███████  ██████ ██     ██   ██ ██████  ██   ██ ██         ██        ██   ██ ██   ██ 
************************************************************************************/
int SCI_Trans_AdaptRx_Init(SCI_TRANSPORT_RX* gpSciTransportRx)
{
    pSciTransportRx = gpSciTransportRx;
    pSciTransportRx->init();
    return 0;
}

int SCI_Trans_AdaptRx_Config(void)
{
    return pSciTransportRx->config();
}

int SCI_Trans_AdaptRx_Start(void)
{
    return pSciTransportRx->start();
}

inline int SCI_Trans_AdaptRx_FindHead(SCIRXQUE* q)
{
    return pSciTransportRx->findHead(q);
}

inline int SCI_Trans_AdaptRx_CheckLength(SCIRXQUE* q)
{
    return pSciTransportRx->checkLength(q);
}

inline int SCI_Trans_AdaptRx_CheckTail(SCIRXQUE* q)
{
    return pSciTransportRx->checkTail(q);
}

inline int SCI_Trans_AdaptRx_CheckSum(SCIRXQUE* q)
{
    return pSciTransportRx->checkSum(q);
}

inline int SCI_Trans_AdaptRx_UpdateHeadPos(SCIRXQUE* q)
{
    return pSciTransportRx->updateHeadPos(q);
}

inline int SCI_Trans_AdaptRx_SaveGoodPacket(int len, SCIRXQUE* q)
{
    return pSciTransportRx->saveGoodPacket(len, q);
}

inline Uint16 SCI_Trans_AdaptRx_GetLength()
{
    return pSciTransportRx->mRxTotalLength;
}

void SCI_RX_UnpackData(SCIRXQUE* q)
{
    while (GetSciRxQueLength(q) >= SCI_Trans_AdaptRx_GetLength())
    {
        if (SCI_Trans_AdaptRx_FindHead(q) == FAIL)
        {
            return;
        }

        if (SCI_Trans_AdaptRx_CheckLength(q) == FAIL)
        {
            return;
        }

        if (SCI_Trans_AdaptRx_CheckTail(q) == FAIL)
        {
            SciRxDeQueue(q);
            return;
        }

        if (SCI_Trans_AdaptRx_CheckSum(q) == FAIL)
        {
            SciRxDeQueue(q);
            return;
        }

        SCI_Trans_AdaptRx_SaveGoodPacket(SCI_Trans_AdaptRx_GetLength(), q);

        SCI_Trans_AdaptRx_UpdateHeadPos(q);
    }
}

/***********************************************************************************
███████  ██████ ██      █████  ██████   █████  ██████  ████████     ████████ ██   ██ 
██      ██      ██     ██   ██ ██   ██ ██   ██ ██   ██    ██           ██     ██ ██  
███████ ██      ██     ███████ ██   ██ ███████ ██████     ██           ██      ███   
     ██ ██      ██     ██   ██ ██   ██ ██   ██ ██         ██           ██     ██ ██  
███████  ██████ ██     ██   ██ ██████  ██   ██ ██         ██           ██    ██   ██
************************************************************************************/
int SCI_Trans_AdaptTx_Init(SCI_TRANSPORT_TX* gpSciTransportTx)
{
    pSciTransportTx = gpSciTransportTx;
    pSciTransportTx->init();
    return 0;

}

inline int SCI_Trans_AdaptTx_UpdatePayLoad()
{
    return pSciTransportTx->updatePayLoad();
}

inline int SCI_Trans_AdaptTx_CalCheckSum()
{
    return pSciTransportTx->calCheckSum();
}

inline int SCI_Trans_AdaptTx_PackOneFrame()
{
    return pSciTransportTx->packOneFrame();
}

inline int SCI_Trans_AdaptTx_EnQueOneFrame(SCITXQUE* txQue)
{
    return pSciTransportTx->enQueOneFrame(txQue);
}

void SCI_TX_PackData(SCITXQUE* txQue)
{
    SCI_Trans_AdaptTx_UpdatePayLoad();
    SCI_Trans_AdaptTx_CalCheckSum();
    SCI_Trans_AdaptTx_PackOneFrame();
    SCI_Trans_AdaptTx_EnQueOneFrame(txQue);
}
