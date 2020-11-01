#include "spwm_service.h"
SPWM_PARA gSpwmPara = {0};

#define ZERO_MAX (2100)
#define ZERO_MIN (1900)

inline void openAH(void){
	EPwm1Regs.AQCSFRC.bit.CSFA = 3;
}

inline void closeAH(void){
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
}

inline void openAL(void){
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;
}

inline void closeAL(void){
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
}

inline void openBH(void){
	EPwm2Regs.AQCSFRC.bit.CSFA = 3;
}

inline void closeBH(void){
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
}
inline void openBL(void){
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;
}

inline void closeBL(void){
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
}

inline void openCH(void){
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;
}

inline void closeCH(void){
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
}
inline void openCL(void){
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;
}

inline void closeCL(void){
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;
}

/**************************************************************
 *Name:						GetCurrentHallValue
 *Function:
 *Input:					none
 *Output:					none
 *Author:					Simon
 *Date:						2018.10.31
 **************************************************************/
Uint16 GetCurrentHallValue(void){

	Uint16 temp;
	Uint16 a;
	Uint16 b;
	Uint16 c;

	a = GpioDataRegs.GPADAT.bit.GPIO27;
	b = GpioDataRegs.GPADAT.bit.GPIO26;
	c = GpioDataRegs.GPADAT.bit.GPIO25;

	temp = ((a << 2) + (b << 1) + c);

	if(temp < 1 || temp >6){
//		gSysState.erro.bit.software = 1;
	}
	return temp;
}


static void FindSinTbl(int16 ct,int16 *psinvalue)
{
	if(ct < 1024)
	{
		*psinvalue = SDC_Sin_Tbl[ct]; 		/* 0--90*/
	}
	else if(ct < 2048)
	{
		*psinvalue = SDC_Sin_Tbl[2047-ct]; 	/* 90--180*/
	}
	else if(ct < 3072)
	{
		*psinvalue = -SDC_Sin_Tbl[ct-2048];	/* 180--270*/
	}
	else if(ct < 4096)
	{
		*psinvalue = -SDC_Sin_Tbl[4095-ct]; 	/* 270--360*/
	}
	else
	{

    }
}

void Calculate_Three_Phase_Duty(SPWM_PARA* spwmPara)
{
	   long ful;
	   int16 pa,pb;
       int16 ct = spwmPara->Rvdt_Pos;

	   FindSinTbl(ct,&pa);

	   ful = (long)pa * (long)spwmPara->Duty;
	   spwmPara->Phase_Duty_U = (int16)(ful/32000);

	   if((ct >= 0) && (ct <= 2047)){
		    EPMW6_OUTPUT_UP(750, spwmPara->Phase_Duty_U);
		    closeAL();
		    openAH();
	   }
	   else if((ct >= 2048) && (ct < 4096)){
		   EPMW6_OUTPUT_DOWN(750, spwmPara->Phase_Duty_U);
		   closeAH();
		   openAL();
	   }
	   else{
		   closeAH();
		   closeAL();
	   }

	   ct += 1365;
	   if(ct > 4095) ct -= 4096;
	   FindSinTbl(ct,&pb);
	   ful = (long)pb * (long)spwmPara->Duty;
	   spwmPara->Phase_Duty_V = (int16)(ful/32000);

	   if((ct >= 0) && (ct <= 2047)){
		   EPMW3_OUTPUT_UP(750, spwmPara->Phase_Duty_V);
		   closeBL();
		   openBH();
	   }
	   else if((ct >= 2048) && (ct < 4096)){
		   EPMW3_OUTPUT_DOWN(750, spwmPara->Phase_Duty_V);
		   closeBH();
		   openBL();
	   }
	   else{
		   closeBH();
		   closeBL();
	   }

	   ct += 1365;
	   if(ct > 4095) ct -= 4096;
	   spwmPara->Phase_Duty_W = -(spwmPara->Phase_Duty_U + spwmPara->Phase_Duty_V);

	   if((ct >= 0) && (ct <= 2047)){
		   EPMW2_OUTPUT_UP(750, spwmPara->Phase_Duty_W);
		   closeCL();
		   openCH();
	   }
	   else if((ct >= 2048) && (ct < 4096)){
		   EPMW2_OUTPUT_DOWN(750, spwmPara->Phase_Duty_W);
		   closeCH();
		   openCL();
	   }
	   else{
		   closeCH();
		   closeCL();
	   }
//	   ful = (long)pa * (long)spwmPara->Duty;
//	   spwmPara->Phase_Duty_U = (int16)(ful/32000);
}


