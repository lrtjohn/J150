#ifndef SCI_PROTOCAL_H_
#define SCI_PROTOCAL_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sci_queue.h"
#include "sys_state_service.h"
#include "prod.h"
#include <stdlib.h>

/*0x5a      0x5a    0x01    0x0102      0x01    0x0a0b  0xcrch     0xcrcl   0xa5    0xa5*/
/*head1     head2   len     serialnum   cmd     data    crcHigh    crcLow   tail1   tail2*/
//UNIT_LEN = len(cmd + data) = 3
//EXTRA_LEN = (head1 + head2 + len + serialnum + crch + crcl + tail1 + tail2) = 9
//OFFSET = (head1 + head2 + len + serialnum) = 5
#define HEAD1 0x5a
#define HEAD2 0x5a
#define TAIL1 0xa5
#define TAIL2 0xa5
#define SUCCESS     (1)
#define FAIL        (0)
#define UNIT_LEN    (3)
#define EXTRA_LEN   (9)
#define OFFSET      (5)





typedef PF_UION_2BYTES VAR16;
typedef void (*functionMsgCodeUnpack)(VAR16 a, int b,int c);
typedef void (*UpdateTxVal)(int a, int b,int c);

void Init_Sci_Protocol(void);

extern SCIRXQUE* gScibRxQue;
extern SCITXQUE* gScibTxQue;
#endif



