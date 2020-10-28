#include "spwm_service.h"
SPWM_PARA gSpwmPara = {0};

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



void Spwm_Output(SPWM_PARA* spwmPara)
{
	GpioDataRegs.GPBDAT.bit.GPIO50 = 1;
	updateAndCheckVoltage();
//	spwmPara->TargetDuty = spwmPara->OpenLoopDuty;
//	spwmPara->TargetDuty = gDebugDataArray[0];
//	spwmPara->TargetDuty = spwmPara->CloseLoopDuty;
#if(SPWM_DUTY_GRADUAL_CHANGE == INCLUDE_FEATURE)
	++(spwmPara->DutyAddIntervalCnt);
	if(spwmPara->DutyAddIntervalCnt >= spwmPara->DutyAddInterval){

	spwmPara->DutyAddIntervalCnt = 0;

	if(spwmPara->Duty_Gradual > spwmPara->TargetDuty){
		if((spwmPara->Duty_Gradual - spwmPara->Ddtmax) < spwmPara->TargetDuty){
			spwmPara->Duty_Gradual = spwmPara->TargetDuty;
		}
		else{
			spwmPara->Duty_Gradual = spwmPara->Duty_Gradual - spwmPara->Ddtmax;
		}
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

   	if(spwmPara->Duty_Gradual > spwmPara->ThresholdDutyP)
	{
    	spwmPara->Duty_Gradual = spwmPara->ThresholdDutyP;
   	}
   	else if(spwmPara->Duty_Gradual < spwmPara->ThresholdDutyN)
	{
       	spwmPara->Duty_Gradual = spwmPara->ThresholdDutyN;
   	}

	spwmPara->Duty = spwmPara->Duty_Gradual;
	}
#endif

#if(SPWM_DUTY_GRADUAL_CHANGE == EXCLUDE_FEATURE)
    spwmPara->Duty = spwmPara->TargetDuty;
#endif

#if(PF_PWM_RVDT == INCLUDE_FEATURE)
    spwmPara->Rvdt_Current_Pos = Get_RVDT_Position(SDB_RVDT_Read_Addr);

    spwmPara->Rvdt_Pos = spwmPara->Rvdt_Current_Pos - spwmPara->Rvdt_Zero;

	if(spwmPara->Rvdt_Pos < 0)
	{
		spwmPara->Rvdt_Pos += 4096;
	}
	else if(spwmPara->Rvdt_Pos > 4095)
	{
		spwmPara->Rvdt_Pos -= 4096;
	}
	else
	{
        //TODO generate alarm
    }

	if(gSwitch)
	{
		Calculate_Three_Phase_Duty(spwmPara);
	}
	else
	{
		Disable_All_Epwms();
	}
#endif

//	gSciAppProtocolTx_J150.RFU = spwmPara->Duty;
//	gSciAppProtocolTx_J150.RFU = gSysStateFlag.sysRunningState;
	gSciAppProtocolTx_J150.RFU = gSysStateFlag.alarm.all;

	if(IS_SYS_RUNNING_STATE_FORWARD_RUN)
	{
#if(PF_PWM_ECAP == INCLUDE_FEATURE)
	SwitchDirection(spwmPara);
#endif
	}
	else{
		DISABLE_GATE_DRIVER();
		Disable_All_Epwms();
	}


//    EPMW2_OUTPUT_DUAL_PLOARITY(750, spwmPara->Phase_Duty_W);
//    EPMW3_OUTPUT_DUAL_PLOARITY(750, spwmPara->Phase_Duty_V);
//    EPMW6_OUTPUT_DUAL_PLOARITY(750, spwmPara->Phase_Duty_U);

//    EPMW1_OUTPUT_DUAL_PLOARITY(750, gtest2[0]);
//    EPMW4_OUTPUT_DUAL_PLOARITY(750, gtest2[1]);
//    EPMW5_OUTPUT_DUAL_PLOARITY(750, gtest2[2]);
	GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1;
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
}
