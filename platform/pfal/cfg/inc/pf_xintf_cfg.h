#ifndef PF_XINTF_CFG_H_
#define PF_XINTF_CFG_H_

// #include "DSP2833x_Gpio.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

#define TOTAL_SPI 1

typedef enum
{
    DATA_MODE_16BIT,
    DATA_MODE_32BIT
}XINTF_DATA_MODE;

typedef enum
{
    ADDR_DISABLE,
    ADDR_ENABLE
}XINTF_ADDR_ENABLE;

typedef enum
{
    ZONE0_DISABLE,
    ZONE0_ENABLE
}XINTF_ZONE0_ENABLE;

typedef enum
{
    ZONE6_DISABLE,
    ZONE6_ENABLE
}XINTF_ZONE6_ENABLE;

typedef enum
{
    ZONE7_DISABLE,
    ZONE7_ENABLE
}XINTF_ZONE7_ENABLE;

typedef struct
{
    XINTF_DATA_MODE xintfDataMode;
    XINTF_ADDR_ENABLE xintfAddrEnable;
    XINTF_ZONE0_ENABLE xintfZone0Enale;
    XINTF_ZONE6_ENABLE xintfZone6Enale;
    XINTF_ZONE7_ENABLE xintfZone7Enale;
}CFG_XINTF_TBL;

typedef void (*CFG_XINTF_HDL_TBL)(CFG_XINTF_TBL dataMode);

void PFAL_XINTF_CFG(CFG_XINTF_TBL* cfgXintfTbl, int len);

#endif
