#ifndef SCI_QUEUE_H_
#define SCI_QUEUE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "pf_data_struct.h"
#include "sys_state_service.h"



typedef PF_RING_BUFFER SCIRXQUE;
typedef PF_RING_BUFFER SCITXQUE;


int SciRxEnQueue(int e, SCIRXQUE *RS422RxQue);
int SciTxEnQueue(char e, SCITXQUE *RS422TxQue);

int SciRxDeQueue(SCIRXQUE *RS422RxQue);
int SciTxDeQueue(SCITXQUE *RS422TxQue);

int IsSciRxQueueEmpty(SCIRXQUE *RS422RxQue);

int GetSciRxQueLength(SCIRXQUE *RS422RxQue);
int GetSciTxQueLength(SCITXQUE *RS422TxQue);
#endif
