#ifndef PF_CFG_H_
#define PF_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "pf_adc_cfg.h"
#include "pf_gpio_cfg.h"
#include "pf_pwm_cfg.h"
#include "pf_ecap_cfg.h"
#include "pf_sci_cfg.h"
#include "pf_spi_cfg.h"
#include "pf_xintf_cfg.h"
#include "pf_timer_cfg.h"
#include "pf_interrupt_cfg.h"
#include "prod.h"

CFG_GPIO_TBL CfgGpioTbl_User[] =
{
 //{gpio number, gpio direction}
 	{29, GPIO_INTPUT}, //DISABLE_BIT
	{13, GPIO_INTPUT}, //CV_ERR_3V3
	{17, GPIO_INTPUT}, //OC_FG_3V3
	{42, GPIO_INTPUT}, //VCC5V_PG
	{43, GPIO_INTPUT}, //VCC3V3_PG
	{44, GPIO_INTPUT}, //VDD5V_PG
	{45, GPIO_INTPUT}, //VCC1V9_PG
	{31, GPIO_INTPUT}, //OV_FG_3V3

	// {0, GPIO_INTPUT},
	// {1, GPIO_INTPUT},
	// {2, GPIO_INTPUT},
	// {3, GPIO_INTPUT},
	// {4, GPIO_INTPUT},
	// {5, GPIO_INTPUT},
	// {7, GPIO_INTPUT},
	// {9, GPIO_INTPUT},
	// {12, GPIO_INTPUT},
	// {15, GPIO_INTPUT},
	// {16, GPIO_INTPUT},
	// {22, GPIO_INTPUT},
	// {51, GPIO_INTPUT},
	// {77, GPIO_INTPUT},
	// {78, GPIO_INTPUT},

	{7, GPIO_OUTPUT}, //MX_RJ_KZ
	{9, GPIO_OUTPUT}, //BREAK_RJ_KZ
	{12, GPIO_OUTPUT}, //ERR_CLR
	{15, GPIO_OUTPUT}, //ENABLE_3V3_N
	{16, GPIO_OUTPUT}, //ENABLE_3V3_P
	{49, GPIO_OUTPUT}, //ZDGC_OUT1
	{50, GPIO_OUTPUT}, //ZDGC_OUT2
	{51, GPIO_OUTPUT}, //DSP_WDI
	{59, GPIO_OUTPUT}, //ZDGC_OUT3
	{60, GPIO_OUTPUT}, //ZDGC_OUT4
	{64, GPIO_OUTPUT}, //ZDGC_OUT5
	{65, GPIO_OUTPUT}, //ZDGC_OUT6
	{67, GPIO_OUTPUT}, //ZDGC_OUT7
	{68, GPIO_OUTPUT}, //ZDGC_OUT8
	{77, GPIO_OUTPUT}, //RS422_DE
	{78, GPIO_OUTPUT} //RS422_RE
};

CFG_ECAP_TBL CfgECapTbl_User[] =
{
 {
  ECAP_4,
  27
 },
 {
  ECAP_3,
  26
 },
 {
  ECAP_2,
  25
 }
};

#define EPWM_PERIOD_K 30
CFG_PWM_TBL CfgPwmTbl_User[] =
{
#if(PF_PWM_1A == INCLUDE_FEATURE)
   {
       {
           PWM1A
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_1B == INCLUDE_FEATURE)
   {
       {
           PWM1B
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_2A == INCLUDE_FEATURE)
   {
       {
           PWM2A
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_2B == INCLUDE_FEATURE)
   {
       {
           PWM2B
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_3A == INCLUDE_FEATURE)
   {
       {
           PWM3A
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_3B == INCLUDE_FEATURE)
   {
       {
           PWM3B
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_4A == INCLUDE_FEATURE)
   {
       {
           PWM4A
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_4B == INCLUDE_FEATURE)
   {
       {
           PWM4B
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_5A == INCLUDE_FEATURE)
   {
       {
           PWM5A
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_5B == INCLUDE_FEATURE)
   {
       {
           PWM5B
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_6A == INCLUDE_FEATURE)
   {
       {
           PWM6A
       },
       {
           EPWM_PERIOD_K
       }
   },
#endif
#if(PF_PWM_6B == INCLUDE_FEATURE)
   {
       {
           PWM6B
       },
       {
           EPWM_PERIOD_K
       }
   }
#endif
};

CFG_SCI_TBL CfgSciTbl_User[] =
{
    // {
    //     {
    //         SCIA,       //sci moudule, A, B, C
    //         28,         //sci rx gpio index
    //         29          //sci tx gpio index
    //     },
    //     {
    //         BAUD_RATE_115200    //sci baud rate
    //     }
    // },
    {
        {
            SCIB, 
            23,
            22
        },
        {
            BAUD_RATE_115200,
            DISABLE_LOOP_BACK
        }
    },
    // {
    //     {
    //         SCIC, 
    //         62,
    //         63
    //     },
    //     {
    //         BAUD_RATE_115200,
    //         ENABLE_LOOP_BACK
    //     }
    // }
};


CFG_SPI_TBL CfgSpiTbl_User[] =
{
    {54, 55, 56, 57}
};

CFG_XINTF_TBL CfgXintfTbl_User[] =
{
    {
        DATA_MODE_16BIT,        //DATA_MODE_16BIT   DATA_MODE_32BIT          select data bus width
        ADDR_DISABLE,           //ADDR_DISABLE  ADDR_ENAABLE                 address bus enable or not
        ZONE0_DISABLE,          //ZONE0_DISABLE  ZONE0_ENABLE                zone0 enable or not
        ZONE6_ENABLE,           //ZONE6_DISABLE  ZONE6_ENABLE                zone6 enable or not
        ZONE7_DISABLE           //ZONE7_DISABLE  ZONE7_ENABLE                zone7 enable or not
    }
};

CFG_TIMER_TBL CfgTimerTbl_User[] =
{
    {
        TIMER0,             //Timer moudule, timer0 timer1
        5000,               //timer period, unit:us
        CPU_FREQUENCY       //system frequency
    },
    {
        TIMER1, 
        20000,
        CPU_FREQUENCY       //system frequency
    }
};


CFG_INTERRUPT_TBL CfgInterruptTbl_User[] = 
{
    TIMER0_ISR,
    TIMER1_ISR,
    EPWM1,
    SCIBRX,
    SCIBTX,
    ECAP2,
    ECAP3,
    ECAP4,
    // SCICRX,
    // SCICTX
};

CFG_ADC_TBL CfgAdcTbl_User[] = 
{
    8
};
#endif /* MAIN_H_ */
