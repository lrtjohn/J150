#ifndef SCI_SERVICE_H_
#define SCI_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sci_protocal.h"
#include "sci_queue.h"


void Sci_A_Receive(SCIRXQUE* RS422RxQue);
void Sci_B_Receive(SCIRXQUE* RS422RxQue);
void Sci_C_Receive(SCIRXQUE* RS422RxQue);

void SCI_A_Transmit(SCITXQUE* RS422TxQue);
void SCI_B_Transmit(SCITXQUE* RS422TxQue);
void SCI_C_Transmit(SCITXQUE* RS422TxQue);

void ClearSciaRxOverFlow(void);
void ClearScibRxOverFlow(void);
void ClearScicRxOverFlow(void);

void CheckEnableSciaTx(SCITXQUE* RS422TxQue);
void CheckEnableScibTx(SCITXQUE* RS422TxQue);
void CheckEnableScicTx(SCITXQUE* RS422TxQue);

#define Init_Sci_Service(){                                                 \
                            Init_Sci_Protocol();                            \
	                        SCI_Trans_AdaptRx_Init(&gSciTransRx_J150);          \
	                        SCI_APP_PROTOCOL_Init(&gSciAppProtocolRx_J150);   \
                          }          
#endif

