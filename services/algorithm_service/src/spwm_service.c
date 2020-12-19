#include "spwm_service.h"
#include <string.h>
#include <stdlib.h>
SPWM_PARA gSpwmPara = {0};

#define ZERO_MAX (2250)
#define ZERO_MIN (1840)

PWM_CURRENT_QUE* pwm_busCurrent_Que = NULL;

void Init_PWM_Buf(void)
{
	if(pwm_busCurrent_Que == NULL)
	{
		pwm_busCurrent_Que = (PWM_CURRENT_QUE*)malloc(sizeof(PWM_CURRENT_QUE));
		if(pwm_busCurrent_Que == NULL)
		{
			//TODO generate alarm
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		pwm_busCurrent_Que->front = 0;
		pwm_busCurrent_Que->rear = 0;
		pwm_busCurrent_Que->bufferLen = 128;
		pwm_busCurrent_Que->buffer = (Uint16*)malloc(sizeof(Uint16) * pwm_busCurrent_Que->bufferLen);
		if(pwm_busCurrent_Que->buffer == NULL)
		{
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		memset(pwm_busCurrent_Que->buffer, 0 , sizeof(pwm_busCurrent_Que->buffer));
	}
}

#pragma CODE_SECTION(PwmBusCurrentEnQueue, "ramfuncs")
int32 PwmBusCurrentEnQueue(Uint16 e, PWM_CURRENT_QUE *PWMBusCurrentQue)
{
//	static int isfull = 0;
	static int32 I_bus_Sum_tmp = 0;
	if((PWMBusCurrentQue->rear + 1) % (PWMBusCurrentQue->bufferLen) == PWMBusCurrentQue->front)
	{
		I_bus_Sum_tmp = I_bus_Sum_tmp - PWMBusCurrentQue->buffer[PWMBusCurrentQue->front];
		PWMBusCurrentQue->front = (PWMBusCurrentQue->front + 1) % (PWMBusCurrentQue->bufferLen);
//		isfull = 1;
	}
	else{
//		isbfull = 0;
	}

	PWMBusCurrentQue->buffer[PWMBusCurrentQue->rear] = e;
	I_bus_Sum_tmp = I_bus_Sum_tmp + PWMBusCurrentQue->buffer[PWMBusCurrentQue->rear];
	PWMBusCurrentQue->rear = (PWMBusCurrentQue->rear + 1) % (PWMBusCurrentQue->bufferLen);
	return I_bus_Sum_tmp;
}

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
		SET_HALL_ERROR_ALARM;
	}
	else{
		CLEAR_HALL_ERROR_ALARM;
	}
	return temp;
}


//static void FindSinTbl(int16 ct,int16 *psinvalue)
//{
//	if(ct < 1024)
//	{
//		*psinvalue = SDC_Sin_Tbl[ct]; 		/* 0--90*/
//	}
//	else if(ct < 2048)
//	{
//		*psinvalue = SDC_Sin_Tbl[2047-ct]; 	/* 90--180*/
//	}
//	else if(ct < 3072)
//	{
//		*psinvalue = -SDC_Sin_Tbl[ct-2048];	/* 180--270*/
//	}
//	else if(ct < 4096)
//	{
//		*psinvalue = -SDC_Sin_Tbl[4095-ct]; 	/* 270--360*/
//	}
//	else
//	{
//
//    }
//}

