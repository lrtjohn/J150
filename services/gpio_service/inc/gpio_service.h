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
//#define TOOGLE_DRIVE_BOARD_WATCHDOG		(GpioDataRegs.GPCTOGGLE.bit.GPIO85 = 1)
#define ENABLE_GATE_DRIVER()                                            		    \
                                        {                                           \
                                            GpioDataRegs.GPADAT.bit.GPIO16 = 1;     \
                                            GpioDataRegs.GPADAT.bit.GPIO15 = 0;   	\
                                        }
#define DISABLE_GATE_DRIVER()                                            		    \
                                        {                                           \
                                            GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   \
                                            GpioDataRegs.GPADAT.bit.GPIO15 = 1;     \
                                        }
#define ENABLE_BUSBAR_VOLTAGE			(GpioDataRegs.GPADAT.bit.GPIO7 = 1)
#define DISABLE_BUSBAR_VOLTAGE			(GpioDataRegs.GPACLEAR.bit.GPIO7 = 1)
#define IS_BUSBAR_ENABLED               (GpioDataRegs.GPADAT.bit.GPIO7 == 1)

#define DISABLE_SW_BREAK			    (GpioDataRegs.GPACLEAR.bit.GPIO9 = 1)
#define ENABLE_SW_BREAK                 (GpioDataRegs.GPASET.bit.GPIO9 = 1)
#define IS_SW_BREAK_ENABLED             (GpioDataRegs.GPADAT.bit.GPIO9 == 1)

#define ENABLE_RS422_DRIVER()                                            			\
                                        {                                           \
                                            GpioDataRegs.GPCDAT.bit.GPIO77 = 1;     \
                                            GpioDataRegs.GPCCLEAR.bit.GPIO78 = 1;   \
                                        }

#define IS_VCC3V3_PG                    (GpioDataRegs.GPBDAT.bit.GPIO43 == 0)
#define IS_VCC1V9_PG                    (GpioDataRegs.GPBDAT.bit.GPIO45 == 0)
#define IS_VCC5V_PG                     (GpioDataRegs.GPBDAT.bit.GPIO42 == 0)
#define IS_VDD5V_PG                     (GpioDataRegs.GPBDAT.bit.GPIO44 == 0)
#define IS_HARDWARE_OC				    (GpioDataRegs.GPADAT.bit.GPIO17 == 0)
#define IS_HARDWARE_OV					(GpioDataRegs.GPADAT.bit.GPIO31 == 0)
#define IS_HARDWARE_OC_OV               (GpioDataRegs.GPADAT.bit.GPIO13 == 0)

//#define TURN_ON_PWM_VALVE               (GpioDataRegs.GPCCLEAR.bit.GPIO84 = 1)
#define TURN_OFF_PWM_VALVE              (GpioDataRegs.GPCSET.bit.GPIO84 = 1)

#define DELAY_NOPS(times)                               \
                        {                               \
                            int i;                      \
                            for(i = 0; i < times; ++i)  \
                            {                           \
                                asm (" NOP");           \
                            }                           \
                        }

#define HARDWARE_OVER_CURRENT_CLEAR()                                               \
                                        {                                           \
                                            GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   \
                                            DELAY_NOPS(5);							\
                                            GpioDataRegs.GPASET.bit.GPIO12 = 1;		\
                                        }

#define DIABLE_ALL()                                            \
                    {                                           \
                    	Disable_All_Epwms();                    \
		                DISABLE_SW_BREAK;                       \
                    }

#define DIGIT_SIG_ROUTING_INSPECTION()                                              	   	   \
                                        {                                           	   	   \
                                            if(IS_VCC5V_PG) SET_SYS_PG_VCC5V_ALARM;       	   \
                                            if(IS_VCC1V9_PG) SET_SYS_PG_1V9_ALARM;        	   \
                                            if(IS_VCC3V3_PG) SET_SYS_PG_VCC3V3_ALARM;     	   \
											if(IS_VDD5V_PG) SET_SYS_PG_VDD5V_ALARM;       	   \
											if(IS_HARDWARE_OC){								   \
												SET_SYS_BUS_CURRENT_ALARM; 	   				   \
											}												   \
											else CLEAR_SYS_BUS_CURRENT_ALARM;			   	   \
											if(IS_HARDWARE_OV) SET_SYS_BUS_OVER_VOLTAGE_ALARM; \
											else CLEAR_SYS_BUS_OVER_VOLTAGE_ALARM;			   \
                                        }

                    
#endif

