#include "pf_gpio_cfg.h"

const CFG_GPIO_TBL CfgGpioTbl_Default[] =
{
 {3, GPIO_OUTPUT},			//{gpio number, gpio direction}
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT},
 {3, GPIO_OUTPUT}
};

#define GPIO 0
/*all the gpio configuration function*/
void CFG_GPIO_0(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = GPIO;
	 GpioCtrlRegs.GPADIR.bit.GPIO0 = direction;
}
void CFG_GPIO_1(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO1 = direction;
}
void CFG_GPIO_2(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO2 = direction;
}
void CFG_GPIO_3(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO3 = direction;
}
void CFG_GPIO_4(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO4 = direction;
}
void CFG_GPIO_5(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO5 = direction;
}
void CFG_GPIO_6(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO6 = direction;
}
void CFG_GPIO_7(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO7 = direction;
}
void CFG_GPIO_8(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO8 = direction;
}
void CFG_GPIO_9(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO9 = direction;
}
void CFG_GPIO_10(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO10 = direction;
}
void CFG_GPIO_11(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO11 = direction;
}
void CFG_GPIO_12(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO12 = direction;
}
void CFG_GPIO_13(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO13 = direction;
}
void CFG_GPIO_14(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO14 = direction;
}
void CFG_GPIO_15(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO15 = direction;
}
void CFG_GPIO_16(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO16 = direction;
}
void CFG_GPIO_17(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO17 = direction;
}
void CFG_GPIO_18(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO18 = direction;
}
void CFG_GPIO_19(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO19 = direction;
}
void CFG_GPIO_20(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO20 = direction;
}
void CFG_GPIO_21(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO21 = direction;
}
void CFG_GPIO_22(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO22 = direction;
}
void CFG_GPIO_23(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO23 = direction;
}
void CFG_GPIO_24(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO24 = direction;
}
void CFG_GPIO_25(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO25 = direction;
}
void CFG_GPIO_26(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO26 = direction;
}
void CFG_GPIO_27(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO27 = direction;
}
void CFG_GPIO_28(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO28 = direction;
}
void CFG_GPIO_29(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO29 = direction;
}
void CFG_GPIO_30(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO30 = direction;
}
void CFG_GPIO_31(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = GPIO;
     GpioCtrlRegs.GPADIR.bit.GPIO31 = direction;
}
void CFG_GPIO_32(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO32 = direction;
}
void CFG_GPIO_33(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO33 = direction;
}
void CFG_GPIO_34(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO34 = direction;
}
void CFG_GPIO_35(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO35 = direction;
}
void CFG_GPIO_36(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO36 = direction;
}
void CFG_GPIO_37(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO37 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO37 = direction;
}
void CFG_GPIO_38(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO38 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO38 = direction;
}
void CFG_GPIO_39(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO39 = direction;
}
void CFG_GPIO_40(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO40 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO40 = direction;
}
void CFG_GPIO_41(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO41 = direction;
}
void CFG_GPIO_42(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO42 = direction;
}
void CFG_GPIO_43(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO43 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO43 = direction;
}
void CFG_GPIO_44(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO44 = direction;
}
void CFG_GPIO_45(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO45 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO45 = direction;
}
void CFG_GPIO_46(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO46 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO46 = direction;
}
void CFG_GPIO_47(GPIO_DIRECTION direction)
{
	GpioCtrlRegs.GPBMUX1.bit.GPIO47 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO47 = direction;
}
void CFG_GPIO_48(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO48 = direction;
}
void CFG_GPIO_49(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO49 = direction;
}
void CFG_GPIO_50(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO50 = direction;
}
void CFG_GPIO_51(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO51 = direction;
}
void CFG_GPIO_52(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO52 = direction;
}
void CFG_GPIO_53(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO53 = direction;
}
void CFG_GPIO_54(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO54 = direction;
}
void CFG_GPIO_55(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO55 = direction;
}
void CFG_GPIO_56(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO56 = direction;
}
void CFG_GPIO_57(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO57 = direction;
}
void CFG_GPIO_58(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO58 = direction;
}
void CFG_GPIO_59(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO59 = direction;
}
void CFG_GPIO_60(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO60 = direction;
}
void CFG_GPIO_61(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO61 = direction;
}
void CFG_GPIO_62(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO62 = direction;
}
void CFG_GPIO_63(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = GPIO;
     GpioCtrlRegs.GPBDIR.bit.GPIO63 = direction;
}
void CFG_GPIO_64(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO64 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO64 = direction;
}
void CFG_GPIO_65(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO65 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO65 = direction;
}
void CFG_GPIO_66(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO66 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO66 = direction;
}
void CFG_GPIO_67(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO67 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO67 = direction;
}
void CFG_GPIO_68(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO68 = direction;
}
void CFG_GPIO_69(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO69 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO69 = direction;
}
void CFG_GPIO_70(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO70 = direction;
}
void CFG_GPIO_71(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO71 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO71 = direction;
}
void CFG_GPIO_72(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO72 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO72 = direction;
}
void CFG_GPIO_73(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO73 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO73 = direction;
}
void CFG_GPIO_74(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO74 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO74 = direction;
}
void CFG_GPIO_75(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO75 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO75 = direction;
}
void CFG_GPIO_76(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO76 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO76 = direction;
}
void CFG_GPIO_77(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO77 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO77 = direction;
}
void CFG_GPIO_78(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO78 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO78 = direction;
}
void CFG_GPIO_79(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX1.bit.GPIO79 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO79 = direction;
}
void CFG_GPIO_80(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO80 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO80 = direction;
}
void CFG_GPIO_81(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO81 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO81 = direction;
}
void CFG_GPIO_82(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO82 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO82 = direction;
}
void CFG_GPIO_83(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO83 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO83 = direction;
}
void CFG_GPIO_84(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO84 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO84 = direction;
}
void CFG_GPIO_85(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO85 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO85 = direction;
}
void CFG_GPIO_86(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO86 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO86 = direction;
}
void CFG_GPIO_87(GPIO_DIRECTION direction)
{
    GpioCtrlRegs.GPCMUX2.bit.GPIO87 = GPIO;
     GpioCtrlRegs.GPCDIR.bit.GPIO87 = direction;
}

