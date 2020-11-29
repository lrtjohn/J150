#ifndef SCI_J150_H
#define SCI_J150_H

#include "sci_adapt.h"
#include "sys_state_service.h"

/**************************************************************************************************************************
     ██  ██ ███████  ██████      ██████  ██   ██     ██████  ██████   ██████  ████████  ██████   ██████  ██████  ██
     ██ ███ ██      ██  ████     ██   ██  ██ ██      ██   ██ ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██
     ██  ██ ███████ ██ ██ ██     ██████    ███       ██████  ██████  ██    ██    ██    ██    ██ ██      ██    ██ ██
██   ██  ██      ██ ████  ██     ██   ██  ██ ██      ██      ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██
 █████   ██ ███████  ██████      ██   ██ ██   ██     ██      ██   ██  ██████     ██     ██████   ██████  ██████  ███████
****************************************************************************************************************************/

/******************Macro**************************/
/* Head1    Head2   Length    Command    WorkMode   TargetSpeed     RFU     RFU     CheckSum */
/* 1byte    1byte   1byte     2bytes     1byte       2bytes          4bytes  4bytes  1byte*/
#define HEAD_1_DATA             (0x55)
#define HEAD_2_DATA             (0xaa)
#define TOTAL_LEN               (0x11)
#define HEAD_LEN                (2)

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
    COMMAND_PARA_NONE       = 0, 
    COMMAND_PARA_CONFIG     = 0x0C01,
    COMMAND_MOTOR_START     = 0x0C02,
    COMMAND_MOTOR_STOP      = 0x0C03,
    COMMAND_DEBUG_DATA      = 0x0C04,
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
    COMMAND_DEFINITION          command;
    WORKMODE                    workMode;
    Uint16                      targetSpeed;
    unsigned char               goodPacketArray[TOTAL_LEN];

    GetCommand                  getCommand;
    GetWorkMode                 getWorkMode;
    GetTargetSpeed              getTargetSpeed;
    UnpackPayLoad               unpackPayload;
}SCI_APP_PROTOCOL_RX;

/******************Function***********************/
extern void SCI_APP_PROTOCOL_RX_Init(SCI_APP_PROTOCOL_RX* rxAppProtocol);        
/***********Extern globale variable***************/
extern SCI_TRANSPORT_RX    gSciTransRx_J150;
extern SCI_APP_PROTOCOL_RX gSciAppProtocolRx_J150;

/**************************************************************************************************************************
     ██  ██ ███████  ██████      ████████ ██   ██     ██████  ██████   ██████  ████████  ██████   ██████  ██████  ██
     ██ ███ ██      ██  ████        ██     ██ ██      ██   ██ ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██
     ██  ██ ███████ ██ ██ ██        ██      ███       ██████  ██████  ██    ██    ██    ██    ██ ██      ██    ██ ██
██   ██  ██      ██ ████  ██        ██     ██ ██      ██      ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██
 █████   ██ ███████  ██████         ██    ██   ██     ██      ██   ██  ██████     ██     ██████   ██████  ██████  ███████
****************************************************************************************************************************/
/*******************SCI TX PROTOCOL START HERE********************/
#define TX_HEAD1_DATA               (0x55)
#define TX_HEAD2_DATA               (0xAA)
#define TX_LENGTH_DATA              (0x21)

#define TX_HEAD1_POS                (0)
#define TX_HEAD1_LEN                (1)

#define TX_HEAD2_POS                (TX_HEAD1_POS + TX_HEAD1_LEN)
#define TX_HEAD2_LEN                (1)

#define TX_LENGTH_POS               (TX_HEAD2_POS + TX_HEAD2_LEN)
#define TX_LENGTH_LEN               (1)

#define TX_WORK_STATUS_POS          (TX_LENGTH_POS + TX_LENGTH_LEN)
#define TX_WORK_STATUS_LEN          (2)

#define TX_SYS_STATUS_1_POS         (TX_WORK_STATUS_POS + TX_WORK_STATUS_LEN)
#define TX_SYS_STATUS_1_LEN         (2)