//void Calculate_Three_Phase_Duty(SPWM_PARA* spwmPara)
//{
//	   long ful;
//	   int16 pa,pb;
//       int16 ct = spwmPara->Rvdt_Pos;
//
//	   FindSinTbl(ct,&pa);
//
//	   ful = (long)pa * (long)spwmPara->Duty;
//	   spwmPara->Phase_Duty_U = (int16)(ful/32000);
//
//	   if((ct >= 0) && (ct <= 2047)){
//		    EPMW6_OUTPUT_UP(750, spwmPara->Phase_Duty_U);
//		    closeAL();
//		    openAH();
//	   }
//	   else if((ct >= 2048) && (ct < 4096)){
//		   EPMW6_OUTPUT_DOWN(750, spwmPara->Phase_Duty_U);
//		   closeAH();
//		   openAL();
//	   }
//	   else{
//		   closeAH();
//		   closeAL();
//	   }
//
//	   ct += 1365;
//	   if(ct > 4095) ct -= 4096;
//	   FindSinTbl(ct,&pb);
//	   ful = (long)pb * (long)spwmPara->Duty;
//	   spwmPara->Phase_Duty_V = (int16)(ful/32000);
//
//	   if((ct >= 0) && (ct <= 2047)){
//		   EPMW3_OUTPUT_UP(750, spwmPara->Phase_Duty_V);
//		   closeBL();
//		   openBH();
//	   }
//	   else if((ct >= 2048) && (ct < 4096)){
//		   EPMW3_OUTPUT_DOWN(750, spwmPara->Phase_Duty_V);
//		   closeBH();
//		   openBL();
//	   }
//	   else{
//		   closeBH();
//		   closeBL();
//	   }
//
//	   ct += 1365;
//	   if(ct > 4095) ct -= 4096;
//	   spwmPara->Phase_Duty_W = -(spwmPara->Phase_Duty_U + spwmPara->Phase_Duty_V);
//
//	   if((ct >= 0) && (ct <= 2047)){
//		   EPMW2_OUTPUT_UP(750, spwmPara->Phase_Duty_W);
//		   closeCL();
//		   openCH();
//	   }
//	   else if((ct >= 2048) && (ct < 4096)){
//		   EPMW2_OUTPUT_DOWN(750, spwmPara->Phase_Duty_W);
//		   closeCH();
//		   openCL();
//	   }
//	   else{
//		   closeCH();
//		   closeCL();
//	   }
////	   ful = (long)pa * (long)spwmPara->Duty;
////	   spwmPara->Phase_Duty_U = (int16)(ful/32000);
//}


#pragma CODE_SECTION(SwitchDirection, "ramfuncs")
void SwitchDirection(SPWM_PARA* spwmPara){
    //1:A 2:B 3:C
    switch (spwmPara->CurrentHallPosition) {
        case 4://C+ --------------->A-
        	if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
            	closeBL(); closeAH(); closeCL(); closeBH();
    			EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
    			EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
    			openCH(); openAL();
        	}
			else if(5 == spwmPara->LastHalllPosition){
	        	closeBL(); closeAH(); closeCL(); closeBH();
				EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
				EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
				openCH(); openAL();
			}
			else{
				SET_PAHSE_CHANGE_ALARM;
				DIABLE_ALL();
			}
            break;
        case 6://C+ --------------->B-
        	if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeAH(); closeBH(); closeCL(); closeAL();
    			EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
    			EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
    			openCH(); openBL();
        	}
			else if(4 == spwmPara->LastHalllPosition){
	            closeAH(); closeBH(); closeCL(); closeAL();
				EPMW3_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
				EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
				openCH(); openBL();
			}
			else{
				SET_PAHSE_CHANGE_ALARM;
				DIABLE_ALL();
			}
            break;
        case 2://A+ --------------->B-
        	if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeCL(); closeBH(); closeAL(); closeCH();
    			EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
    			EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
    			openAH(); openBL();
        	}
			else if(6 == spwmPara->LastHalllPosition){
	            closeCL(); closeBH(); closeAL(); closeCH();
				EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
				EPMW2_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
				openAH(); openBL();
			}
			else{
				SET_PAHSE_CHANGE_ALARM;
				DIABLE_ALL();
			}
            break;
        case 3://A+ --------------->C-
        	if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeBH(); closeCH(); closeAL(); closeBL();
    			EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
    			EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
    			openAH(); openCL();
        	}
			else if(2 == spwmPara->LastHalllPosition){
	            closeBH(); closeCH(); closeAL(); closeBL();
				EPMW1_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
				EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
				openAH(); openCL();
			}
			else{
				SET_PAHSE_CHANGE_ALARM;
				DIABLE_ALL();
			}
            break;
        case 1://B+ --------------->C-
        	if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeAL(); closeBL(); closeCH(); closeAH();
    			EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
    			EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
    			openBH(); openCL();
        	}
			else if(3 == spwmPara->LastHalllPosition){
	            closeAL(); closeBL(); closeCH(); closeAH();
				EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
				EPMW3_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
				openBH(); openCL();
			}
			else{
				SET_PAHSE_CHANGE_ALARM;
				DIABLE_ALL();
			}
            break;
        case 5://B+ --------------->A-
        	if(spwmPara->CurrentHallPosition == spwmPara->LastHalllPosition){
                closeCH(); closeAH(); closeBL(); closeCL();
    			EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
    			EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
    			openBH(); openAL();
        	}
			else if(1 == spwmPara->LastHalllPosition){
	            closeCH(); closeAH(); closeBL(); closeCL();
				EPMW2_OUTPUT_UP(PWM_DUTY_BASE, spwmPara->Duty);
				EPMW1_OUTPUT_DOWN(PWM_DUTY_BASE, spwmPara->Duty);
				openBH(); openAL();
			}
			else{
				SET_PAHSE_CHANGE_ALARM;
				DIABLE_ALL();
			}
            break;
        default:
        	Disable_All_Epwms();
        	SET_HALL_ERROR_ALARM;
            break;
    }
}

