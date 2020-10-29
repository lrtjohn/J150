#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "main.h"
#include <stdlib.h>
#include "pf_isr.h"
#ifdef FLASH_PROGRAM
#include "flash_hal.h"
#endif
/*
 *******
 * main.c
 *******
*/
#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtest = 0;
Uint16 flashArrayW[4] = {0x0802, 0x1991, 0x1234, 0x5678};
Uint16 flashArrayR[4] = {0, 0, 0, 0};
int i = 0;
#endif

Uint32 gtArinc429SendWord = 0x00002008 + 0x01010101;
Uint32 gtArinc429ReadWord = 0;

int gTestcount = 0;
int gIsOcCnt = 0;

void main(void)
{
	InitSysCtrl(); /*禁止内部看门狗，初始化锁相环，外围时钟及FLASH*/

	DISABLE_GATE_DRIVER(); /*禁止驱动芯片*/
	DISABLE_BUSBAR_VOLTAGE; /*断开母线开关*/
	Disable_All_Epwms(); /*PWM开关禁止*/
	DISABLE_SW_BREAK; /*禁止泄放*/

	/*设置PWM管脚为GPIO输出时的安全电平*/
	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;

	Init_Sys_State_Service(); /*状态机等变量初始化*/
	Init_Spwm_Service(); /*PWM事件管理器相关变量初始化*/
    Init_Sci_Service(); /*初始化SCI接收和发送环形队列，初始化协议层接收和发送函数指针，初始化物理层接收和发送函数指针*/
	Init_Adc_Service(); /*初始化所有ADC变量*/
	Init_gKF_Speed(); /*初始化卡尔曼滤波全局变量*/
	Init_PID_Service(); /*初始化PID全局变量*/
	Init_OpenLoop_Service();/*初始化开环全局变量*/
	Init_Timer0_Buf(); /*初始化5ms中断中母线电压环形队列变量*/
//	Init_ECap_Service();

	/*ADC事件管理器配置*/
	PFAL_ADC_CFG(CfgAdcTbl_User,sizeof(CfgAdcTbl_User)/sizeof(CfgAdcTbl_User[0]));		        			// pass the test
	/*GPIO事件管理器配置*/
	PFAL_GPIO_CFG(CfgGpioTbl_User,sizeof(CfgGpioTbl_User)/sizeof(CfgGpioTbl_User[0]));	        			// pass the test
	/*PWM事件管理器配置*/
	PFAL_PWM_CFG(CfgPwmTbl_User,sizeof(CfgPwmTbl_User)/sizeof(CfgPwmTbl_User[0]));		        			// pass the test
	/*ECAP事件管理器配置*/
	PFAL_ECAP_CFG(CfgECapTbl_User, sizeof(CfgECapTbl_User)/sizeof(CfgECapTbl_User[0]));
	/*SCI事件管理器配置*/
	PFAL_SCI_CFG(CfgSciTbl_User,sizeof(CfgSciTbl_User)/sizeof(CfgSciTbl_User[0]));		        			// pass the test
	/*SPI事件管理器配置*/
	PFAL_SPI_CFG(CfgSpiTbl_User,sizeof(CfgSpiTbl_User)/sizeof(CfgSpiTbl_User[0]));              			// pass the test
//	PFAL_XINTF_CFG(CfgXintfTbl_User,sizeof(CfgXintfTbl_User)/sizeof(CfgXintfTbl_User[0]));  				// pass the test
	/*定时器0，1事件管理器配置*/
	PFAL_TIMER_CFG(CfgTimerTbl_User,sizeof(CfgTimerTbl_User)/sizeof(CfgTimerTbl_User[0]));      			// pass the test

	/*PUBIT上电自检*/
	/*VDD5V不查，硬件过流不查，270V不查*/
	/*已知固定电平的数字输入管脚检查，AD采集的电流信号是否越界，电流的AD零位是否越界，温度信号是否越界，其余电压PG是否正常*/

	ENABLE_DRIVERS(); /*等待VDD5V完成上电后清除硬件过流及使能RS422*/
	/*检查硬件过流故障是否存在，如果存在，对硬件过流故障置位*/
	/*检查270V，对母线电压欠压故障置位*/
	/*中断配置使能*/
	PFAL_INTERRUPT_CFG(CfgInterruptTbl_User,sizeof(CfgInterruptTbl_User)/sizeof(CfgInterruptTbl_User[0]));
	
	while(1)
	{
		/*补周期BIT*/
//		gTestcount++;
//		if (gTestcount == 1000){
//			if (IS_HARDWARE_OC){
//				HARDWARE_OVER_CURRENT_CLEAR();
//				gIsOcCnt++;
//				gTestcount = 0;
//			}
//			else {
//				gTestcount = 0;
//			}
//		}
//		gSciAppProtocolTx_J150.currentSpeed = gIsOcCnt;
		DIGIT_SIG_ROUTING_INSPECTION();

#if(SYS_DEBUG == INCLUDE_FEATURE)
		PF_ProcessSciRxPacket(gScibRxQue);
        ProcessSciRxPacket(gScibRxQue);
#else
		SCI_RX_UnpackData(gScibRxQue);
#endif

#if(J150_SCI_PROTOCOL_TX == NOT_INCLUDE_FEATURE)
        PackSciTxPacket(gScibTxQue,gSciTxVar);
#endif

#if (ARINC429_FEATURE == INCLUDE_FEATURE)
		Arinc429_WriteTxFIFO_ONE_WORD(gtArinc429SendWord);

		if (!(Arinc429_ReadStatusReg() & 0x01))
		{
			gtArinc429ReadWord = Arinc429_ReadRxFIFO_ONE_WORD();
			gtArinc429SendWord++;
		}
#endif

	}
}
