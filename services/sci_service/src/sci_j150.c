#include "sci_j150.h"
#include <stdio.h>


static Uint16 J150_APP_PROTOCOL_GetCommand(unsigned char* data)
{
    Uint16 command;
    
    command = ((data[COMMAND_POS]) << 8) | data[COMMAND_POS + 1];

    return command;
}

static Uint16 J150_APP_PROTOCOL_GetWorkMode(unsigned char* data)
{
    return data[WORK_MODE_POS];
}

static Uint16 J150_APP_PROTOCOL_GetTargetSpeed(unsigned char* data)
{
    Uint16 targetSpeed;
    
    targetSpeed = ((data[TARGET_SPEED_POS]) << 8) | data[TARGET_SPEED_POS + 1];

    return targetSpeed;
}

static Uint16 J150_APP_PROTOCOL_GetCheckSum(unsigned char* data)
{
    return data[CHECK_SUM_POS];
}

static int J150_TransInit(void)
{
    return SUCCESS;
}

static int J150_TransConfig(void)
{
    return SUCCESS;
}

static int J150_TransStart(void)
{
    return SUCCESS;
}

static int J150_TransFindHead(SCIRXQUE* q)
{
    return SUCCESS;
}

static int J150_TransCheckLength(SCIRXQUE* q)
{

    return SUCCESS;
}

static int J150_TransCheckTail(SCIRXQUE* q)
{

    return SUCCESS;
}

static int J150_TransSaveGoodPacket(int len, SCIRXQUE* q)
{

    return SUCCESS;
}

static int J150_TransCheckSum(unsigned char* q)
{

    return SUCCESS;
}

static int J150_TransUpdateHeadPos(SCIRXQUE* q)
{

    return SUCCESS;
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
    J150_APP_PROTOCOL_GetCommand,
    J150_APP_PROTOCOL_GetWorkMode,
    J150_APP_PROTOCOL_GetTargetSpeed,
    J150_APP_PROTOCOL_GetCheckSum
};
SCI_TRANSPORT gSciJ150Trans =
{
    J150_TransInit,
    J150_TransConfig,
    J150_TransStart,
    J150_TransFindHead,
    J150_TransCheckLength,
    J150_TransCheckTail,
    J150_TransSaveGoodPacket,
    J150_TransCheckSum,
    J150_TransUpdateHeadPos,
};

void SCI_J150_UnpackData(SCIRXQUE* q, SCI_APP_PROTOCOL* pAppProtocol)
{
    while(GetSciRxQueLength(q) >= pAppProtocol->totalLen);
    {
        if(SCI_Trans_Adapt_FindHead(q) == FAIL)
        {
            return;
        }
        else
        {
            /* code */
        }

        if(SCI_Trans_Adapt_CheckLength(q) == FAIL)
        {
            return;
        }
        else
        {
            /* code */
        }

        if(SCI_Trans_Adapt_CheckTail(q) == FAIL)
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

        SCI_Trans_Adapt_SaveGoodPacket(pAppProtocol->totalLen, q);

        if(SCI_Trans_Adapt_CheckSum(pAppProtocol->goodPacketArray) == FAIL)
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

        SCI_Trans_Adapt_UpdateHeadPos(q);
    }
}
