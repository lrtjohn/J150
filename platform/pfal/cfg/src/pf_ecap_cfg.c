#include "pf_ecap_cfg.h"

void InitECAP1Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;      // Enable pull-up on GPIO5 (CAP1)
   GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;     // Enable pull-up on GPIO24 (CAP1)
// GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;     // Enable pull-up on GPIO34 (CAP1)


// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;    // Synch to SYSCLKOUT GPIO5 (CAP1)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;   // Synch to SYSCLKOUT GPIO24 (CAP1)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 0;   // Synch to SYSCLKOUT GPIO34 (CAP1)

/* Configure eCAP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP1 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;     // Configure GPIO5 as CAP1
   GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;    // Configure GPIO24 as CAP1
// GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 1;    // Configure GPIO24 as CAP1

    EDIS;
}

void InitECAP2Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;     // Enable pull-up on GPIO7 (CAP2)
   GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (CAP2)
// GpioCtrlRegs.GPBPUD.bit.GPIO37 = 0;    // Enable pull-up on GPIO37 (CAP2)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;    // Synch to SYSCLKOUT GPIO7 (CAP2)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;   // Synch to SYSCLKOUT GPIO25 (CAP2)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO37 = 0;   // Synch to SYSCLKOUT GPIO37 (CAP2)

/* Configure eCAP-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP2 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 3;    // Configure GPIO7 as CAP2
   GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;   // Configure GPIO25 as CAP2
// GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 3;   // Configure GPIO37 as CAP2

    EDIS;
}
// endif DSP28_ECAP2

void InitECAP3Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;      // Enable pull-up on GPIO9 (CAP3)
   GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;     // Enable pull-up on GPIO26 (CAP3)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;    // Synch to SYSCLKOUT GPIO9 (CAP3)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;   // Synch to SYSCLKOUT GPIO26 (CAP3)

/* Configure eCAP-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP3 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;     // Configure GPIO9 as CAP3
   GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as CAP3

    EDIS;
}
// endif DSP28_ECAP3

void InitECAP4Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // Enable pull-up on GPIO11 (CAP4)
   GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pull-up on GPIO27 (CAP4)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0; // Synch to SYSCLKOUT GPIO11 (CAP4)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0; // Synch to SYSCLKOUT GPIO27 (CAP4)

/* Configure eCAP-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP4 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;  // Configure GPIO11 as CAP4
   GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;  // Configure GPIO27 as CAP4

    EDIS;
}
// endif DSP28_ECAP4


void InitECAP5Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;     // Enable pull-up on GPIO3 (CAP5)
   GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;    // Enable pull-up on GPIO48 (CAP5)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 0;  // Synch to SYSCLKOUT GPIO3 (CAP5)
   GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = 0; // Synch to SYSCLKOUT GPIO48 (CAP5)

/* Configure eCAP-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP5 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 2;   // Configure GPIO3 as CAP5
   GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 1;  // Configure GPIO48 as CAP5

    EDIS;
}
// endif DSP28_ECAP5


void InitECAP6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;     // Enable pull-up on GPIO1 (CAP6)
   GpioCtrlRegs.GPBPUD.bit.GPIO49 = 0;    // Enable pull-up on GPIO49 (CAP6)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 0;  // Synch to SYSCLKOUT GPIO1 (CAP6)
   GpioCtrlRegs.GPBQSEL2.bit.GPIO49 = 0; // Synch to SYSCLKOUT GPIO49 (CAP6)

/* Configure eCAP-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP6 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 2;   // Configure GPIO1 as CAP6
   GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 1;  // Configure GPIO49 as CAP6

    EDIS;
}
// endif DSP28_ECAP6

void ECAP1Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap1Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap1Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap1Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap1Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap1Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap1Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap1Regs.ECCTL1.bit.CAP4POL = 0;

	 ECap1Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap1Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap1Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap1Regs.ECCTL1.bit.CTRRST4 = 0;

	 ECap1Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap1Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap1Regs.ECCTL1.bit.PRESCALE =0;

	 ECap1Regs.ECEINT.bit.CEVT1 = 1;            // 2 events = interrupt
	 ECap1Regs.ECEINT.bit.CEVT2 = 1;
	 ECap1Regs.ECEINT.bit.CEVT3 = 1;
	 ECap1Regs.ECEINT.bit.CEVT4 = 1;

	 ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void ECAP2Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap2Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap2Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap2Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap2Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap2Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap2Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap2Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap2Regs.ECCTL1.bit.CAP4POL = 0;

	 ECap2Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap2Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap2Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap2Regs.ECCTL1.bit.CTRRST4 = 0;

	 ECap2Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap2Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap2Regs.ECCTL1.bit.PRESCALE =0;

	 ECap2Regs.ECEINT.bit.CEVT1 = 1;            // 2 events = interrupt
	 ECap2Regs.ECEINT.bit.CEVT2 = 1;
	 ECap2Regs.ECEINT.bit.CEVT3 = 1;
	 ECap2Regs.ECEINT.bit.CEVT4 = 1;

	 ECap2Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void ECAP3Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap3Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap3Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap3Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap3Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap3Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap3Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap3Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap3Regs.ECCTL1.bit.CAP4POL = 0;

	 ECap3Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap3Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap3Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap3Regs.ECCTL1.bit.CTRRST4 = 0;

	 ECap3Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap3Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap3Regs.ECCTL1.bit.PRESCALE =0;

	 ECap3Regs.ECEINT.bit.CEVT1 = 1;            // 2 events = interrupt
	 ECap3Regs.ECEINT.bit.CEVT2 = 1;
	 ECap3Regs.ECEINT.bit.CEVT3 = 1;
	 ECap3Regs.ECEINT.bit.CEVT4 = 1;

	 ECap3Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void ECAP4Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap4Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap4Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap4Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap4Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap4Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap4Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap4Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap4Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap4Regs.ECCTL1.bit.CAP4POL = 0;

	 ECap4Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap4Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap4Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap4Regs.ECCTL1.bit.CTRRST4 = 0;

	 ECap4Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap4Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap4Regs.ECCTL1.bit.PRESCALE =0;

	 ECap4Regs.ECEINT.bit.CEVT1 = 1;            // 2 events = interrupt
	 ECap4Regs.ECEINT.bit.CEVT2 = 1;
	 ECap4Regs.ECEINT.bit.CEVT3 = 1;
	 ECap4Regs.ECEINT.bit.CEVT4 = 1;

	 ECap4Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap4Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void ECAP5Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap5Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap5Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap5Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap5Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap5Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap5Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap5Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap5Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap5Regs.ECCTL1.bit.CAP4POL = 0;


	 ECap5Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap5Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap5Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap5Regs.ECCTL1.bit.CTRRST4 = 1;

	 ECap5Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap5Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap5Regs.ECCTL1.bit.PRESCALE =0;

	 ECap5Regs.ECEINT.bit.CEVT1 = 1;            // 2 events = interrupt
	 ECap5Regs.ECEINT.bit.CEVT2 = 1;
	 ECap5Regs.ECEINT.bit.CEVT3 = 1;
	 ECap5Regs.ECEINT.bit.CEVT4 = 1;

	 ECap5Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap5Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void ECAP6Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap6Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap6Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap6Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap6Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap6Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap6Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap6Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap6Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap6Regs.ECCTL1.bit.CAP4POL = 0;


	 ECap6Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap6Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap6Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap6Regs.ECCTL1.bit.CTRRST4 = 1;

	 ECap6Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap6Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap6Regs.ECCTL1.bit.PRESCALE =0;

	 ECap6Regs.ECEINT.bit.CEVT1 = 1;
	 ECap6Regs.ECEINT.bit.CEVT2 = 1;
	 ECap6Regs.ECEINT.bit.CEVT3 = 1;
	 ECap6Regs.ECEINT.bit.CEVT4 = 1;

	 ECap6Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap6Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void CFG_ECAP_1()
{
	InitECAP1Gpio();
	ECAP1Config();
}
void CFG_ECAP_2()
{
	InitECAP2Gpio();
	ECAP2Config();
}
void CFG_ECAP_3()
{
	InitECAP3Gpio();
	ECAP3Config();
}
void CFG_ECAP_4()
{
	InitECAP4Gpio();
	ECAP4Config();
}
void CFG_ECAP_5()
{
	InitECAP5Gpio();
	ECAP5Config();
}
void CFG_ECAP_6()
{
	InitECAP6Gpio();
	ECAP6Config();
}

const CFG_ECAP_HDL_TBL SDB_CfgECAPHdlTbl[TOTAL_ECAP] =
{
	CFG_ECAP_1,
	CFG_ECAP_2,
	CFG_ECAP_3,
	CFG_ECAP_4,
	CFG_ECAP_5,
	CFG_ECAP_6
};


void PFAL_ECAP_CFG(CFG_ECAP_TBL* cfgECapTbl, int len)
{
#if(PF_ECAP == INCLUDE_FEATURE)
	int i = 0;

	EALLOW;
	for(i = 0; i < len; ++i)
	{
		SDB_CfgECAPHdlTbl[cfgECapTbl[i].ecapModule]();
	}
    EDIS;
#endif
}
