

#include "adc_service.h"
#include "spwm_service.h"

SysAnalogVar gSysAnalogVar = {0};
Current_Struct gCurrent_Struct = {0};
Voltage_Struct gVoltage_Struct = {0};
Temperature_Struct gTemperature_Struct = {0};
Analog_Ref_Struct gAnalog_Ref_Struct = {0};

Uint16 ADCINA0(void){return Get_Adc_CHL0;}
Uint16 ADCINA1(void){return Get_Adc_CHL2;}
Uint16 ADCINA2(void){return Get_Adc_CHL4;}
Uint16 ADCINA3(void){return Get_Adc_CHL6;}
Uint16 ADCINA4(void){return Get_Adc_CHL8;}
Uint16 ADCINA5(void){return Get_Adc_CHL10;}
Uint16 ADCINA6(void){return Get_Adc_CHL12;}
Uint16 ADCINA7(void){return Get_Adc_CHL14;}

Uint16 ADCINB0(void){return Get_Adc_CHL1;}
Uint16 ADCINB1(void){return Get_Adc_CHL3;}
Uint16 ADCINB2(void){return Get_Adc_CHL5;}
Uint16 ADCINB3(void){return Get_Adc_CHL7;}
Uint16 ADCINB4(void){return Get_Adc_CHL9;}
Uint16 ADCINB5(void){return Get_Adc_CHL11;}
Uint16 ADCINB6(void){return Get_Adc_CHL13;}
Uint16 ADCINB7(void){return Get_Adc_CHL15;}


const UV SDB_SingleAdUVTBL[TOTAL_SNGL_ANAL_CHS] = 
{
 	ADCINA0,
	ADCINB0,
	ADCINA1,
	ADCINB1,
	ADCINA2,
	ADCINB2,
	ADCINA3,
	ADCINB3,
	ADCINA4,
	ADCINB4,
	ADCINA5,
	ADCINB5,
	ADCINA6,
	ADCINB6,
	ADCINA7,
	ADCINB7
};

const Uint16 SDB_SingleAnologMaxMinInit[TOTAL_SNGL_ANAL_CHS][4] = 
{
        //{max,2ndmax,min,2ndmin}
	{0,0,0,0},            //0
	{0,0,0,0},            //1
	{0,0,0,0},      	  //2
	{0,0,0,0},            //3
	{0,0,0,0},            //4
	{0,0,0,0},      	  //5
	{3063,2968,300,400},      //6 320V, 310V, 210V, 215V 2013,2060
	{0,0,0,0},            //7
	{0,0,0,0}, 			  //8
	{0,0,0,0},            //9
	{1600,0,1000,0},      //10
	{0,0,0,0},            //11
	{550,0,200,0},        //12
	{0,0,0,0},            //13
	{0,0,0,0},            //14
	{0,0,0,0}             //15
};

#pragma CODE_SECTION(Spwm_HighSpeed_BIT, "ramfuncs")
void UpdateSingleAnalog(SysAnalogVar* sysAnalogVar)
{
	int index;

	for(index = 0; index < TOTAL_SNGL_ANAL_CHS; ++index)
	{
        sysAnalogVar->single.var[index].value = sysAnalogVar->single.var[index].updateValue();
	}
}

