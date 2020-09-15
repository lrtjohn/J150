#ifndef PF_CFG_H_
#define PF_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "pf_adc_cfg.h"
#include "pf_gpio_cfg.h"
#include "pf_pwm_cfg.h"
#include "pf_sci_cfg.h"
#include "pf_spi_cfg.h"
#include "pf_xintf_cfg.h"
#include "pf_timer_cfg.h"
#include "pf_interrupt_cfg.h"
#include "prod.h"

CFG_GPIO_TBL CfgGpioTbl_User[] =
{
    {86, GPIO_OUTPUT},			//{gpio number, gpio direction}
    {87, GPIO_OUTPUT},
    {39, GPIO_OUTPUT},
    {60, GPIO_OUTPUT},
    {61, GPIO_OUTPUT},
    {85, GPIO_OUTPUT},
    {16, GPIO_OUTPUT},
    {84, GPIO_OUTPUT},
    {51, GPIO_OUTPUT},
    {63, GPIO_OUTPUT},
    {31, GPIO_OUTPUT},
    {83, GPIO_OUTPUT},
    {59, GPIO_INTPUT},
    {35, GPIO_INTPUT},
    {12, GPIO_INTPUT},
    {40, GPIO_INTPUT},
    {42, GPIO_INTPUT},
    {62, GPIO_INTPUT},
    {47, GPIO_INTPUT},
	{81, GPIO_INTPUT}
};

#define EPWM_PERIOD_K 40
CFG_PWM_TBL CfgPwmTbl_User[] =
{
   {
       {
           PWM1A
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM1B
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM2A
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM2B
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM3A
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM3B
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM4A
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM4B
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM5A
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM5B
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM6A
       },
       {
           EPWM_PERIOD_K
       }
   },
   {
       {
           PWM6B
       },
       {
           EPWM_PERIOD_K
       }
   }
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
            ENABLE_LOOP_BACK
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
        TIMER0,       //Timer moudule, timer0 timer1
        20000,         //timer period, unit:us
        120          //system frequency
    },
    {
        TIMER1, 
        20000,
        120
    }
};


CFG_INTERRUPT_TBL CfgInterruptTbl_User[] = 
{
    TIMER0_ISR,
    TIMER1_ISR,
    EPWM1,
    SCIBRX,
    SCIBTX,
    // SCICRX,
    // SCICTX
};

CFG_ADC_TBL CfgAdcTbl_User[] = 
{
    8
};
#endif /* MAIN_H_ */
