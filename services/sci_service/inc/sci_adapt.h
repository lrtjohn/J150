#ifndef SCI_ADAPT_H
#define SCI_ADAPT_H

#include "sci_queue.h"

#define SCI_RX_HEAD_LEN_MAX     (2)
#define SCI_RX_TAIL_LEN_MAX     (2)

typedef int(*ADAPT_RX_Init)(void);
typedef int(*ADAPT_RX_Config)(void);
typedef int(*ADAPT_RX_Start)(void);
typedef int(*ADAPT_RX_FindHead)(SCIRXQUE* q);
typedef int(*ADAPT_RX_CheckLength)(SCIRXQUE* q);
typedef int(*ADAPT_RX_CheckTail)(SCIRXQUE* q);
typedef int(*ADAPT_RX_SaveGoodPacket)(int len, SCIRXQUE* q);
typedef int(*ADAPT_RX_CheckSum)(SCIRXQUE* q);
typedef int(*ADAPT_RX_UpdateHeadPos)(SCIRXQUE* q);

typedef struct _SCI_TRANSPORT_RX
{
    ADAPT_RX_Init              init;
    ADAPT_RX_Config            config;
    ADAPT_RX_Start             start;
    ADAPT_RX_FindHead          findHead;
    ADAPT_RX_CheckLength       checkLength;
    ADAPT_RX_CheckTail         checkTail;
    ADAPT_RX_SaveGoodPacket    saveGoodPacket;
    ADAPT_RX_CheckSum          checkSum;
    ADAPT_RX_UpdateHeadPos     updateHeadPos;

    Uint16 mRxHead[SCI_RX_HEAD_LEN_MAX];
    Uint16 mRxHeadLength;
    Uint16 mRxTail[SCI_RX_TAIL_LEN_MAX];
    Uint16 mRxTailLength;
    Uint16 mTotalLength;
    void*  mpAppProtocol;
}SCI_TRANSPORT_RX;


extern void U16_TO_U8(void* d, void* s);
extern void U32_TO_U8(void* d, void* s);
extern int SCI_Trans_AdaptRx_Config(void);
extern int SCI_Trans_AdaptRx_Start(void);
extern int SCI_Trans_AdaptRx_Init(SCI_TRANSPORT_RX* gpSciTransportRx);
extern void SCI_RX_UnpackData(SCIRXQUE* q);
#endif