#pragma CODE_SECTION(SwitchDirection, "ramfuncs")
void SwitchDirection(SPWM_PARA* spwmPara){
	int16 middleDuty;

	middleDuty = ((spwmPara->Duty) >> 1) + 1;
	spwmPara->LastHalllPosition = spwmPara->CurrentHallPosition;
	spwmPara->CurrentHallPosition = GetCurrentHallValue();
    //1:A 2:B 3:C
    switch (spwmPara->CurrentHallPosition) {
        case 4://C+ --------------->A-
        	closeBH(); closeAH(); closeCL();
            if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeBL();
            	EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
                openCH(); openAL();
            }
            else if(6 == spwmPara->LastHalllPosition){
            	EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, middleDuty);
                openCH();
                openAL();
                openBL();
            }
            else{
            	Disable_All_Epwms();
//	                gSysInfo.hallErrorCount++;
            }
            break;
        case 6://C+ --------------->B-
            closeAL(); closeBH(); closeCL();
            if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeAH();
            	EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
                openCH(); openBL();
            }
            else if(2 == spwmPara->LastHalllPosition){
            	EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW1_OUTPUT_UP(PWM_DUTY_BASE, middleDuty);
                openCH(); openBL(); openAH();
            }
            else{
            	Disable_All_Epwms();
//	                gSysInfo.hallErrorCount++;
            }
            break;
        case 2://A+ --------------->B-
            closeCH(); closeBH(); closeAL();
            if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeCL();
            	EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
                openAH(); openBL();
            }
            else if(3 == spwmPara->LastHalllPosition){
            	EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, middleDuty);
                openAH(); openBL(); openCL();
            }
            else{
            	Disable_All_Epwms();
//                gSysInfo.hallErrorCount++;
            }
            break;
        case 3://A+ --------------->C-
            closeBL(); closeCH(); closeAL();
            if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeBH();
            	EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
                openAH(); openCL();
            }
            else if(1 == spwmPara->LastHalllPosition){
            	EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW2_OUTPUT_UP(PWM_DUTY_BASE, middleDuty);
                openAH(); openCL(); openBH();
            }
            else{
            	Disable_All_Epwms();
//	                gSysInfo.hallErrorCount++;
            }
            break;
        case 1://B+ --------------->C-
            closeAH(); closeBL(); closeCH();
            if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeAL();
            	EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
                openBH(); openCL();
            }
            else if(5 == spwmPara->LastHalllPosition){
            	EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, middleDuty);
                openBH(); openCL(); openAL();
            }
            else{
            	Disable_All_Epwms();
//	                gSysInfo.hallErrorCount++;
            }
            break;
        case 5://B+ --------------->A-
            closeCL(); closeAH(); closeBL();
            if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeCH();
            	EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
                openBH(); openAL();
            }
            else if(4 == spwmPara->LastHalllPosition){
            	EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
            	EPMW3_OUTPUT_UP(PWM_DUTY_BASE, middleDuty);
                openBH(); openAL(); openCH();
            }
            else{
            	Disable_All_Epwms();
//	                gSysInfo.hallErrorCount++;
            }
            break;
        default:
        	Disable_All_Epwms();
            break;
    }
}

