#include <stdio.h>
#include "sci_adapt.h"

SCI_TRANSPORT_RX* pSciTransportRx = NULL;

int SCI_Trans_AdaptRx_Config(void)
{
    return pSciTransportRx->config();
}

int SCI_Trans_AdaptRx_Start(void)
{
    return pSciTransportRx->start();
}

int SCI_Trans_AdaptRx_FindHead(SCIRXQUE* q)
{
    return pSciTransportRx->findHead(q);
}

int SCI_Trans_AdaptRx_CheckLength(SCIRXQUE* q)
{
    return pSciTransportRx->checkLength(q);
}

int SCI_Trans_AdaptRx_CheckTail(SCIRXQUE* q)
{
    return pSciTransportRx->checkTail(q);
}

int SCI_Trans_AdaptRx_CheckSum(SCIRXQUE* q)
{
    return pSciTransportRx->checkSum(q);
}

int SCI_Trans_AdaptRx_UpdateHeadPos(SCIRXQUE* q)
{
    return pSciTransportRx->updateHeadPos(q);
}

int SCI_Trans_AdaptRx_SaveGoodPacket(int len, SCIRXQUE* q)
{
    return pSciTransportRx->saveGoodPacket(len, q);
}

int SCI_Trans_AdaptRx_Init(SCI_TRANSPORT_RX* gpSciTransportRx)
{
    pSciTransportRx = gpSciTransportRx;
    pSciTransportRx->init();
    return 0;
}

inline Uint16 SCI_Trans_AdaptRx_GetLength()
{
    return pSciTransportRx->mTotalLength;
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
