#ifndef SCI_ADAPT_H
#define SCI_ADAPT_H

#include "sci_queue.h"

typedef int(*ADAPT_Init)(void);
typedef int(*ADAPT_Config)(void);
typedef int(*ADAPT_Start)(void);
typedef int(*ADAPT_FindHead)(SCIRXQUE* q);
typedef int(*ADAPT_CheckLength)(SCIRXQUE* q);
typedef int(*ADAPT_CheckTail)(SCIRXQUE* q);
typedef int(*ADAPT_CheckSum)(SCIRXQUE* q);

typedef struct _SCI_TRANSPORT
{
    ADAPT_Init              init;
    ADAPT_Config            config;
    ADAPT_Start             start;
    ADAPT_FindHead          findHead;
    ADAPT_CheckLength       checkLength;
    ADAPT_CheckTail         checkTail;
    ADAPT_CheckSum          checkSum;
}SCI_TRANSPORT;


#endif
