#ifndef GPIO_SERVICE_H_
#define GPIO_SERVICE_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sys_state_service.h"


/*
    GPIO12/TZ1          OV_ERR
    GPIO84              PWM_OE
    GPIO40              VDD3V3_PG
    GPIO42              1V9_PG
    GPIO47              VCC3V3_PG
    GPIO51              WDI


    GPIO85              WDI_QD_3V3
    GPIO16              EN_QD_3V3
*/
#define TOOGLE_CTL_BOARD_WATCHDOG		(GpioDataRegs.GPBTOGGLE.bit.GPIO51 = 1)
#define TOOGLE_DRIVE_BOARD_WATCHDOG		(GpioDataRegs.GPCTOGGLE.bit.GPIO85 = 1)
#define TURN_ON_CTL_BOARD()                                            				\
                                        {                                           \
                                            GpioDataRegs.GPADAT.bit.GPIO31 = 1;     \
                                            GpioDataRegs.GPCCLEAR.bit.GPIO83 = 1;     \
                                        }

#define IS_VDD3V3_PG                    (GpioDataRegs.GPBDAT.bit.GPIO40 == 1)
#define IS_1V9_PG                       (GpioDataRegs.GPBDAT.bit.GPIO42 == 1)
#define IS_VCC3V3_PG                    (GpioDataRegs.GPBDAT.bit.GPIO47 == 1)
#define IS_OC							(GpioDataRegs.GPCDAT.bit.GPIO81 == 1)

#define IS_OV_ERR_TZ                    (GpioDataRegs.GPADAT.bit.GPIO12 == 1)

#define TURN_ON_PWM_VALVE               (GpioDataRegs.GPCCLEAR.bit.GPIO84 = 1)
#define TURN_OFF_PWM_VALVE              (GpioDataRegs.GPCSET.bit.GPIO84 = 1)

#define DELAY_NOPS(times)                               \
                        {                               \
                            int i;                      \
                            for(i = 0; i < times; ++i)  \
                            {                           \
                                asm (" NOP");           \
                            }                           \
                        }

#define ENABLE_DRIVE_BOARD_PWM_OUTPUT()                                             \
                                        {                                           \
											DELAY_NOPS(0);						\
                                            GpioDataRegs.GPADAT.bit.GPIO16 = 0;     \
                                            DELAY_NOPS(30);                          \
                                            GpioDataRegs.GPADAT.bit.GPIO16 = 1;     \
                                            DELAY_NOPS(30);                          \
                                            GpioDataRegs.GPADAT.bit.GPIO16 = 0;     \
                                            DELAY_NOPS(15);                          \
                                            GpioDataRegs.GPADAT.bit.GPIO16 = 1;     \
                                            DELAY_NOPS(30);                          \
                                            GpioDataRegs.GPADAT.bit.GPIO16 = 0;		\
                                        }




#define DIGIT_SIG_ROUTING_INSPECTION()                                              \
                                        {                                           \
                                            if(!IS_VDD3V3_PG)                       \
                                            {                                       \
                                                SET_SYS_PG_VDD3V3_ALARM;            \
                                            }                                       \
                                            if(!IS_1V9_PG)                          \
                                            {                                       \
                                                SET_SYS_PG_1V9_ALARM;               \
                                            }                                       \
                                            if(!IS_VCC3V3_PG)                       \
                                            {                                       \
                                                SET_SYS_PG_VCC3V3_ALARM;            \
                                            }                                       \
											if(!IS_OC)                       		\
                                            {                                       \
                                                SET_SYS_BUS_CURRENT_ALARM;          \
                                            }                                       \
                                        }

                    
#endif

