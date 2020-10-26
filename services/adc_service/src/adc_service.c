

#include "adc_service.h"

SysAnalogVar gSysAnalogVar = {0};

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
	{3063,2968,235,245},            //6 320V, 310V, 210V, 215V 2013,2060
	{0,0,0,0},            //7
	{0,0,0,0}, 			  //8
	{0,0,0,0},            //9
	{0,0,0,0},            //10
	{0,0,0,0},            //11
	{0,0,0,0},            //12
	{0,0,0,0},            //13
	{0,0,0,0},            //14
	{0,0,0,0}             //15
};

void UpdateSingleAnalog(SysAnalogVar* sysAnalogVar)
{
	int index;

	for(index = 0; index < TOTAL_SNGL_ANAL_CHS; ++index)
	{
        sysAnalogVar->single.var[index].value = sysAnalogVar->single.var[index].updateValue();
	}
}

void updateAndCheckVoltage(void){
    static int count_max = 0;

    gSysAnalogVar.single.var[updatePower270V_M].value = gSysAnalogVar.single.var[updatePower270V_M].updateValue();

    if(IS_SYS_BUS_OVER_VOLTAGE_ALARM){
        if((gSysAnalogVar.single.var[updatePower270V_M].value < gSysAnalogVar.single.var[updatePower270V_M].max2nd)){
        	CLEAR_SYS_BUS_OVER_VOLTAGE_ALARM;
        }
        else{
        	SET_SYS_BUS_OVER_VOLTAGE_ALARM;
        }
    }
    else if(!IS_SYS_BUS_OVER_VOLTAGE_ALARM){
        if((gSysAnalogVar.single.var[updatePower270V_M].value > gSysAnalogVar.single.var[updatePower270V_M].max)) {
            ++count_max;
            if(count_max > 10){
                count_max = 0;
                SET_SYS_BUS_OVER_VOLTAGE_ALARM;
            }
        }
        else{
            count_max = 0;
        }
    }
    else{
//        gSysSWAlarm.bit.updateAndCheckVoltage = 1;
//        gSysAlarm.bit.softwareFault = 1;
    }
//    if(IS_SYS_BUS_UNDER_VOLTAGE_ALARM){
//        if((gSysAnalogVar.single.var[updatePower270V_M].value > gSysAnalogVar.single.var[updatePower270V_M].min2nd)){
//        	CLEAR_SYS_BUS_UNDER_VOLTAGE_ALARM;
//        }
//        else{
//        	SET_SYS_BUS_UNDER_VOLTAGE_ALARM;
//        }
//    }
//    else if (!IS_SYS_BUS_UNDER_VOLTAGE_ALARM){
//        if((gSysAnalogVar.single.var[updatePower270V_M].value < gSysAnalogVar.single.var[updatePower270V_M].min)) {
//            ++count_min;
//            if(count_min > 10){
//                count_min = 0;
//                SET_SYS_BUS_UNDER_VOLTAGE_ALARM;
//            }
//        }
//        else{
//            count_min = 0;
//        }
//    }
//    else {
////    	gSysSWAlarm.bit.updateAndCheckVoltage = 1;
////        gSysAlarm.bit.softwareFault = 1;
//    }
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

