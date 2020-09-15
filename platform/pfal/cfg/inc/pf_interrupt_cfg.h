#ifndef PF_INTERRUPT_CFG_H_
#define PF_INTERRUPT_CFG_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

#define TOTAL_INTERRUPT 1
typedef enum
{
    TIMER0_ISR,
    TIMER1_ISR,
    EPWM1,
    ECAP1,
    ECAP2,
    ECAP3,
    ECAP4,
    ECAP5,
    ECAP6,
    SCIARX,
    SCIATX,
    SCIBRX,
    SCIBTX,
    SCICRX,
    SCICTX
}CFG_ISR_ENABLE;


typedef struct
{
    CFG_ISR_ENABLE cfgIsrEnable;
}CFG_INTERRUPT_TBL;

typedef void (*CFG_INTERRUPT_HDL_TBL)(CFG_ISR_ENABLE isrEnable);

void PFAL_INTERRUPT_CFG(CFG_INTERRUPT_TBL* cfgInterruptTbl, int len);
#endif