//#pragma CODE_SECTION(OverCurrentSoftProtect, "ramfuncs")
//void OverCurrentSoftProtect(SPWM_PARA* spwmPara){
//	if(1 == spwmPara->restrictduty){
//		spwmPara->Duty_Gradual = spwmPara->Duty_Gradual - 7;
//	}
//	else{
//		spwmPara->Duty_Gradual = spwmPara->Duty_Gradual;
//	}
//}

#pragma CODE_SECTION(Duty_Gradual_Change, "ramfuncs")
void Duty_Gradual_Change (SPWM_PARA* spwmPara){
	double currSpeed;
	int16 CurrentCompensate;

	currSpeed = gEcapPara.gMotorSpeedEcap;
	CurrentCompensate = gSpwmPara.CurrentCompensateDuty;
	spwmPara->lastDuty = spwmPara->Duty;

	if(currSpeed < 0) currSpeed = 0;
	else if(currSpeed > 6000) currSpeed = 6000;
	else; /*DO NOTHING*/
	/*占空比缓变开始*/

	if(1 == spwmPara->restrictduty){
		if(spwmPara->TargetDuty > (spwmPara->lastDuty - 3)){
			spwmPara->Duty_Gradual = spwmPara->lastDuty - 3;
		}
		else{
			spwmPara->Duty_Gradual = spwmPara->TargetDuty;
		}
	}
	else{
		spwmPara->StepMaxDuty = (int16)((K_MAXDUTY * currSpeed + B_MAXDUTY + CurrentCompensate) * spwmPara->BusVolt_Ratio);
		if(spwmPara->TargetDuty > spwmPara->StepMaxDuty){
			spwmPara->Duty_Gradual_mid = spwmPara->StepMaxDuty;

		}
		else{
			spwmPara->Duty_Gradual_mid = spwmPara->TargetDuty;
		}

		if(spwmPara->lastDuty >= spwmPara->Duty_Gradual_mid){
            spwmPara->DutyMinusIntervalCnt = spwmPara->DutyMinusIntervalCnt + 1;
            if(spwmPara->DutyMinusIntervalCnt > spwmPara->DutyMinusInterval){
                spwmPara->DutyMinusIntervalCnt = 0;
                spwmPara->Duty_Gradual = spwmPara->lastDuty - 1;
            }
            else{
                spwmPara->Duty_Gradual = spwmPara->lastDuty;
            }
		}
		else{
			spwmPara->DutyAddIntervalCnt = spwmPara->DutyAddIntervalCnt + 1;
			if(spwmPara->DutyAddIntervalCnt > spwmPara->DutyAddInterval){
				spwmPara->DutyAddIntervalCnt = 0;
				spwmPara->Duty_Gradual = spwmPara->lastDuty + 1;
			}
			else{
				spwmPara->Duty_Gradual = spwmPara->lastDuty;
			}
		}
	}

	if(spwmPara->Duty_Gradual > spwmPara->ThresholdDutyP) spwmPara->Duty_Gradual = spwmPara->ThresholdDutyP;
	else if(spwmPara->Duty_Gradual < spwmPara->ThresholdDutyN) spwmPara->Duty_Gradual = spwmPara->ThresholdDutyN;

	spwmPara->Duty = spwmPara->Duty_Gradual;
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
		Pwm_Init_BIT(spwmPara);
		break;
	case SYS_FORWARD_RUN:
		BridgeABC_Current_Monitor_BIT();
		PwrBus_OverVoltage_BIT();
		break;
	case SYS_STOP:
	case SYS_ALARM:
		DIABLE_ALL();
		BridgeABC_Current_Monitor_BIT();
		PwrBus_OverVoltage_BIT();
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
	static int cnt_battle = 0;
	GpioDataRegs.GPBSET.bit.GPIO50 = 1; /*线程监视*/
	spwmPara->LastHalllPosition = spwmPara->CurrentHallPosition;
	spwmPara->CurrentHallPosition = GetCurrentHallValue();
	spwmPara->pwmSM = gSysStateFlag.sysRunningState;
	if(IS_HARDWARE_OC) {
		DIABLE_ALL();
		SET_SYS_BUS_CURRENT_ALARM;
		SET_BUS_OVER_CURT_PROT;
//		gCnt_Clear = 1;
//		spwmPara->pwmSM = PWM_ALARM;
	}

    UpdateSingleAnalog(&gSysAnalogVar); /*读取16通道ADC转换结果*/

    if(IS_HALL_ERROR_ALARM || IS_PAHSE_CHANGE_ALARM) SET_MOTOR_HALL_PROT;
    else CLEAR_MOTOR_HALL_PROT;

	Spwm_HighSpeed_BIT(spwmPara);
	if(gSciAppProtocolRx_J150.workMode == WORK_MODE_NORMAL){
		if(IS_SYS_ALARM){
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
		if(cnt_battle == 0){
			GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;
			cnt_battle = 1;
		}
		else{
			GpioDataRegs.GPASET.bit.GPIO12 = 1;
			cnt_battle = 0;
		}
		if(IS_SYS_BUS_CURRENT_ALARM || IS_HALL_ERROR_ALARM){
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
	GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1; /*线程监视*/
}

void Init_Spwm_Service(void)
{
	gSpwmPara.Duty = 0;
//	gSpwmPara.Phase_Duty_U = 0;
//	gSpwmPara.Phase_Duty_V = 0;
//	gSpwmPara.Phase_Duty_W = 0;
//	gSpwmPara.Rvdt_Current_Pos = 0;
//	gSpwmPara.Rvdt_Pos = 0;
//	gSpwmPara.Rvdt_Zero = 1500;
	gSpwmPara.Duty_Gradual = 0;
	gSpwmPara.Duty_Gradual_mid = 0;
	gSpwmPara.DutyAddInterval = 12;//15;
	gSpwmPara.DutyAddIntervalCnt = 0;
    gSpwmPara.DutyMinusInterval = 12;   //10
    gSpwmPara.DutyMinusIntervalCnt = 0;
	gSpwmPara.lastDuty = 0;
	gSpwmPara.StepMaxDuty = 0;
	gSpwmPara.BusVolt_Ratio = 0.794;
	gSpwmPara.ThresholdDutyP = 1250;
	gSpwmPara.ThresholdDutyN = 0;
	gSpwmPara.OpenLoopDuty = 0;
	gSpwmPara.CloseLoopDuty = 0;
	gSpwmPara.CurrentCompensateDuty = 0;
	gSpwmPara.CurrentHallPosition = 0;
	gSpwmPara.LastHalllPosition = 0;
	gSpwmPara.TargetDuty = 0;
	gSpwmPara.pwmSM = SYS_INIT;
	gSpwmPara.restrictduty = 0;
	gSpwmPara.Cnt_PWM_Init_BIT = 0;
}
