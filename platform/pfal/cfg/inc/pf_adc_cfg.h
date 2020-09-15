#ifndef PF_ADC_CFG_H_
#define PF_ADC_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

typedef struct
{
    int i;
}CFG_ADC_TBL;

typedef void (*CFG_ADC_HDL_TBL)(CFG_ADC_TBL cfgAdcTblElement);
void PFAL_ADC_CFG(CFG_ADC_TBL* cfgAdcTbl, int len);
#endif /* MAIN_H_ */

