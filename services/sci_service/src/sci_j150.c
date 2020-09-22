#include "sci_j150.h"

SCI_TRANSPORT gSciJ150Trans;


static Uint16 APP_PROTOCOL_GetCommand(unsigned char* data)
{
    Uint16 command;
    
    command = ((data[COMMAND_POS]) << 8) | data[COMMAND_POS + 1];

    return command;
}

static Uint16 APP_PROTOCOL_GetWorkMode(unsigned char* data)
{
    return data[WORK_MODE_POS];
}

static Uint16 APP_PROTOCOL_GetTargetSpeed(unsigned char* data)
{
    Uint16 targetSpeed;
    
    targetSpeed = ((data[TARGET_SPEED_POS]) << 8) | data[TARGET_SPEED_POS + 1];

    return targetSpeed;
}

static Uint16 APP_PROTOCOL_Init(SCI_APP_PROTOCOL* pAppProtocol)
{
    pAppProtocol->head[0]           = HEAD_1_DATA;
    pAppProtocol->head[1]           = HEAD_1_DATA;
    pAppProtocol->totalLen          = TOTAL_LEN;
    pAppProtocol->init              = APP_PROTOCOL_Init;
    pAppProtocol->getCommand        = APP_PROTOCOL_GetCommand;
    pAppProtocol->getWorkMode       = APP_PROTOCOL_GetWorkMode;
    pAppProtocol->getTargetSpeed    = APP_PROTOCOL_GetTargetSpeed;
    return 1;
}