/*由PWM中断调用*/
#pragma CODE_SECTION(PwrBus_OverVoltage_BIT, "ramfuncs")
void PwrBus_OverVoltage_BIT(void){
    static int count_enable_alarm = 0;
    static int cnt_disable_alarm = 0;
    static int cnt_disable_break = 0;
    static int cnt_enable_break = 0;

    if(gSpwmPara.pwmSM == SYS_FORWARD_RUN){
    	if (gSysAnalogVar.single.var[updatePower270V_M].value > gVoltage_Struct.Thr_max3rd_Voltage){
    		++cnt_enable_break;
    		if(cnt_enable_break > 3){
    			cnt_enable_break = 0;
    			ENABLE_SW_BREAK;
    		}
			else;/*DO NOTHING*/
    	}
    	else{
			cnt_enable_break = 0;

    		if(IS_SW_BREAK_ENABLED){
        		if(gSysAnalogVar.single.var[updatePower270V_M].value < gVoltage_Struct.Thr_max4th_Voltage){
        			++cnt_disable_break;
        			if(cnt_disable_break > 5){
        				cnt_disable_break = 0;
        				DISABLE_SW_BREAK;
        			}
        		}
        		else cnt_disable_break = 0;
			}
    		else cnt_disable_break = 0;
    	}
    }
	else{
		DISABLE_SW_BREAK;
		cnt_enable_break = 0;
		cnt_disable_break = 0;
	}


	if (gSysAnalogVar.single.var[updatePower270V_M].value > gVoltage_Struct.Thr_max_Voltage){
		++count_enable_alarm;
		if(count_enable_alarm > 3){
			count_enable_alarm = 0;
			SET_SW_BUS_OV_ALARM;
		}
		else;/*DO NOTHING*/
	}
	else{
		count_enable_alarm = 0;
		if(IS_SW_BUS_OV_ALARM){
			if(gSysAnalogVar.single.var[updatePower270V_M].value < gVoltage_Struct.Thr_max2nd_Voltage){
				++cnt_disable_alarm;
				if(cnt_disable_alarm > 5){
					cnt_disable_alarm = 0;
					CLEAR_SW_BUS_OV_ALARM;
				}
				else;/*DO NOTHING*/
			}
			else cnt_disable_alarm = 0;
		}
		else cnt_disable_alarm = 0;
	}
}

/*由主循环调用*/
void PwrBus_UnderVoltage(void){
	static int count_min = 0;
	static int count_min2nd = 0;

		if (gSysAnalogVar.single.var[updatePower270V_M].value < gVoltage_Struct.Thr_min_Voltage){ /*210*/
            ++count_min;
            if(count_min > 10){
                count_min = 0;
                SET_SYS_BUS_UNDER_VOLTAGE_ALARM;
            }
		}
		else{
			if(count_min >= 1) --count_min;
			else count_min = 0; 
		}

		if(IS_SYS_BUS_UNDER_VOLTAGE_ALARM){
			if(gSysAnalogVar.single.var[updatePower270V_M].value > gVoltage_Struct.Thr_min2nd_Voltage){ /*215V*/
				++count_min2nd;
				if(count_min2nd > 150){					
					count_min2nd = 0;
					CLEAR_SYS_BUS_UNDER_VOLTAGE_ALARM;
				}
				else{
					if(count_min2nd >= 1) --count_min2nd;
					else count_min2nd = 0;
				}
			}
		}
}

