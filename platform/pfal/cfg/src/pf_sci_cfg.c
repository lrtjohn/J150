#include "pf_sci_cfg.h"
#include "prod.h"

const CFG_SCI_TBL CFG_SCI_INFO[] =
{
    {
        {
            SCIA,       //sci moudule, A, B, C
            28,         //sci rx gpio index
            29          //sci tx gpio index
        },
        {
            BAUD_RATE_115200    //sci baud rate
        }
    },
    {
        {
            SCIB, 
            11,
            9
        },
        {
            BAUD_RATE_115200
        }
    },
    {
        {
            SCIC, 
            62,
            63
        },
        {
            BAUD_RATE_115200
        }
    }
};


void CFG_SCI_A(CFG_SCI_TBL cfgSciTblElement)
{
    Uint16 baudrate = 0;
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up for GPIO29 (SCITXDA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation

//SCI WORKING MODE
    SciaRegs.SCICCR.all                 = 0x0007;       // 1 stop bit,  No loopback No parity,8 char bits, async mode, idle-line protocol
    SciaRegs.SCICTL1.all                = 0x0003;       // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all                = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA       = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA     = 1;
    switch(cfgSciTblElement.cfgSciParam.sciBaudRate)
    {
        case BAUD_RATE_115200:
            baudrate = (Uint16)((30000000/115200/8) - 1);
            SciaRegs.SCIHBAUD = (baudrate & 0xff00) >> 8;
            SciaRegs.SCILBAUD = baudrate & 0x00ff;
            break;
        case BAUD_RATE_9600:
            baudrate = (Uint16)((30000000/9600/8) - 1);
            SciaRegs.SCIHBAUD = (baudrate & 0xff00) >> 8;
            SciaRegs.SCILBAUD = baudrate & 0x00ff;
            break;
    }
    if(cfgSciTblElement.cfgSciParam.sciLoopBack == ENABLE_LOOP_BACK)
    {
        SciaRegs.SCICCR.bit.LOOPBKENA   = 1; 
    }
    else
    {
        SciaRegs.SCICCR.bit.LOOPBKENA   = 0; 
    }
    SciaRegs.SCICTL1.all                = 0x0023;   // Relinquish SCI from Reset

//FIFO
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET   = 0;
    SciaRegs.SCIFFRX.bit.RXFIFORESET    = 0;
    SciaRegs.SCIFFTX.all                = 0xE028;
    SciaRegs.SCIFFTX.bit.TXFFIENA       = 1;

    SciaRegs.SCIFFTX.bit.TXFFINTCLR     = 1;
    SciaRegs.SCIFFRX.all                = 0x2028;

    SciaRegs.SCIFFRX.bit.RXFFIENA       = 1;
    SciaRegs.SCIFFCT.all                = 0x0;
    EDIS;
}
void CFG_SCI_B(CFG_SCI_TBL cfgSciTblElement)
{
    Uint16 baudrate = 0;
    EALLOW;
    switch(cfgSciTblElement.cfgSciGpio.rxNum)
    {
        case 11:
            GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;
            GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;
            GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;
            break;
        case 15:
            GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;
            GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;
            GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;


            break;
        case 19:
            GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;
            GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;
            GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;
            break;
        case 23:
            GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;
            GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;
            GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;
            break;
        default:
            //TODO generate warning
            break;
    }

    switch(cfgSciTblElement.cfgSciGpio.txNum)
    {
        case 9:
            GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;
            GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;
            break;
        case 14:
            GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;
            GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;
            break;
        case 18:
            GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;
            GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;
            break;
        case 22:
            GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;
            GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;
            break;
        default:
            //TODO generate warning
            break;
    }

    ScibRegs.SCICCR.all                 = 0x0007;       // 1 stop bit,  No loopback No parity,8 char bits, async mode, idle-line protocol
    ScibRegs.SCICTL1.all                = 0x0003;       // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    ScibRegs.SCICTL2.all                = 0x0003;
    ScibRegs.SCICTL2.bit.TXINTENA       = 1;
    ScibRegs.SCICTL2.bit.RXBKINTENA     = 1;
    switch(cfgSciTblElement.cfgSciParam.sciBaudRate)
    {
        case BAUD_RATE_115200:
            baudrate = (Uint16)((30000000/115200/8) - 1);
            ScibRegs.SCIHBAUD = (baudrate & 0xff00) >> 8;
            ScibRegs.SCILBAUD = baudrate & 0x00ff;
            break;
        case BAUD_RATE_9600:
            baudrate = (Uint16)((30000000/9600/8) - 1);
            ScibRegs.SCIHBAUD = (baudrate & 0xff00) >> 8;
            ScibRegs.SCILBAUD = baudrate & 0x00ff;
            break;
    }
    if(cfgSciTblElement.cfgSciParam.sciLoopBack == ENABLE_LOOP_BACK)
    {
        ScibRegs.SCICCR.bit.LOOPBKENA   = 1; 
    }
    else
    {
        ScibRegs.SCICCR.bit.LOOPBKENA   = 0; 
    }
    ScibRegs.SCICTL1.all                = 0x0023;   // Relinquish SCI from Reset
//FIFO
    ScibRegs.SCIFFTX.bit.TXFIFOXRESET   = 0;
    ScibRegs.SCIFFRX.bit.RXFIFORESET    = 0;
    ScibRegs.SCIFFTX.all                = 0xE028;
    ScibRegs.SCIFFTX.bit.TXFFIENA       = 1;

    ScibRegs.SCIFFTX.bit.TXFFINTCLR     = 1;
    ScibRegs.SCIFFRX.all                = 0x2021;

    ScibRegs.SCIFFRX.bit.RXFFIENA       = 1;
    ScibRegs.SCIFFCT.all                = 0x0;
    EDIS;
}
void CFG_SCI_C(CFG_SCI_TBL cfgSciTblElement)
{
    Uint16 baudrate = 0;
    EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;    // Enable pull-up for GPIO62 (SCIRXDC)
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;    // Enable pull-up for GPIO63 (SCITXDC)

    GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)

    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 for SCIRXDC operation
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 for SCITXDC operation

    ScicRegs.SCICCR.all                 = 0x0007;       // 1 stop bit,  No loopback No parity,8 char bits, async mode, idle-line protocol
    ScicRegs.SCICTL1.all                = 0x0003;       // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    ScicRegs.SCICTL2.all                = 0x0003;
    ScicRegs.SCICTL2.bit.TXINTENA       = 1;
    ScicRegs.SCICTL2.bit.RXBKINTENA     = 1;
    switch(cfgSciTblElement.cfgSciParam.sciBaudRate)
    {
        case BAUD_RATE_115200:
            baudrate = (Uint16)((30000000/115200/8) - 1);
            ScicRegs.SCIHBAUD = (baudrate & 0xff00) >> 8;
            ScicRegs.SCILBAUD = baudrate & 0x00ff;
            break;
        case BAUD_RATE_9600:
            baudrate = (Uint16)((30000000/9600/8) - 1);
            ScicRegs.SCIHBAUD = (baudrate & 0xff00) >> 8;
            ScicRegs.SCILBAUD = baudrate & 0x00ff;
            break;
    }

    if(cfgSciTblElement.cfgSciParam.sciLoopBack == ENABLE_LOOP_BACK)
    {
        ScicRegs.SCICCR.bit.LOOPBKENA   = 1; 
    }
    else
    {
        ScicRegs.SCICCR.bit.LOOPBKENA   = 0; 
    }
    
    ScicRegs.SCICCR.bit.LOOPBKENA       = 0;        // enable loop back
    ScicRegs.SCICTL1.all                = 0x0023;   // Relinquish SCI from Reset
//FIFO
    ScicRegs.SCIFFTX.bit.TXFIFOXRESET   = 0;
    ScicRegs.SCIFFRX.bit.RXFIFORESET    = 0;
    ScicRegs.SCIFFTX.all                = 0xE028;
    ScicRegs.SCIFFTX.bit.TXFFIENA       = 0;

    ScicRegs.SCIFFTX.bit.TXFFINTCLR     = 1;
    ScicRegs.SCIFFRX.all                = 0x2028;

    ScicRegs.SCIFFRX.bit.RXFFIENA       = 1;
    ScicRegs.SCIFFCT.all                = 0x0;
    EDIS;
}

const CFG_SCI_HDL_TBL SDB_CfgSCIHdlTbl[TOTAL_SCI] =
{
     CFG_SCI_A,
     CFG_SCI_B,
     CFG_SCI_C
};


void PFAL_SCI_CFG(CFG_SCI_TBL* cfgSciTbl, int len)
{
#if(PF_SCI == INCLUDE_FEATURE)
    int i = 0;
    EALLOW;
    for(i = 0; i < len; ++i)
    {
        SDB_CfgSCIHdlTbl[cfgSciTbl[i].cfgSciGpio.sciModule](cfgSciTbl[i]);
    }
    EDIS;
#endif
}
