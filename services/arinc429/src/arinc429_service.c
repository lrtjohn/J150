#include "arinc429_service.h"


ARINC429_PARA gArinc429Para = {0};

int arinc429[11] = {0,0,0,0,0,0,0,0,0,0,0};
Uint32 Arinc429_SetCtlReg(ARINC429_CTL_REG ctlRegVal)
{
    Uint16 opcode = 0x10;
    Uint32 dummy;

    Assert_CS_Pin();

    SpiaRegs.SPITXBUF = (opcode) << 8;
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (ctlRegVal.HighLowByte.HighByte << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (ctlRegVal.HighLowByte.LowByte << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    Deassert_CS_Pin();

    return dummy;
}

Uint16 Arinc429_ReadStatusReg(void)
{
    int ret;
    Uint16 opcode = 0x0A;

    Assert_CS_Pin();

    SpiaRegs.SPITXBUF = (opcode << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    ret = SpiaRegs.SPIRXBUF;
    arinc429[3] = ret;

    SpiaRegs.SPITXBUF = (0x0000);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    ret = (SpiaRegs.SPIRXBUF);
    
    arinc429[4] = ret;

    Deassert_CS_Pin();

    return ret;
}

Uint16 Arinc429_ReadCtlReg(void)
{
    Uint16 opcode = 0x0B;
    Uint16 ret;

    Assert_CS_Pin();
  
    SpiaRegs.SPITXBUF = (opcode << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    arinc429[5] = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (0x0000);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    arinc429[6] = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (0x0000);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    arinc429[7] = (SpiaRegs.SPIRXBUF);


    ret = arinc429[6];
    ret = ret << 8;
    ret = ret | arinc429[7];

    Deassert_CS_Pin();

    return ret;
}

Uint32 Arinc429_ReadRxFIFO_ONE_WORD(void)
{
    Uint16 opcode = 0x08;
    Uint32 tmp;
    Uint32 ret;

    Assert_CS_Pin();

    SpiaRegs.SPITXBUF = (opcode << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    tmp = SpiaRegs.SPIRXBUF;

    SpiaRegs.SPITXBUF = (0x0000);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    tmp = SpiaRegs.SPIRXBUF;
    ret = tmp << 24;

    SpiaRegs.SPITXBUF = (0x0000);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    tmp = SpiaRegs.SPIRXBUF;
    ret |= (tmp << 16);

    SpiaRegs.SPITXBUF = (0x0000);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    tmp = SpiaRegs.SPIRXBUF;
    ret |= (tmp << 8);

    SpiaRegs.SPITXBUF = (0x0000);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    tmp = SpiaRegs.SPIRXBUF;
    ret |= (tmp);

    Deassert_CS_Pin();

    return ret;
}

Uint32 Arinc429_WriteTxFIFO_ONE_WORD(Uint32 data)
{
    Uint16 opcode = 0x0E;
    Uint32 dummy;

    Uint16 high;
    Uint32 low;

    low = (Uint16)data;
    high = (Uint16)(data >> 16);

    Assert_CS_Pin();

    SpiaRegs.SPITXBUF = (opcode << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (high);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (high << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (low);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    SpiaRegs.SPITXBUF = (low << 8);
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
    dummy = (SpiaRegs.SPIRXBUF);

    Deassert_CS_Pin();

    return dummy;
}

void Arinc429_MasterReset(void)
{
    int i;
	Arinc429_MR_DEASSERT;

	for(i = 0; i < 100; ++i)
	{
		asm (" NOP");
	}

	Arinc429_MR_ASSERT;
	for(i = 0; i < 100; ++i)
	{
		asm (" NOP");
	}

	Arinc429_MR_DEASSERT;
	for(i = 0; i < 100; ++i)
	{
		asm (" NOP");
	}
}

void Arinc429_InitCtlReg(void)
{
	ARINC429_CTL_REG tmp;
	tmp.all = 0x2800;
	tmp.regVale.SelfTest = 1;

    Arinc429_SetCtlReg(tmp);
}

void Init_Arinc429_Service(void)
{
    Arinc429_MasterReset();
    Arinc429_InitCtlReg();
    gArinc429Para.arinc429RegStatus = Arinc429_ReadStatusReg();
    gArinc429Para.arinc429CtlReg = Arinc429_ReadCtlReg();
}