#pragma CODE_SECTION(BridgeABC_Current_Monitor_BIT, "ramfuncs")
void BridgeABC_Current_Monitor_BIT(void){
	int16 I_bridge_temp;
	int i;
	int alarm_flag;
	int restrict_flag;
	static int cnt_bridgeSum;
	static int cnt_busCurrent;

	gCurrent_Struct.I_bridgeABC[0] = gSysAnalogVar.single.var[updateBridgeCurrentA].value - gCurrent_Struct.zero_IABC[0];
	gCurrent_Struct.I_bridgeABC[1] = gSysAnalogVar.single.var[updateBridgeCurrentB].value - gCurrent_Struct.zero_IABC[1];
	gCurrent_Struct.I_bridgeABC[2] = gSysAnalogVar.single.var[updateBridgeCurrentC].value - gCurrent_Struct.zero_IABC[2];

	alarm_flag = restrict_flag = 0;
	gCurrent_Struct.I_busCurrent = gCurrent_Struct.I_bridgeSum = 0;
	for(i=0; i<3; i++){
		I_bridge_temp = gCurrent_Struct.I_bridgeABC[i];
		if(I_bridge_temp > gCurrent_Struct.Pos_BridgeCurrent[i]) gCurrent_Struct.Pos_BridgeCurrent[i] = I_bridge_temp;
		if(I_bridge_temp < gCurrent_Struct.Neg_BridgeCurrent[i]) gCurrent_Struct.Neg_BridgeCurrent[i] = I_bridge_temp;

		gCurrent_Struct.I_bridgeSum = I_bridge_temp + gCurrent_Struct.I_bridgeSum;
		if(I_bridge_temp < 0) I_bridge_temp = - I_bridge_temp;
		gCurrent_Struct.I_busCurrent = gCurrent_Struct.I_busCurrent + I_bridge_temp;
		if(I_bridge_temp > gCurrent_Struct.Thr_min_I_Bridge){
			restrict_flag = 1;
			if(I_bridge_temp > gCurrent_Struct.Thr_max_I_Bridge){
				gCurrent_Struct.cnt_max_threshold[i] = (I_bridge_temp - gCurrent_Struct.Thr_max_I_Bridge) +
						gCurrent_Struct.cnt_max_threshold[i];
		        if(gCurrent_Struct.cnt_max_threshold[i] > 150){
		        	gCurrent_Struct.cnt_max_threshold[i] = 0;
		        	alarm_flag = 1;
		        }
			}
		    else{
			    if(gCurrent_Struct.cnt_max_threshold[i] >= 1) --gCurrent_Struct.cnt_max_threshold[i];
			    else gCurrent_Struct.cnt_max_threshold[i] = 0;
		    }
		}
		else gCurrent_Struct.cnt_max_threshold[i] = 0;
	}
	if(gCurrent_Struct.I_bridgeSum < 0 ) gCurrent_Struct.I_bridgeSum = - gCurrent_Struct.I_bridgeSum;
	if(gCurrent_Struct.I_bridgeSum >= gCurrent_Struct.Thr_BridgeSum){
		++cnt_bridgeSum;
		if(cnt_bridgeSum > 10) SET_BRIDGE_CURRENT_SUM_ALARM;
	}
	else{
		if(cnt_bridgeSum >= 1) --cnt_bridgeSum;
		else{
			cnt_bridgeSum = 0;
			CLEAR_BRIDGE_CURRENT_SUM_ALARM;
		}
	}
	if(gCurrent_Struct.I_busCurrent >= gCurrent_Struct.Thr_BusCurrent){
		++cnt_busCurrent;
		if(cnt_busCurrent > 10) SET_BUS_CURRENT_ALARM;
	}
	else{
		if(cnt_busCurrent >= 1) --cnt_busCurrent;
		else{
			cnt_busCurrent = 0;
			CLEAR_BUS_CURRENT_ALARM;
		}
	}
	if(restrict_flag) gSpwmPara.restrictduty = 1;
	else gSpwmPara.restrictduty = 0;
	if(alarm_flag) SET_BRIDGE_CURRENT_ALARM;
	else{
		if(IS_SYS_RUNNING_STATE_ALARM) CLEAR_BRIDGE_CURRENT_ALARM;
	}

	if(gCurrent_Struct.I_busCurrent > gCurrent_Struct.Max_BusCurrent) gCurrent_Struct.Max_BusCurrent = gCurrent_Struct.I_busCurrent;
	if(gCurrent_Struct.I_bridgeSum > gCurrent_Struct.Pos_BridgeSum) gCurrent_Struct.Pos_BridgeSum = gCurrent_Struct.I_bridgeSum;
	if(gCurrent_Struct.I_bridgeSum < gCurrent_Struct.Neg_BridgeSum) gCurrent_Struct.Neg_BridgeSum = gCurrent_Struct.I_bridgeSum;
	GpioDataRegs.GPBDAT.bit.GPIO50 = 0;/*debug3*/
}

