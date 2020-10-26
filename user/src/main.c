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
	InitSysCtrl();

	Init_Sys_State_Service();
	Init_Spwm_Service();
    Init_Sci_Service();
	Init_Adc_Service();
	Init_gKF_Speed();
	Init_PID_Service();
	Init_OpenLoop_Service();
	Init_Timer0_Buf();
//	Init_ECap_Service();

	PFAL_ADC_CFG(CfgAdcTbl_User,sizeof(CfgAdcTbl_User)/sizeof(CfgAdcTbl_User[0]));		        			// pass the test
	PFAL_GPIO_CFG(CfgGpioTbl_User,sizeof(CfgGpioTbl_User)/sizeof(CfgGpioTbl_User[0]));	        			// pass the test
	PFAL_PWM_CFG(CfgPwmTbl_User,sizeof(CfgPwmTbl_User)/sizeof(CfgPwmTbl_User[0]));		        			// pass the test
	PFAL_ECAP_CFG(CfgECapTbl_User, sizeof(CfgECapTbl_User)/sizeof(CfgECapTbl_User[0]));
	PFAL_SCI_CFG(CfgSciTbl_User,sizeof(CfgSciTbl_User)/sizeof(CfgSciTbl_User[0]));		        			// pass the test
	PFAL_SPI_CFG(CfgSpiTbl_User,sizeof(CfgSpiTbl_User)/sizeof(CfgSpiTbl_User[0]));              			// pass the test
//	PFAL_XINTF_CFG(CfgXintfTbl_User,sizeof(CfgXintfTbl_User)/sizeof(CfgXintfTbl_User[0]));  				// pass the test
	PFAL_TIMER_CFG(CfgTimerTbl_User,sizeof(CfgTimerTbl_User)/sizeof(CfgTimerTbl_User[0]));      			// pass the test
	PFAL_INTERRUPT_CFG(CfgInterruptTbl_User,sizeof(CfgInterruptTbl_User)/sizeof(CfgInterruptTbl_User[0]));
	Disable_All_Epwms();
//	TURN_ON_PWM_VALVE;
	ENABLE_DRIVERS();

#if (ARINC429_FEATURE == INCLUDE_FEATURE)
	Init_Arinc429_Service();
#endif

#if(SYS_DEBUG == INCLUDE_FEATURE)
	DISABLE_GLOBAL_INTERRUPT;
	if (Flash_WR(0x330000, flashArrayW, sizeof(flashArrayW)) != STATUS_SUCCESS)
	{
		gtest |= 0x01;
	}

	if (Flash_RD(0x330000,flashArrayR, sizeof(flashArrayR)) != STATUS_SUCCESS)
	{
		gtest |= 0x02;
	}
	ENABLE_GLOBAL_INTERRUPT;
#endif

	
	while(1)
	{
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

        CheckEnableScibTx(gScibTxQue);
	}
}