void OverCurrentSoftProtect(SPWM_PARA* spwmPara){
	if(1 == spwmPara->restrictduty){
		spwmPara->Duty_Gradual = spwmPara->Duty_Gradual - 7;
	}
	else{
		spwmPara->Duty_Gradual = spwmPara->Duty_Gradual;
	}
}

#pragma CODE_SECTION(Duty_Gradual_Change, "ramfuncs")
void Duty_Gradual_Change (SPWM_PARA* spwmPara){
	/*占空比缓变开始*/
	++(spwmPara->DutyAddIntervalCnt); /*缓变频数计数*/
	if(spwmPara->DutyAddIntervalCnt >= spwmPara->DutyAddInterval){

	spwmPara->DutyAddIntervalCnt = 0;

	if(spwmPara->Duty_Gradual > spwmPara->TargetDuty){
			spwmPara->Duty_Gradual = spwmPara->TargetDuty;
    }
    else if(spwmPara->Duty_Gradual < spwmPara->TargetDuty){
    	if((spwmPara->Duty_Gradual + spwmPara->Ddtmax) > spwmPara->TargetDuty){
    		spwmPara->Duty_Gradual = spwmPara->TargetDuty;
    	}
    	else{
    		spwmPara->Duty_Gradual = spwmPara->Duty_Gradual + spwmPara->Ddtmax;
    	}
    }
    else{
           //nothing need change
    }

	OverCurrentSoftProtect(spwmPara);

   	if(spwmPara->Duty_Gradual > spwmPara->ThresholdDutyP) spwmPara->Duty_Gradual = spwmPara->ThresholdDutyP;
   	else if(spwmPara->Duty_Gradual < spwmPara->ThresholdDutyN) spwmPara->Duty_Gradual = spwmPara->ThresholdDutyN;

	spwmPara->Duty = spwmPara->Duty_Gradual;
	}
}

#pragma CODE_SECTION(Pwm_Init_BIT, "ramfuncs")
void Pwm_Init_BIT(SPWM_PARA* spwmPara){
	if(spwmPara->Cnt_PWM_Init_BIT <= (CNT_INIT_END + 10)) ++spwmPara->Cnt_PWM_Init_BIT;
	if(spwmPara->Cnt_PWM_Init_BIT <= 60){
		/*DO NOTHING*/
	}
	else if(spwmPara->Cnt_PWM_Init_BIT <= 124){
		gCurrent_Struct.zerosum_IABC[0] = gSysAnalogVar.single.var[updateBridgeCurrentA].value + gCurrent_Struct.zerosum_IABC[0];
		gCurrent_Struct.zerosum_IABC[1] = gSysAnalogVar.single.var[updateBridgeCurrentB].value + gCurrent_Struct.zerosum_IABC[1];
		gCurrent_Struct.zerosum_IABC[2] = gSysAnalogVar.single.var[updateBridgeCurrentC].value + gCurrent_Struct.zerosum_IABC[2];
	}
	else if(spwmPara->Cnt_PWM_Init_BIT == 125){
		gCurrent_Struct.zero_IABC[0] = gCurrent_Struct.zerosum_IABC[0] >> 6;
		gCurrent_Struct.zero_IABC[1] = gCurrent_Struct.zerosum_IABC[1] >> 6;
		gCurrent_Struct.zero_IABC[2] = gCurrent_Struct.zerosum_IABC[2] >> 6;
	}
	else if(spwmPara->Cnt_PWM_Init_BIT == 126){
		if((gCurrent_Struct.zero_IABC[0] > ZERO_MAX) || (gCurrent_Struct.zero_IABC[0] < ZERO_MIN) ||
		   (gCurrent_Struct.zero_IABC[1] > ZERO_MAX) || (gCurrent_Struct.zero_IABC[1] < ZERO_MIN) ||
		   (gCurrent_Struct.zero_IABC[2] > ZERO_MAX) || (gCurrent_Struct.zero_IABC[2] < ZERO_MIN))
		{
			SET_HW_CURRENT_ZERO_ALARM;/*改报警位*/
		}
	}
	else if(spwmPara->Cnt_PWM_Init_BIT <= CNT_INIT_END){
		BridgeABC_Current_Monitor_BIT();
		PwrBus_OverVoltage_BIT();
	}
	else{
		/*no use*/
	}

}

