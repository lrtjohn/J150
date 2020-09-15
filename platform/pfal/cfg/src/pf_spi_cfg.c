#include "pf_spi_cfg.h"

const CFG_SPI_TBL CfgSpiTbl[] =
{
    {54, 55, 56, 57}
};

void CFG_SPI_A(CFG_SPI_TBL cfgSpiTblElement)
{
    if(
        (cfgSpiTblElement.spiSIMOAPin == 54) && 
        (cfgSpiTblElement.spiSOMIAPin == 55) && 
        (cfgSpiTblElement.spiCLKAPin  == 56) && 
        (cfgSpiTblElement.spiSTEAPin  == 57)
      )
    {
        EALLOW;
        GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0;   // Enable pull-up on GPIO54 (SPISIMOA)
        GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;   // Enable pull-up on GPIO55 (SPISOMIA)
        GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;   // Enable pull-up on GPIO56 (SPICLKA)
        GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0;   // Enable pull-up on GPIO57 (SPISTEA)

        GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3; // Asynch input GPIO16 (SPISIMOA)
        GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input GPIO17 (SPISOMIA)
        GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO18 (SPICLKA)
        GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO19 (SPISTEA)

        GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1; // Configure GPIO54 as SPISIMOA
        GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; // Configure GPIO55 as SPISOMIA
        GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
        GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA
        EDIS;         
    }
    else if(
             (cfgSpiTblElement.spiSIMOAPin == 16) && 
             (cfgSpiTblElement.spiSOMIAPin == 17) && 
             (cfgSpiTblElement.spiCLKAPin  == 18) && 
             (cfgSpiTblElement.spiSTEAPin  == 19)
            )
    {
        EALLOW;
        GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
        GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
        GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
        GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

        GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
        GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
        GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
        GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA
        EDIS;

    }
    else
    {
        //TODO generate warning info
    }

    SpiaRegs.SPICCR.all =0x0007;	// Reset on, rising edge, 16-bit char bits
    SpiaRegs.SPICTL.all =0x0006;
    SpiaRegs.SPIBRR =0x01d;
    SpiaRegs.SPICTL.bit.CLK_PHASE = 1;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;
    // SpiaRegs.SPICCR.all =0x00C7;
    SpiaRegs.SPIPRI.bit.FREE = 1;  // Set so breakpoints don't disturb xmission
}

const CFG_SPI_HDL_TBL SDB_CfgSpiHdlTbl[TOTAL_SPI] =
{
     CFG_SPI_A
};

void PFAL_SPI_CFG(CFG_SPI_TBL* cfgSpiTbl, int len)
{
#if(PF_SPI == INCLUDE_FEATURE)
    SDB_CfgSpiHdlTbl[0](cfgSpiTbl[0]);
#endif
}
