#include <stdio.h>
#include "sci_adapt.h"

SCI_TRANSPORT* pSciTransport = NULL;
SCI_TRANSPORT gSciTransport;

int SCI_Adapt_Config(void)
{
    return pSciTransport->config();
}

int SCI_Adapt_Start(void)
{
    return pSciTransport->start();
}

int SCI_Adapt_FindHead(SCIRXQUE* q)
{
    return pSciTransport->findHead(q);
}

int SCI_Adapt_CheckLength(SCIRXQUE* q)
{
    return pSciTransport->checkLength(q);
}

int SCI_Adapt_CheckTail(SCIRXQUE* q)
{
    return pSciTransport->checkTail(q);
}

int SCI_Adapt_CheckSum(unsigned char* q)
{
    return pSciTransport->checkSum(q);
}

int SCI_Adapt_UpdateHeadPos(SCIRXQUE* q)
{
    return pSciTransport->updateHeadPos(q);
}

int SCI_Adapt_SaveGoodPacket(int len, SCIRXQUE* q)
{
    return pSciTransport->saveGoodPacket(len, q);
}

int SCI_Adapt_Init(SCI_TRANSPORT* gpSciTransport)
{
    pSciTransport = gpSciTransport;
    pSciTransport->init();
    return 0;
}
