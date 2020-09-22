#ifndef SCI_ADAPT_H
#define SCI_ADAPT_H

#include "sci_queue.h"

typedef int(*ADAPT_Init)(void);
typedef int(*ADAPT_Config)(void);
typedef int(*ADAPT_Start)(void);
typedef int(*ADAPT_FindHead)(SCIRXQUE* q);
typedef int(*ADAPT_CheckLength)(SCIRXQUE* q);
typedef int(*ADAPT_CheckTail)(SCIRXQUE* q);
typedef int(*ADAPT_SaveGoodPacket)(int len, SCIRXQUE* q);
typedef int(*ADAPT_CheckSum)(unsigned char* q);
typedef int(*ADAPT_UpdateHeadPos)(SCIRXQUE* q);

typedef struct _SCI_TRANSPORT
{
    ADAPT_Init              init;
    ADAPT_Config            config;
    ADAPT_Start             start;
    ADAPT_FindHead          findHead;
    ADAPT_CheckLength       checkLength;
    ADAPT_CheckTail         checkTail;
    ADAPT_SaveGoodPacket    saveGoodPacket;
    ADAPT_CheckSum          checkSum;
    ADAPT_UpdateHeadPos     updateHeadPos;

}SCI_TRANSPORT;


extern int SCI_Trans_Adapt_Config(void);
extern int SCI_Trans_Adapt_Start(void);
extern int SCI_Trans_Adapt_FindHead(SCIRXQUE* q);
extern int SCI_Trans_Adapt_CheckLength(SCIRXQUE* q);
extern int SCI_Trans_Adapt_CheckTail(SCIRXQUE* q);
extern int SCI_Trans_Adapt_CheckSum(unsigned char* q);
extern int SCI_Trans_Adapt_UpdateHeadPos(SCIRXQUE* q);
extern int SCI_Trans_Adapt_SaveGoodPacket(int len, SCIRXQUE* q);
extern int SCI_Trans_Adapt_Init(SCI_TRANSPORT* gpSciTransport);
#endif