void CheckMotorTemperature(void){
    static int cnt_alarm_max = 0;
    static int cnt_alarm_max2nd = 0;
    static int over_alarm_limit_lasttime = 0;

    static int cnt_warning_max = 0;
    static int cnt_warning_max2nd = 0;
    static int over_warning_limit_lasttime = 0;

    if(over_alarm_limit_lasttime == 1){/*保护*/
        if(gSysAnalogVar.single.var[updateMotorTemp].value < gTemperature_Struct.Thr_max2nd_alarm_motor_Temp){
            ++cnt_alarm_max2nd;
            if(cnt_alarm_max2nd >5000){
            	CLEAR_MOTOR_TEMPERATURE_ALARM;
            	over_alarm_limit_lasttime = 0;
            }
        }
        else{
        	cnt_alarm_max2nd = 0;
            over_alarm_limit_lasttime = 1;
            SET_MOTOR_TEMPERATURE_ALARM;
        }
    }
    else if (over_alarm_limit_lasttime == 0){
        if(gSysAnalogVar.single.var[updateMotorTemp].value > gTemperature_Struct.Thr_max_alarm_motor_Temp) {
            ++cnt_alarm_max;
            if(cnt_alarm_max > 5000){
                cnt_alarm_max = 0;
                SET_MOTOR_TEMPERATURE_ALARM;
                over_alarm_limit_lasttime = 1;
            }
        }
        else{
            if(cnt_alarm_max >= 1) --cnt_alarm_max;
            else cnt_alarm_max = 0;
        }
    }
    else{
//    	gSysSWAlarm.bit.updateAndCheckTemperature = 1;
//    	gSysAlarm.bit.softwareFault = 1;
    }

    if(over_warning_limit_lasttime == 1){/*警告*/
        if(gSysAnalogVar.single.var[updateMotorTemp].value < gTemperature_Struct.Thr_max2nd_warning_motor_Temp){
            ++cnt_warning_max2nd;
            if(cnt_warning_max2nd >5000){
            	CLEAR_MOTOR_TEMPERATURE_WARNING;
            	over_warning_limit_lasttime = 0;
            }
        }
        else{
        	cnt_warning_max2nd = 0;
            over_warning_limit_lasttime = 1;
            SET_MOTOR_TEMPERATURE_WARNING;
        }
    }
    else if (over_warning_limit_lasttime == 0){
        if(gSysAnalogVar.single.var[updateMotorTemp].value > gTemperature_Struct.Thr_max_warning_motor_Temp) {
            ++cnt_warning_max;
            if(cnt_warning_max > 5000){
                cnt_warning_max = 0;
                SET_MOTOR_TEMPERATURE_WARNING;
                over_alarm_limit_lasttime = 1;
            }
        }
        else{
            if(cnt_warning_max >= 1) --cnt_warning_max;
            else cnt_warning_max = 0;
        }
    }
    else{
//    	gSysSWAlarm.bit.updateAndCheckTemperature = 1;
//    	gSysAlarm.bit.softwareFault = 1;
    }
}

void CheckDriverTemperature(void){
    static int cnt_alarm_max = 0;
    static int cnt_alarm_max2nd = 0;
    static int over_alarm_limit_lasttime = 0;

    static int cnt_warning_max = 0;
    static int cnt_warning_max2nd = 0;
    static int over_warning_limit_lasttime = 0;

    if(over_alarm_limit_lasttime == 1){/*保护*/
        if(gSysAnalogVar.single.var[updateDriverTemp].value < gTemperature_Struct.Thr_max2nd_alarm_driver_Temp){
            ++cnt_alarm_max2nd;
            if(cnt_alarm_max2nd >5000){
            	CLEAR_DRIVER_TEMPERATURE_ALARM;
            	over_alarm_limit_lasttime = 0;
            }
        }
        else{
        	cnt_alarm_max2nd = 0;
            over_alarm_limit_lasttime = 1;
            SET_DRIVER_TEMPERATURE_ALARM;
        }
    }
    else if (over_alarm_limit_lasttime == 0){
        if(gSysAnalogVar.single.var[updateDriverTemp].value > gTemperature_Struct.Thr_max_alarm_driver_Temp) {
            ++cnt_alarm_max;
            if(cnt_alarm_max > 5000){
                cnt_alarm_max = 0;
                SET_DRIVER_TEMPERATURE_ALARM;
                over_alarm_limit_lasttime = 1;
            }
        }
        else{
            if(cnt_alarm_max >= 1) --cnt_alarm_max;
            else cnt_alarm_max = 0;
        }
    }
    else{
//    	gSysSWAlarm.bit.updateAndCheckTemperature = 1;
//    	gSysAlarm.bit.softwareFault = 1;
    }

    if(over_warning_limit_lasttime == 1){/*警告*/
        if(gSysAnalogVar.single.var[updateDriverTemp].value < gTemperature_Struct.Thr_max2nd_warning_driver_Temp){
            ++cnt_warning_max2nd;
            if(cnt_warning_max2nd >5000){
            	CLEAR_DRIVERR_TEMPERATURE_WARNING;
            	over_warning_limit_lasttime = 0;
            }
        }
        else{
        	cnt_warning_max2nd = 0;
            over_warning_limit_lasttime = 1;
            SET_DRIVER_TEMPERATURE_WARNING;
        }
    }
    else if (over_warning_limit_lasttime == 0){
        if(gSysAnalogVar.single.var[updateDriverTemp].value > gTemperature_Struct.Thr_max_warning_driver_Temp) {
            ++cnt_warning_max;
            if(cnt_warning_max > 5000){
                cnt_warning_max = 0;
                SET_DRIVER_TEMPERATURE_WARNING;
                over_alarm_limit_lasttime = 1;
            }
        }
        else{
            if(cnt_warning_max >= 1) --cnt_warning_max;
            else cnt_warning_max = 0;
        }
    }
    else{
//    	gSysSWAlarm.bit.updateAndCheckTemperature = 1;
//    	gSysAlarm.bit.softwareFault = 1;
    }
}

