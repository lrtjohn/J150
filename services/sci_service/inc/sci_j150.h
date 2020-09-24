#ifndef SCI_J150_H
#define SCI_J150_H
#include "sci_adapt.h"
#include "sys_state_service.h"

/******************Macro**************************/
#define PTR_SCI_J150_TRANS  (&gSciJ150Trans)

/* Head1    Head2   Length    Command    WorkMode   TargetSpeed     RFU     RFU     CheckSum */
/* 1byte    1byte   1byte     2bytes     1byte       2bytes          4bytes  4bytes  1byte*/
#define HEAD_LEN                (2)
#define HEAD_1_DATA             (0x55)
#define HEAD_2_DATA             (0xaa)
#define TOTAL_LEN               (0x11)

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

#define RX_MIN_TARGET_SPEED     (500)
#define RX_MAX_TARGET_SPEED     (5000)
/******************Data structure*****************/
typedef enum
{
    WORK_MODE_NORMAL = 1,
    WORK_MODE_SPECIAL,
}WORKMODE;

typedef enum
{
    COMMAND_PARA_NONE = 0, 
    COMMAND_PARA_CONFIG = 1,
    COMMAND_MOTOR_START = 2,
    COMMAND_MOTOR_STOP =3,
}COMMAND_DEFINITION;

typedef enum
{
    RX_STATUS_INIT,
    RX_STATUS_CONFIG,
}RX_STATUS;

#define IS_WORK_MODE_GOOD(mode)             ((mode == WORK_MODE_NORMAL) || (mode == WORK_MODE_SPECIAL))
#define IS_COMMAND_GOOD(cmd)                ((cmd == COMMAND_PARA_CONFIG) || (cmd == COMMAND_MOTOR_START) || (cmd == COMMAND_MOTOR_STOP))
#define IS_TARGET_SPEED_GOOD(speed)         (speed >= RX_MIN_TARGET_SPEED && speed <= RX_MAX_TARGET_SPEED)
#define IS_PAYLOAD_GOOD(mode, cmd, speed)   (IS_WORK_MODE_GOOD(mode) && IS_COMMAND_GOOD(cmd) && IS_TARGET_SPEED_GOOD(speed))

typedef Uint16(*GetCommand)(unsigned char* data);
typedef Uint16(*GetWorkMode)(unsigned char* data);
typedef Uint16(*GetTargetSpeed)(unsigned char* data);
typedef Uint16(*GetCheckSum)(unsigned char* data);
typedef Uint16(*UnpackPayLoad)(void);

typedef struct _SCI_APP_PROTOCOL_RX
{
    Uint16                      head[HEAD_LEN];
    Uint16                      totalLen;
    COMMAND_DEFINITION          command;
    WORKMODE                    workMode;
    Uint16          targetSpeed;
    unsigned char   goodPacketArray[TOTAL_LEN];

    GetCommand      getCommand;
    GetWorkMode     getWorkMode;
    GetTargetSpeed  getTargetSpeed;
    GetCheckSum     getCheckSum;
    UnpackPayLoad   unpackPayload;
}SCI_APP_PROTOCOL_RX;

/******************Function***********************/
extern void SCI_APP_PROTOCOL_Init(SCI_APP_PROTOCOL_RX* appProtocol);
extern void J150_SCI_UnpackData(SCIRXQUE* q);
/***********Extern globale variable***************/
extern SCI_TRANSPORT_RX    gSciTransRx_J150;
extern SCI_APP_PROTOCOL_RX gSciAppProtocolRx_J150;
#endif
