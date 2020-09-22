

#include "adc_service.h"

SysAnalogVar gSysAnalogVar = {0};

Uint16 updateBridgeCurrentB(void){return Get_Adc_CHL0;}
Uint16 updateBridgeCurrentA(void){return Get_Adc_CHL2;}
Uint16 updateDriverTemp(void){return Get_Adc_CHL4;}
Uint16 updatePower270V_M(void){return Get_Adc_CHL6;}
Uint16 Reversed_chl5(void){return Get_Adc_CHL8;}
Uint16 updateVoltage28V(void){return Get_Adc_CHL10;}
Uint16 updateCurrent28V(void){return Get_Adc_CHL12;}
Uint16 updateMotorTemp(void){return Get_Adc_CHL14;}

Uint16 updateBridgeCurrentC(void){return Get_Adc_CHL1;}
Uint16 updateCurrentMin(void){return Get_Adc_CHL3;}
Uint16 updateVoltageRef1V5(void){return Get_Adc_CHL5;}
Uint16 updateDriverVoltage5V(void){return Get_Adc_CHL7;}
Uint16 updateCurrentMax(void){return Get_Adc_CHL9;}
Uint16 updateVoltageRef2V5(void){return Get_Adc_CHL11;}
Uint16 updateVoltageAVDD5V(void){return Get_Adc_CHL13;}
Uint16 updateVoltageVCC5V(void){return Get_Adc_CHL15;}


const UV SDB_SingleAdUVTBL[TOTAL_SNGL_ANAL_CHS] = 
{
 	updateBridgeCurrentB,
	updateBridgeCurrentC,
	updateBridgeCurrentA,
	updateCurrentMin,
	updateDriverTemp,
	updateVoltageRef1V5,
	updatePower270V_M,
	updateDriverVoltage5V,
	Reversed_chl5,
	updateCurrentMax,
	updateVoltage28V,
	updateVoltageRef2V5,
	updateCurrent28V,
	updateVoltageAVDD5V,
	updateMotorTemp,
	updateVoltageVCC5V
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
	{0,0,0,0},            //6
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