void check_28V_Current(void){
	static int cnt_alarm = 0;

	if((gSysAnalogVar.single.var[updateCurrent28V].value > gSysAnalogVar.single.var[updateCurrent28V].max) ||
	   (gSysAnalogVar.single.var[updateCurrent28V].value < gSysAnalogVar.single.var[updateCurrent28V].min)){
		++cnt_alarm;
		if(cnt_alarm > 10){
			SET_CONTROL_BUS_CURRENT_ALARM;
		}
	}
	else{
		if(cnt_alarm >= 1) --cnt_alarm;
		else{
			cnt_alarm = 0;
			CLEAR_CONTROL_BUS_CURRENT_ALARM;
		} 			
	}
}

void check_28V_Voltage(void){
	static int cnt_alarm = 0;

	if((gSysAnalogVar.single.var[updateVoltage28V].value > gSysAnalogVar.single.var[updateVoltage28V].max) ||
	   (gSysAnalogVar.single.var[updateVoltage28V].value < gSysAnalogVar.single.var[updateVoltage28V].min)){
		++cnt_alarm;
		if(cnt_alarm > 10){
			SET_CONTROL_BUS_VOLTAGE_ALARM;
		}
	}
	else{
		if(cnt_alarm >= 1) --cnt_alarm;
		else{
			cnt_alarm = 0;
			CLEAR_CONTROL_BUS_VOLTAGE_ALARM;
		} 			
	}
}

void check_Analog_Ref(void){
	int i;
	gAnalog_Ref_Struct.analog_ref[0] = gSysAnalogVar.single.var[updateVoltageVCC5V].value;
	gAnalog_Ref_Struct.analog_ref[1] = gSysAnalogVar.single.var[updateVoltageAVDD5V].value;
	gAnalog_Ref_Struct.analog_ref[2] = gSysAnalogVar.single.var[updateVoltageRef2V5].value;
	gAnalog_Ref_Struct.analog_ref[3] = gSysAnalogVar.single.var[updateCurrentMax].value;
	gAnalog_Ref_Struct.analog_ref[4] = gSysAnalogVar.single.var[updateDriverVoltage5V].value;
	gAnalog_Ref_Struct.analog_ref[5] = gSysAnalogVar.single.var[updateVoltageRef1V5].value;
	gAnalog_Ref_Struct.analog_ref[6] = gSysAnalogVar.single.var[updateCurrentMin].value;

	for(i=0; i<7; i++){
		if((gAnalog_Ref_Struct.analog_ref[i] > gAnalog_Ref_Struct.thr_max_analog_ref[i]) ||
		   (gAnalog_Ref_Struct.analog_ref[i] < gAnalog_Ref_Struct.thr_min_analog_ref[i])){
			++gAnalog_Ref_Struct.cnt_analog_ref[i];
			if(gAnalog_Ref_Struct.cnt_analog_ref[i] > 20){
				SET_HW_ANALOG_LEVEL_ALARM;
			}
		}
		else{
			if(gAnalog_Ref_Struct.cnt_analog_ref[i] >= 1) --gAnalog_Ref_Struct.cnt_analog_ref[i];
			else{
				gAnalog_Ref_Struct.cnt_analog_ref[i] = 0;
				CLEAR_HW_ANALOG_LEVEL_ALARM;
			} 			
		}
	}

}


