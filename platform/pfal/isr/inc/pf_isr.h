#ifndef PF_ISR_H_
#define PF_ISR_H_

#include "pwm_isr.h"
#include "sci_rx_isr.h"
#include "sci_tx_isr.h"
#include "timer0_isr.h"
#include "timer1_isr.h"



#define DISABLE_GLOBAL_INTERRUPT        DINT;\
                                        DRTM;

#define ENABLE_GLOBAL_INTERRUPT         EINT;\
                                        ERTM;

#endif
