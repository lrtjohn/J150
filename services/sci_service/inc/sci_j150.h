#ifndef SCI_J150_H
#define SCI_J150_H
#include "sci_adapt.h"

/******************Macro**************************/
#define PTR_SCI_J150_TRANS  (&gSciJ150Trans)

/* Head1    Head2   Length    Command    WorkMode   TargetSpeed     RFU     RFU     CheckSum */
/* 1byte    1byte   1byte     2bytes     byte       2bytes          4bytes  4bytes  1byte*/
#define HEAD_LEN                (2)
#define HEAD_1_DATA             (0x55)
#define HEAD_2_DATA             (0xaa)
#define TOTAL_LEN               (0x17)

#define HEAD_1_POS              (0)
#define HEAD_1_POS_LEN          (1)

#define HEAD_2_POS              (HEAD_1_POS + HEAD_1_POS_LEN)
#define HEAD_2_POS_LEN          (1)

#define TOTAL_LEN_POS           (HEAD_2_POS + HEAD_2_POS_LEN)
#define TOTAL_LEN_POS_LEN       (1)

#define COMMAND_POS             (TOTAL_LEN_POS + TOTAL_LEN_POS_LEN)
#define COMMAND_POS_LEN         (2)

#define WORK_MODE_POS           (COMMAND_POS + COMMAND_POS_LEN)
#define WORK_MODE_POS_LEN       (1)

#define TARGET_SPEED_POS        (WORK_MODE_POS + WORK_MODE_POS_LEN)
#define TARGET_SPEED_POS_LEN    (2)

#define RFU_1_POS               (TARGET_SPEED_POS + TARGET_SPEED_POS_LEN)
#define RFU_1_POS_LEN           (4)

#define RFU_2_POS               (RFU_1_POS + RFU_1_POS_LEN)
#define RFU_2_POS_LEN           (4)

#define CHECK_SUM_POS           (RFU_2_POS + RFU_2_POS_LEN)
#define CHECK_SUM_POS_LEN       (1)

/******************Data structure*****************/
typedef enum
{
    WORK_MODE_NORMAL = 1,
    WORK_MODE_SPECIAL,
}WORKMODE;

typedef enum
{
    COMMAND_PARA_CONFIG = 1,
    COMMAND_MOTOR_START,
    COMMAND_MOTOR_STOP,

}COMMAND_DEFINITION;

typedef Uint16(*GetCommand)(unsigned char* data);
typedef Uint16(*GetWorkMode)(unsigned char* data);
typedef Uint16(*GetTargetSpeed)(unsigned char* data);
typedef Uint16(*GetCheckSum)(unsigned char* data);

typedef struct _SCI_APP_PROTOCOL
{
    Uint16          head[HEAD_LEN];
    Uint16          totalLen;
    Uint16          command;
    Uint16          workMode;
    Uint16          targetSpeed;
    Uint16          goodPacketArray[TOTAL_LEN];

    GetCommand      getCommand;
    GetWorkMode     getWorkMode;
    GetTargetSpeed  getTargetSpeed;
    GetCheckSum     getCheckSum;
}SCI_APP_PROTOCOL;

/******************Function***********************/
extern Uint16 J150_APP_PROTOCOL_Init(SCI_APP_PROTOCOL* pAppprotocol);
/***********Extern globale variable***************/
extern SCI_TRANSPORT gSciJ150Trans;
extern SCI_APP_PROTOCOL gSciJ150AppProtocol;
#endif