int IsSingleAnalogValueAbnormal(SysAnalogVar* sysAnalogVar)
{
	int index;
	int ret = 1;
	for(index = 0; index < TOTAL_SNGL_ANAL_CHS; ++index)
	{
		if((sysAnalogVar->single.var[index].value > sysAnalogVar->single.var[index].max) ||
				(sysAnalogVar->single.var[index].value < sysAnalogVar->single.var[index].min)) 
		{
			ret = 0;
		}
	}
	return ret;
}

void Init_Adc_Service_Ptr(SysAnalogVar* sysAnalogVar)
{
	int index;
	for (index = 0; index < TOTAL_SNGL_ANAL_CHS; ++index) {
		sysAnalogVar->single.var[index].updateValue = SDB_SingleAdUVTBL[index];
		sysAnalogVar->single.var[index].max =
				SDB_SingleAnologMaxMinInit[index][0];
        sysAnalogVar->single.var[index].max2nd =
                SDB_SingleAnologMaxMinInit[index][1];
		sysAnalogVar->single.var[index].min =
				SDB_SingleAnologMaxMinInit[index][2];
        sysAnalogVar->single.var[index].min2nd =
                SDB_SingleAnologMaxMinInit[index][3];

		sysAnalogVar->single.var[index].count_max = 0;
		sysAnalogVar->single.var[index].count_min = 0;
		sysAnalogVar->single.var[index].value = 0;
	}

}

void Init_Adc_Service(void)
{
	int index;
	for (index = 0; index < TOTAL_SNGL_ANAL_CHS; ++index) {
		gSysAnalogVar.single.var[index].updateValue = SDB_SingleAdUVTBL[index];
		gSysAnalogVar.single.var[index].max =
				SDB_SingleAnologMaxMinInit[index][0];
        gSysAnalogVar.single.var[index].max2nd =
                SDB_SingleAnologMaxMinInit[index][1];
		gSysAnalogVar.single.var[index].min =
				SDB_SingleAnologMaxMinInit[index][2];
        gSysAnalogVar.single.var[index].min2nd =
                SDB_SingleAnologMaxMinInit[index][3];

		gSysAnalogVar.single.var[index].count_max = 0;
		gSysAnalogVar.single.var[index].count_min = 0;
		gSysAnalogVar.single.var[index].value = 0;
	}

}

void Init_ADC_Current(void)
{
	gCurrent_Struct.zerosum_IABC[0] = 0;
	gCurrent_Struct.zerosum_IABC[1] = 0;
	gCurrent_Struct.zerosum_IABC[2] = 0;
	gCurrent_Struct.zero_IABC[0] = 0;
	gCurrent_Struct.zero_IABC[1] = 0;
	gCurrent_Struct.zero_IABC[2] = 0;
	gCurrent_Struct.I_bridgeABC[0] = 0;
	gCurrent_Struct.I_bridgeABC[1] = 0;
	gCurrent_Struct.I_bridgeABC[2] = 0;
	gCurrent_Struct.Thr_max_I_Bridge = 2000;
	gCurrent_Struct.Thr_min_I_Bridge = 2000;
	gCurrent_Struct.Thr_max_I_Bus = 1000;
	gCurrent_Struct.Thr_min_I_Bus = 1000;
	gCurrent_Struct.I_busCurrent = 0;
	gCurrent_Struct.I_bridgeSum = 0;
	gCurrent_Struct.Thr_BridgeSum = 2000;
	gCurrent_Struct.Thr_BusCurrent = 2000;
	gCurrent_Struct.cnt_max_threshold[0] = 0;
	gCurrent_Struct.cnt_max_threshold[1] = 0;
	gCurrent_Struct.cnt_max_threshold[2] = 0;
	gCurrent_Struct.Pos_BridgeCurrent[0] = 0;
	gCurrent_Struct.Pos_BridgeCurrent[1] = 0;
	gCurrent_Struct.Pos_BridgeCurrent[2] = 0;
	gCurrent_Struct.Neg_BridgeCurrent[0] = 0;
	gCurrent_Struct.Neg_BridgeCurrent[1] = 0;
	gCurrent_Struct.Neg_BridgeCurrent[2] = 0;
	gCurrent_Struct.Pos_BridgeSum = 0;
	gCurrent_Struct.Neg_BridgeSum = 0;
	gCurrent_Struct.Max_BusCurrent = 0;
}

