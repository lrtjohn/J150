

#include "adc_service.h"

SysAnalogVar gSysAnalogVar = {0};

Uint16 updateForceValue(void){return Get_Adc_CHL1;}
Uint16 updateBusCurrentP(void){return Get_Adc_CHL2;}
Uint16 updatePower28V_M(void){return Get_Adc_CHL3;}
Uint16 updateBridgeCurrentB(void){return Get_Adc_CHL4;}
Uint16 updateBusCurrentB(void){return Get_Adc_CHL5;}
Uint16 updatePower28V(void){return Get_Adc_CHL6;}
Uint16 updateBridgeCurrentA(void){return Get_Adc_CHL7;}
Uint16 updateBusCurrentA(void){return Get_Adc_CHL8;}
Uint16 updateDisplacementValue(void){return Get_Adc_CHL9;}
Uint16 updateBridgeCurrentC(void){return Get_Adc_CHL10;}
Uint16 updateBusCurrentC(void){return Get_Adc_CHL11;}
Uint16 updateBusCurrentC1(void){return Get_Adc_CHL12;}
Uint16 updateBusCurrentC2(void){return Get_Adc_CHL13;}
Uint16 updateBusCurrentC3(void){return Get_Adc_CHL14;}
Uint16 updateBusCurrentC4(void){return Get_Adc_CHL15;}


const UV SDB_SingleAdUVTBL[TOTAL_SNGL_ANAL_CHS] = 
{
	updateForceValue,
	updateBusCurrentP,
	updatePower28V_M,
	updateBridgeCurrentB,
	updateBusCurrentB,
	updatePower28V,
	updateBridgeCurrentA,
	updateBusCurrentA,
	updateDisplacementValue,
	updateBridgeCurrentC,
	updateBusCurrentC,
    updateBusCurrentC1,
    updateBusCurrentC2,
    updateBusCurrentC3,
    updateBusCurrentC4,
};

const Uint16 SDB_SingleAnologMaxMinInit[TOTAL_SNGL_ANAL_CHS][4] = 
{
        //{max,2ndmax,min,2ndmin}
	{0,0,0,0},            //0
	{300,0,0,0},          //1
	{2870,0,2548,0},      //2
	{3,0,0,0},            //3
	{4,0,0,0},            //4
	{3500,0,3000,0},      //5
	{6,0,0,0},            //6
	{7,0,0,0},            //7
	{2690,2400,861,1000}, //8
	{9,0,0,0},            //9
	{10,0,0,0},           //10
	{11,0,0,0},           //11
	{11,0,0,0},           //12
	{11,0,0,0},           //13
	{11,0,0,0}            //14
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