const CFG_GPIO_HDL_TBL SDB_CfgGPIOHdlTbl[TOTAL_GPIO] =
{
	CFG_GPIO_0,
	CFG_GPIO_1,
	CFG_GPIO_2,
	CFG_GPIO_3,
	CFG_GPIO_4,
	CFG_GPIO_5,
	CFG_GPIO_6,
	CFG_GPIO_7,
	CFG_GPIO_8,
	CFG_GPIO_9,
	CFG_GPIO_10,
	CFG_GPIO_11,
	CFG_GPIO_12,
	CFG_GPIO_13,
	CFG_GPIO_14,
	CFG_GPIO_15,
	CFG_GPIO_16,
	CFG_GPIO_17,
	CFG_GPIO_18,
	CFG_GPIO_19,
	CFG_GPIO_20,
	CFG_GPIO_21,
	CFG_GPIO_22,
	CFG_GPIO_23,
	CFG_GPIO_24,
	CFG_GPIO_25,
	CFG_GPIO_26,
	CFG_GPIO_27,
	CFG_GPIO_28,
	CFG_GPIO_29,
	CFG_GPIO_30,
	CFG_GPIO_31,
	CFG_GPIO_32,
	CFG_GPIO_33,
	CFG_GPIO_34,
	CFG_GPIO_35,
	CFG_GPIO_36,
	CFG_GPIO_37,
	CFG_GPIO_38,
	CFG_GPIO_39,
	CFG_GPIO_40,
	CFG_GPIO_41,
	CFG_GPIO_42,
	CFG_GPIO_43,
	CFG_GPIO_44,
	CFG_GPIO_45,
	CFG_GPIO_46,
	CFG_GPIO_47,
	CFG_GPIO_48,
	CFG_GPIO_49,
	CFG_GPIO_50,
	CFG_GPIO_51,
	CFG_GPIO_52,
	CFG_GPIO_53,
	CFG_GPIO_54,
	CFG_GPIO_55,
	CFG_GPIO_56,
	CFG_GPIO_57,
	CFG_GPIO_58,
	CFG_GPIO_59,
	CFG_GPIO_60,
	CFG_GPIO_61,
	CFG_GPIO_62,
	CFG_GPIO_63,
	CFG_GPIO_64,
	CFG_GPIO_65,
	CFG_GPIO_66,
	CFG_GPIO_67,
	CFG_GPIO_68,
	CFG_GPIO_69,
	CFG_GPIO_70,
	CFG_GPIO_71,
	CFG_GPIO_72,
	CFG_GPIO_73,
	CFG_GPIO_74,
	CFG_GPIO_75,
	CFG_GPIO_76,
	CFG_GPIO_77,
	CFG_GPIO_78,
	CFG_GPIO_79,
	CFG_GPIO_80,
	CFG_GPIO_81,
	CFG_GPIO_82,
	CFG_GPIO_83,
	CFG_GPIO_84,
	CFG_GPIO_85,
	CFG_GPIO_86,
	CFG_GPIO_87
};

void PFAL_GPIO_CFG(CFG_GPIO_TBL* cfgGpioTbl, int len)
{
#if(PF_GPIO == INCLUDE_FEATURE)
	int i = 0;

	EALLOW;
	for(i = 0; i < len; ++i)
	{
	    SDB_CfgGPIOHdlTbl[cfgGpioTbl[i].gpioIndex](cfgGpioTbl[i].direction);
	}
    EDIS;
#endif
}