#define TX_SYS_STATUS_2_POS         (TX_SYS_STATUS_1_POS + TX_SYS_STATUS_1_LEN)
#define TX_SYS_STATUS_2_LEN         (2)

#define TX_FAULT_STATUS_POS         (TX_SYS_STATUS_2_POS + TX_SYS_STATUS_2_LEN)
#define TX_FAULT_STATUS_LEN         (4)

#define TX_FRAME_CNT_POS            (TX_FAULT_STATUS_POS + TX_FAULT_STATUS_LEN)
#define TX_FRAME_CNT_LEN            (4)

#define TX_TARGET_SPEED_POS         (TX_FRAME_CNT_POS + TX_FRAME_CNT_LEN)
#define TX_TARGET_SPEED_LEN         (2)

#define TX_CURRENT_SPEED_POS        (TX_TARGET_SPEED_POS  + TX_TARGET_SPEED_LEN)
#define TX_CURRENT_SPEED_LEN        (2)

#define TX_BUS_VOLTAGE_POS          (TX_CURRENT_SPEED_POS + TX_CURRENT_SPEED_LEN)
#define TX_BUS_VOLTAGE_LEN          (2)

#define TX_BUS_CURRENT_POS          (TX_BUS_VOLTAGE_POS + TX_BUS_VOLTAGE_LEN)
#define TX_BUS_CURRENT_LEN          (2)

#define TX_SERVO_TEMP_POS           (TX_BUS_CURRENT_POS + TX_BUS_CURRENT_LEN)
#define TX_SERVO_TEMP_LEN           (1)

#define TX_MOTOR_TEMP_POS           (TX_SERVO_TEMP_POS + TX_SERVO_TEMP_LEN)
#define TX_MOTOR_TEMP_LEN           (1)

#define TX_FW_VERSION_POS           (TX_MOTOR_TEMP_POS + TX_MOTOR_TEMP_LEN)
#define TX_FW_VERSION_LEN           (2)

#define TX_WORK_MODE_POS            (TX_FW_VERSION_POS + TX_FW_VERSION_LEN)
#define TX_WORK_MODE_LEN            (1)

#define TX_RFU_POS                  (TX_WORK_MODE_POS + TX_WORK_MODE_LEN)
#define TX_RFU_LEN                  (2)

#define TX_CHECK_SUM_POS            (TX_RFU_POS + TX_RFU_LEN)
#define TX_CHECK_SUM_LEN            (1)

#define SCI_TX_ONE_FRAME_LENGTH     (TX_LENGTH_DATA)


typedef struct _SCI_APP_PROTOCOL_TX
{
    Uint16 txHead1;     /* 1 byte */
    Uint16 txHead2;     /* 1 byte */
    Uint16 txLength;    /* 1 byte */
    Uint16 workStatus;  /* 2 byte */
    Uint16 sysStatus1;  /* 2 byte */
    Uint16 sysStatus2;  /* 2 byte */
    Uint32 faultStatus; /* 4 byte */
    Uint32 frameCnt;    /* 4 byte */
    Uint16 targetSpeed; /* 2 byte */
    Uint16 currentSpeed;/* 2 byte */
    Uint16 busVoltage;  /* 2 byte */
    Uint16 busCurrent;  /* 2 byte */
    Uint16 servoTemp;   /* 1 byte */
    Uint16 motorTemp;   /* 1 byte */
    Uint16 fwVersionNum;/* 2 byte */
    Uint16 workMode;    /* 1 byte */
    Uint16 RFU;         /* 2 byte */
    Uint16 checkSum;    /* 1 byte */
    /* data */
}SCI_APP_PROTOCOL_TX;

extern SCI_TRANSPORT_TX gSciTransTx_J150;
extern SCI_APP_PROTOCOL_TX gSciAppProtocolTx_J150;
extern Uint16 gTxFrameArray[SCI_TX_ONE_FRAME_LENGTH];

//extern Uint16 gCnt_Clear = 0;

extern void SCI_APP_PROTOCOL_TX_Init(SCI_APP_PROTOCOL_TX* txAppProtocol);
extern Uint16 gDebugDataArray[4];
#endif
