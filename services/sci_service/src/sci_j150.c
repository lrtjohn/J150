#include "sci_j150.h"
#include <stdio.h>

/*
* J150 protocol layer API
*/
static Uint16 J150_APP_PROTOCOL_GetCommand(unsigned char* data);
static Uint16 J150_APP_PROTOCOL_GetWorkMode(unsigned char* data);
static Uint16 J150_APP_PROTOCOL_GetTargetSpeed(unsigned char* data);
static Uint16 J150_APP_PROTOCOL_GetCheckSum(unsigned char* data);
/*
* J150 transport layer API
*/
static int J150_TransInit(void);
static int J150_TransConfig(void);
static int J150_TransStart(void);
static int J150_TransFindHead(SCIRXQUE* q);
static int J150_TransCheckLength(SCIRXQUE* q);
static int J150_TransCheckTail(SCIRXQUE* q);
static int J150_TransSaveGoodPacket(int len, SCIRXQUE* q);
static int J150_TransCheckSum(unsigned char* q);
static int J150_TransUpdateHeadPos(SCIRXQUE* q);
/*
* J150 protocol and transport layer global variable
*/
SCI_APP_PROTOCOL gSciJAppProtocol;
SCI_APP_PROTOCOL* pSciJAppProtocol = NULL;

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

/*
* API definition
*/
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


Uint16 SCI_APP_PROTOCOL_GetLength()
{
    return pSciJAppProtocol->totalLen;
}

unsigned char* SCI_APP_PROTOCOL_GetGoodPacketArray()
{
    return pSciJAppProtocol->goodPacketArray;
}

void SCI_APP_PROTOCOL_Init(void)
{
    pSciJAppProtocol = &gSciJ150AppProtocol; 
}

void SCI_J150_UnpackData(SCIRXQUE* q)
{
    while(GetSciRxQueLength(q) >= SCI_APP_PROTOCOL_GetLength());
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

        SCI_Trans_Adapt_SaveGoodPacket(SCI_APP_PROTOCOL_GetLength(), q);

        if(SCI_Trans_Adapt_CheckSum(SCI_APP_PROTOCOL_GetGoodPacketArray()) == FAIL)
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