void Init_ADC_Voltage(void)
{
	gVoltage_Struct.Thr_max_Voltage = 3352;    /*350V*/
	gVoltage_Struct.Thr_max2nd_Voltage = 3255; /*340V*/
	gVoltage_Struct.Thr_max3rd_Voltage = 3206; //3206; /*335*/
	gVoltage_Struct.Thr_max4th_Voltage = 3110; //3110; /*325*/
	gVoltage_Struct.Thr_min_Voltage = 2013;    /*210V*/
	gVoltage_Struct.Thr_min2nd_Voltage = 2060; /*215V*/
}

void Init_ADC_Temperature(void)
{
	gTemperature_Struct.Thr_max_warning_motor_Temp = 3000;    /**/
	gTemperature_Struct.Thr_max2nd_warning_motor_Temp = 2500; /**/
	gTemperature_Struct.Thr_max_alarm_motor_Temp = 4000; 		/**/
	gTemperature_Struct.Thr_max2nd_alarm_motor_Temp = 3500;   /**/

	gTemperature_Struct.Thr_max_warning_driver_Temp = 3000;    /**/
	gTemperature_Struct.Thr_max2nd_warning_driver_Temp = 2500; /**/
	gTemperature_Struct.Thr_max_alarm_driver_Temp = 4000; 		/**/
	gTemperature_Struct.Thr_max2nd_alarm_driver_Temp = 3500;   /**/
}

void Init_Analog_Ref(void)
{
	gAnalog_Ref_Struct.analog_ref[0] = 0;
	gAnalog_Ref_Struct.analog_ref[1] = 0;
	gAnalog_Ref_Struct.analog_ref[2] = 0;
	gAnalog_Ref_Struct.analog_ref[3] = 0;
	gAnalog_Ref_Struct.analog_ref[4] = 0;
	gAnalog_Ref_Struct.analog_ref[5] = 0;
	gAnalog_Ref_Struct.analog_ref[6] = 0;
	gAnalog_Ref_Struct.thr_max_analog_ref[0] = 3800; /*10%*/
	gAnalog_Ref_Struct.thr_max_analog_ref[1] = 3800; /*10%*/
	gAnalog_Ref_Struct.thr_max_analog_ref[2] = 3600; /*10%*/
	gAnalog_Ref_Struct.thr_max_analog_ref[3] = 2645; /*10%*/
	gAnalog_Ref_Struct.thr_max_analog_ref[4] = 2500; /*10%*/
	gAnalog_Ref_Struct.thr_max_analog_ref[5] = 2240; /*10%*/
	gAnalog_Ref_Struct.thr_max_analog_ref[6] = 2240; /*10%*/
	gAnalog_Ref_Struct.thr_min_analog_ref[0] = 3100; /*10%*/
	gAnalog_Ref_Struct.thr_min_analog_ref[1] = 3100; /*10%*/
	gAnalog_Ref_Struct.thr_min_analog_ref[2] = 3000; /*10%*/
	gAnalog_Ref_Struct.thr_min_analog_ref[3] = 2165; /*10%*/
	gAnalog_Ref_Struct.thr_min_analog_ref[4] = 2050; /*10%*/
	gAnalog_Ref_Struct.thr_min_analog_ref[5] = 1830; /*10%*/
	gAnalog_Ref_Struct.thr_min_analog_ref[6] = 1830; /*10%*/
	gAnalog_Ref_Struct.cnt_analog_ref[0] = 0;
	gAnalog_Ref_Struct.cnt_analog_ref[1] = 0;
	gAnalog_Ref_Struct.cnt_analog_ref[2] = 0;
	gAnalog_Ref_Struct.cnt_analog_ref[3] = 0;
	gAnalog_Ref_Struct.cnt_analog_ref[4] = 0;
	gAnalog_Ref_Struct.cnt_analog_ref[5] = 0;
	gAnalog_Ref_Struct.cnt_analog_ref[6] = 0;
}
