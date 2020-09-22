#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "main.h"
#include <stdlib.h>
#include "pf_isr.h"
#include "flash_hal.h"

/*
 *******
 * main.c
 * Test github pull request
 *******
*/
#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtest = 0;
Uint16 flashArrayW[4] = {0x0802, 0x1991, 0x1234, 0x5678};
Uint16 flashArrayR[4] = {0, 0, 0, 0};
int i = 0;
Uint16 *Resolver_read=(Uint16 *)0x100000;
Uint16 Resolver_result=0;
#endif

Uint32 gtArinc429SendWord = 1;
Uint32 gtArinc429ReadWord = 0;

int gTestcount = 0;
int gIsOcCnt = 0;
int gtest = 0;
Uint16 gP = 0;
int gIsOC = 0;
int gNoOC = 0;



void main(void)
{
	InitSysCtrl();

	Init_Sys_State_Service();
	Init_Spwm_Service();
    Init_Sci_Service();
	Init_Adc_Service();

	PFAL_ADC_CFG(CfgAdcTbl_User,sizeof(CfgAdcTbl_User)/sizeof(CfgAdcTbl_User[0]));		        //pass the test
	PFAL_GPIO_CFG(CfgGpioTbl_User,sizeof(CfgGpioTbl_User)/sizeof(CfgGpioTbl_User[0]));	        //pass the test
	PFAL_PWM_CFG(CfgPwmTbl_User,sizeof(CfgPwmTbl_User)/sizeof(CfgPwmTbl_User[0]));		        //pass the test
	PFAL_SCI_CFG(CfgSciTbl_User,sizeof(CfgSciTbl_User)/sizeof(CfgSciTbl_User[0]));		        //pass the test
	PFAL_SPI_CFG(CfgSpiTbl_User,sizeof(CfgSpiTbl_User)/sizeof(CfgSpiTbl_User[0]));              //pass the test
	PFAL_XINTF_CFG(CfgXintfTbl_User,sizeof(CfgXintfTbl_User)/sizeof(CfgXintfTbl_User[0]));  
	PFAL_TIMER_CFG(CfgTimerTbl_User,sizeof(CfgTimerTbl_User)/sizeof(CfgTimerTbl_User[0]));      //pass the test
	PFAL_INTERRUPT_CFG(CfgInterruptTbl_User,sizeof(CfgInterruptTbl_User)/sizeof(CfgInterruptTbl_User[0]));
	Disable_All_Epwms();
	HARDWARE_OVER_CURRENT_CLEAR();
//	TURN_ON_PWM_VALVE;
	ENABLE_GATE_DRIVER();

//	Init_Arinc429_Service();

#if(SYS_DEBUG == INCLUDE_FEATURE)
	DISABLE_GLOBAL_INTERRUPT;
	if(Flash_WR(0x330000, flashArrayW, sizeof(flashArrayW)) != STATUS_SUCCESS)
	{
		gtest |= 0x01;
	}

	if(Flash_RD(0x330000,flashArrayR, sizeof(flashArrayR)) != STATUS_SUCCESS)
	{
		gtest |= 0x02;
	}
	ENABLE_GLOBAL_INTERRUPT;
#endif

//	gtArinc429SendWord = 0x00002008 + 0x01010101;
	
	while(1)
	{
		gTestcount++;
		if(gTestcount == 1000){
			if(IS_HARDWARE_OC){
				HARDWARE_OVER_CURRENT_CLEAR();
				gIsOcCnt++;
				gTestcount = 0;
			}
			else{
				gTestcount = 0;
			}
		}

		DIGIT_SIG_ROUTING_INSPECTION();
#if(SYS_DEBUG == INCLUDE_FEATURE)
		PF_ProcessSciRxPacket(gScibRxQue);
		Resolver_result =(*Resolver_read) >> 6;
#else
        ProcessSciRxPacket(gScibRxQue);
#endif
		SYS_STATE_MACHINE;

        PackSciTxPacket(gScibTxQue,gSciTxVar);

//		Arinc429_WriteTxFIFO_ONE_WORD(gtArinc429SendWord);

//		if(!(Arinc429_ReadStatusReg() & 0x01))
//		{
//			gtArinc429ReadWord = Arinc429_ReadRxFIFO_ONE_WORD();
//			gtArinc429SendWord++;
//		}

        CheckEnableScibTx(gScibTxQue);
	}
}
