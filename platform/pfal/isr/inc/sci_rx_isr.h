#ifndef PF_SCI_RX_ISR_H_
#define PF_SCI_RX_ISR_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sci_service.h"
#include "spwm_service.h"

void PFAL_SCIA_RX_ISR(void);

void PFAL_SCIB_RX_ISR(void);

void PFAL_SCIC_RX_ISR(void);
#endif
