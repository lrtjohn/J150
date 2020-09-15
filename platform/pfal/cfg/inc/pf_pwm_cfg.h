#ifndef PF_PWM_CFG_H_
#define PF_PWM_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

#define TOTAL_PWM 12

typedef enum
{
    PWM1A,
    PWM1B,
    PWM2A,
    PWM2B,
    PWM3A,
    PWM3B,
    PWM4A,
    PWM4B,
    PWM5A,
    PWM5B,
    PWM6A,
    PWM6B
}PWM_MODULE;

typedef struct
{
    PWM_MODULE pwmModule;
}CFG_PWM_MODULE;

typedef struct
{
    Uint16 Frequency;
}CFG_PWM_PARAM;
typedef struct
{
    CFG_PWM_MODULE cfgPwmModule;
    CFG_PWM_PARAM cfgPwmParam;
}CFG_PWM_TBL;

typedef void (*CFG_PWM_HDL_TBL)(CFG_PWM_TBL cfgPwmTblElement);

void PFAL_PWM_CFG(CFG_PWM_TBL* cfgPwmTbl, int len);

#endif /* MAIN_H_ */

