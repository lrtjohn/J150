#ifndef PF_ECAP_CFG_H_
#define PF_ECAP_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

#define TOTAL_ECAP 6

typedef enum
{
    ECAP_1,
	ECAP_2,
	ECAP_3,
	ECAP_4,
	ECAP_5,
	ECAP_6
}ECAP_ENABLE;

typedef struct
{
    ECAP_ENABLE ecapModule;
    int ecapGPIOindex;
}CFG_ECAP_GPIO;

typedef struct
{
	CFG_ECAP_GPIO cfgECapGpio;

}CFG_ECAP_TBL;

typedef void (*CFG_ECAP_HDL_TBL)(CFG_ECAP_TBL cfgECapTblElement);

void PFAL_ECAP_CFG(CFG_ECAP_TBL* cfgECapTbl, int len);

#endif /* MAIN_H_ */
