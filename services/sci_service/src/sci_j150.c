#include "sci_j150.h"
#include <stdio.h>


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

static Uint16 APP_PROTOCOL_GetCheckSum(unsigned char* data)
{
    return data[CHECK_SUM_POS];
}

static int J150_Init(void)
{
    return SUCCESS;
}

static int J150_Config(void)
{
    return SUCCESS;
}

static int J150_Start(void)
{
    return SUCCESS;
}

static int J150_FindHead(SCIRXQUE* q)
{
    return SUCCESS;
}

static int J150_CheckLength(SCIRXQUE* q)
{

    return SUCCESS;
}

static int J150_CheckTail(SCIRXQUE* q)
{

    return SUCCESS;
}

static int J150_SaveGoodPacket(int len, SCIRXQUE* q)
{

    return SUCCESS;
}

static int J150_CheckSum(unsigned char* q)
{

    return SUCCESS;
}

static int J150_UpdateHeadPos(SCIRXQUE* q)
{

    return SUCCESS;
}
Uint16 J150_APP_PROTOCOL_Init(SCI_APP_PROTOCOL* pAppProtocol)
{
    pAppProtocol->head[0]           = HEAD_1_DATA;
    pAppProtocol->head[1]           = HEAD_1_DATA;
    pAppProtocol->totalLen          = TOTAL_LEN;
    pAppProtocol->getCommand        = APP_PROTOCOL_GetCommand;
    pAppProtocol->getWorkMode       = APP_PROTOCOL_GetWorkMode;
    pAppProtocol->getTargetSpeed    = APP_PROTOCOL_GetTargetSpeed;
    pAppProtocol->getCheckSum       = APP_PROTOCOL_GetCheckSum;
    return 1;
}



SCI_APP_PROTOCOL gSciJ150AppProtocol =
{
    {
        HEAD_1_DATA,
        HEAD_2_DATA
    },
    TOTAL_LEN,
    0,
    WORK_MODE_NORMAL,
    0,
    {
        0
    },
    APP_PROTOCOL_GetCommand,
    APP_PROTOCOL_GetWorkMode,
    APP_PROTOCOL_GetTargetSpeed,
    APP_PROTOCOL_GetCheckSum
};
SCI_TRANSPORT gSciJ150Trans =
{
    J150_Init,
    J150_Config,
    J150_Start,
    J150_FindHead,
    J150_CheckLength,
    J150_CheckTail,
    J150_SaveGoodPacket,
    J150_CheckSum,
    J150_UpdateHeadPos,
};

void SCI_J150_UnpackData(SCIRXQUE* q, SCI_APP_PROTOCOL* pAppProtocol)
{
    while(GetSciRxQueLength(q) >= pAppProtocol->totalLen);
    {
        if(SCI_Adapt_FindHead(q) == FAIL)
        {
            return;
        }
        else
        {
            /* code */
        }

        if(SCI_Adapt_CheckLength(q) == FAIL)
        {
            return;
        }
        else
        {
            /* code */
        }

        if(SCI_Adapt_CheckTail(q) == FAIL)
        {
            if(SciRxDeQueue(q) == 0)
            {

            }
            return;
        }
        else
        {
            /* code */
        }

        SCI_Adapt_SaveGoodPacket(pAppProtocol->totalLen, q);

        if(SCI_Adapt_CheckSum(pAppProtocol->goodPacketArray) == FAIL)
        {
            if(SciRxDeQueue(q) == 0)
            {

            }
            return;
        }
        else
        {
            /* code */
        }

        SCI_Adapt_UpdateHeadPos(q);

    }
}
