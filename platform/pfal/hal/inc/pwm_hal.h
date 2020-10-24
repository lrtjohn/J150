#ifndef PF_PWM_HAL_H_
#define PF_PWM_HAL_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"




//#define EPMW1_OUTPUT_DUAL_PLOARITY(halfperiod, duty)  (EPwm1Regs.CMPA.half.CMPA = halfperiod + duty)
//#define EPMW2_OUTPUT_DUAL_PLOARITY(halfperiod, duty)  (EPwm2Regs.CMPA.half.CMPA = halfperiod + duty)
//#define EPMW3_OUTPUT_DUAL_PLOARITY(halfperiod, duty)  (EPwm3Regs.CMPA.half.CMPA = halfperiod + duty)
//#define EPMW4_OUTPUT_DUAL_PLOARITY(halfperiod, duty)  (EPwm4Regs.CMPA.half.CMPA = halfperiod + duty)
//#define EPMW5_OUTPUT_DUAL_PLOARITY(halfperiod, duty)  (EPwm5Regs.CMPA.half.CMPA = halfperiod + duty)
//#define EPMW6_OUTPUT_DUAL_PLOARITY(halfperiod, duty)  (EPwm6Regs.CMPA.half.CMPA = halfperiod + duty)


#define EPMW1_OUTPUT_UP(halfperiod, duty)  (EPwm1Regs.CMPA.half.CMPA = halfperiod + duty)
#define EPMW2_OUTPUT_UP(halfperiod, duty)  (EPwm2Regs.CMPA.half.CMPA = halfperiod + duty)
#define EPMW3_OUTPUT_UP(halfperiod, duty)  (EPwm3Regs.CMPA.half.CMPA = halfperiod + duty)
#define EPMW4_OUTPUT_UP(halfperiod, duty)  (EPwm4Regs.CMPA.half.CMPA = halfperiod + duty)
#define EPMW5_OUTPUT_UP(halfperiod, duty)  (EPwm5Regs.CMPA.half.CMPA = halfperiod + duty)
#define EPMW6_OUTPUT_UP(halfperiod, duty)  (EPwm6Regs.CMPA.half.CMPA = halfperiod + duty)

#define EPMW1_OUTPUT_DOWN(halfperiod, duty)  (EPwm1Regs.CMPA.half.CMPA = halfperiod - duty)
#define EPMW2_OUTPUT_DOWN(halfperiod, duty)  (EPwm2Regs.CMPA.half.CMPA = halfperiod - duty)
#define EPMW3_OUTPUT_DOWN(halfperiod, duty)  (EPwm3Regs.CMPA.half.CMPA = halfperiod - duty)
#define EPMW4_OUTPUT_DOWN(halfperiod, duty)  (EPwm4Regs.CMPA.half.CMPA = halfperiod - duty)
#define EPMW5_OUTPUT_DOWN(halfperiod, duty)  (EPwm5Regs.CMPA.half.CMPA = halfperiod - duty)
#define EPMW6_OUTPUT_DOWN(halfperiod, duty)  (EPwm6Regs.CMPA.half.CMPA = halfperiod - duty)


#define Disable_Epwm1() EPwm1Regs.AQCSFRC.all = 0x0009
#define Disable_Epwm2() EPwm2Regs.AQCSFRC.all = 0x0009
#define Disable_Epwm3() EPwm3Regs.AQCSFRC.all = 0x0009
#define Disable_Epwm4() EPwm4Regs.AQCSFRC.all = 0x0009
#define Disable_Epwm5() EPwm5Regs.AQCSFRC.all = 0x0009
#define Disable_Epwm6() EPwm6Regs.AQCSFRC.all = 0x0009


#define Disable_All_Epwms()\
                            {\
                               Disable_Epwm1();\
                               Disable_Epwm2();\
                               Disable_Epwm3();\
                               Disable_Epwm4();\
                               Disable_Epwm5();\
                               Disable_Epwm6();\
                           }
#define Enable_Epwm1() EPwm1Regs.AQCSFRC.all = 0x000f
#define Enable_Epwm2() EPwm2Regs.AQCSFRC.all = 0x000f
#define Enable_Epwm3() EPwm3Regs.AQCSFRC.all = 0x000f
#define Enable_Epwm4() EPwm4Regs.AQCSFRC.all = 0x000f
#define Enable_Epwm5() EPwm5Regs.AQCSFRC.all = 0x000f
#define Enable_Epwm6() EPwm6Regs.AQCSFRC.all = 0x000f


#define Enable_All_Epwms()\
                            {\
                               Enable_Epwm1();\
                               Enable_Epwm2();\
                               Enable_Epwm3();\
                               Enable_Epwm4();\
                               Enable_Epwm5();\
                               Enable_Epwm6();\
                           }


#endif


