#ifndef PF_ECAP_CFG_H_
#define PF_ECAP_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

#define TOTAL_ECAP 6


void PFAL_ECAP_CFG(CFG_ECAP_TBL* cfgECapTbl, int len);

#endif /* MAIN_H_ */
