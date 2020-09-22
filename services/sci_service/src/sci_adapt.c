#include <stdio.h>
#include "sci_adapt.h"


SCI_TRANSPORT* pSciTransport = NULL;
SCI_TRANSPORT gSciTransport;


int Adapt_Init(void)
{
    gSciTransport.init();
    return 0;
}

int Adapt_Config(void)
{
    gSciTransport.config();
    return 0;
}

int Adapt_Start(void)
{
    gSciTransport.start();
    return 0;
}

int Adapt_FindHead(SCIRXQUE* q)
{
    return gSciTransport.findHead(q);
}

int Adapt_CheckLength(SCIRXQUE* q)
{
    return gSciTransport.checkLength(q);
}

int Adapt_CheckTail(SCIRXQUE* q)
{
    return gSciTransport.checkTail(q);
}

int Adapt_CheckSum(SCIRXQUE* q)
{
    return gSciTransport.checkSum(q);
}