#pragma CODE_SECTION(Spwm_HighSpeed_BIT, "ramfuncs")
void Spwm_HighSpeed_BIT(SPWM_PARA* spwmPara){
	switch(spwmPara->pwmSM){
	case SYS_INIT:
		DIABLE_ALL();
		CLEAR_SW_PWM_ISR_ALARM;
		Pwm_Init_BIT(spwmPara);
		break;
	case SYS_FORWARD_RUN:
		BridgeABC_Current_Monitor_BIT();
		PwrBus_OverVoltage_BIT();
		CLEAR_SW_PWM_ISR_ALARM;
		break;
	case SYS_STOP:
	case SYS_ALARM:
		DIABLE_ALL();
		BridgeABC_Current_Monitor_BIT();
		PwrBus_OverVoltage_BIT();
		CLEAR_SW_PWM_ISR_ALARM;
		break;
	default:
		SET_SW_PWM_ISR_ALARM;
		Disable_All_Epwms();
		break;
	}
}

#pragma CODE_SECTION(Spwm_Output, "ramfuncs")
void Spwm_Output(SPWM_PARA* spwmPara) /*PWM中断函数*/
{
	GpioDataRegs.GPBSET.bit.GPIO50 = 1; /*线程监视*/
	spwmPara->pwmSM = gSysStateFlag.sysRunningState;
	if(!IS_HARDWARE_OC) {
		DIABLE_ALL();
		SET_SYS_BUS_CURRENT_ALARM;
//		spwmPara->pwmSM = PWM_ALARM;
	}

    UpdateSingleAnalog(&gSysAnalogVar); /*读取16通道ADC转换结果*/

	Spwm_HighSpeed_BIT(spwmPara);
	if(gSysStateFlag.j150WorkMode == NORMAL){
		if(gSysStateFlag.alarm.all){
			DIABLE_ALL();
		}
		else{
			if(spwmPara->pwmSM == SYS_FORWARD_RUN){
				Duty_Gradual_Change(spwmPara);
				SwitchDirection(spwmPara);
			}
			else{
				DIABLE_ALL();
			}
		}
	}
	else{
		/*战时*/
	}
	GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1; /*线程监视*/
}

void Init_Spwm_Service(void)
{
	gSpwmPara.Duty = 0;
	gSpwmPara.Phase_Duty_U = 0;
	gSpwmPara.Phase_Duty_V = 0;
	gSpwmPara.Phase_Duty_W = 0;
	gSpwmPara.Rvdt_Current_Pos = 0;
	gSpwmPara.Rvdt_Pos = 0;
	gSpwmPara.Rvdt_Zero = 1500;
	gSpwmPara.Duty_Gradual = 0;
	gSpwmPara.DutyAddInterval = 1000;
	gSpwmPara.DutyAddIntervalCnt = 0;
	gSpwmPara.Ddtmax = 1;
	gSpwmPara.ThresholdDutyP = 600;
	gSpwmPara.ThresholdDutyN = -600;
	gSpwmPara.OpenLoopDuty = 0;
	gSpwmPara.CloseLoopDuty = 0;
	gSpwmPara.CurrentHallPosition = 0;
	gSpwmPara.LastHalllPosition = 0;
	gSpwmPara.TargetDuty = 0;
	gSpwmPara.pwmSM = SYS_INIT;
	gSpwmPara.restrictduty = 0;
	gSpwmPara.Cnt_PWM_Init_BIT = 0;
}
