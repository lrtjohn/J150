#ifndef PF_GPIO_CFG_H_
#define PF_GPIO_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

#define TOTAL_GPIO 88

typedef enum
{
    GPIO_INTPUT,
    GPIO_OUTPUT
}GPIO_DIRECTION;

typedef struct
{
	int gpioIndex;
	GPIO_DIRECTION direction;
}CFG_GPIO_TBL;

typedef void (*CFG_GPIO_HDL_TBL)(GPIO_DIRECTION direction);


void PFAL_GPIO_CFG(CFG_GPIO_TBL* cfgGpioTbl, int len);

#endif /* MAIN_H_ */

