#ifndef PROD_H_
#define PROD_H_


#include "prod_defs.h"

/**********************************************************************************************************************************
â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ€�      â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ€�   â–ˆâ–ˆâ–ˆâ€�    â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�
â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�     â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ€�    â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�
â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�     â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�    â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�  â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�  â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�
â–ˆâ–ˆâ€�â€�â€�â€�â€� â–ˆâ–ˆâ€�     â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â€�â€�â€�  â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�    â–ˆâ–ˆâ€�â€�â€�â€�  â–ˆâ–ˆâ€�â€�â€�â€�  â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â€�
â–ˆâ–ˆâ€�     â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�     â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�â–ˆâ–ˆâ€� â€�â€�â€� â–ˆâ–ˆâ€�    â–ˆâ–ˆâ€�     â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�
***********************************************************************************************************************************/
#define PF_ADC                              INCLUDE_FEATURE
#define PF_GPIO                             INCLUDE_FEATURE
#define PF_ISR                              INCLUDE_FEATURE
#define PF_PWM                              INCLUDE_FEATURE
#define PF_SPI                              INCLUDE_FEATURE
#define PF_TIMER                            INCLUDE_FEATURE
#define PF_SCI                              INCLUDE_FEATURE
#define PF_XINTF                            INCLUDE_FEATURE
#define PF_FLASH                            INCLUDE_FEATURE

#define PF_PWM_1A							INCLUDE_FEATURE
#define PF_PWM_1B							INCLUDE_FEATURE
#define PF_PWM_2A							INCLUDE_FEATURE
#define PF_PWM_2B							INCLUDE_FEATURE
#define PF_PWM_3A							INCLUDE_FEATURE
#define PF_PWM_3B							INCLUDE_FEATURE
#define PF_PWM_4A							NOT_INCLUDE_FEATURE
#define PF_PWM_4B							NOT_INCLUDE_FEATURE
#define PF_PWM_5A							NOT_INCLUDE_FEATURE
#define PF_PWM_5B							NOT_INCLUDE_FEATURE
#define PF_PWM_6A							NOT_INCLUDE_FEATURE
#define PF_PWM_6B							NOT_INCLUDE_FEATURE

#define PF_PWM_RVDT							NOT_INCLUDE_FEATURE
#define PF_PWM_ECAP							INCLUDE_FEATURE

#define SYS_DEBUG                           NOT_INCLUDE_FEATURE

#define SPWM_DUTY_GRADUAL_CHANGE            INCLUDE_FEATURE
/**********************************************************************************************************************************
 â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ€�   â–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�     â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�
â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ€� â–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�    â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�â€�â€�â€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�
â–ˆâ–ˆâ€�     â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�  â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�    â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�  â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�  â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�
â–ˆâ–ˆâ€�     â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â€�â€�â€�â€�â€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â€�  â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�    â–ˆâ–ˆâ€�â€�â€�â€�  â–ˆâ–ˆâ€�â€�â€�â€�  â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â–ˆâ–ˆâ€�â–ˆâ–ˆâ€�â€�â€�â€�
â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€� â€�â€�â€� â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�    â–ˆâ–ˆâ€�     â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�   â–ˆâ–ˆâ€�   â€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�â€�â–ˆâ–ˆâ€�  â–ˆâ–ˆâ€�â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ€�
***********************************************************************************************************************************/
#define J150_SCI_PROTOCOL_RX                INCLUDE_FEATURE
#define J150_SCI_PROTOCOL_TX                INCLUDE_FEATURE

#define ARINC429_FEATURE                    NOT_INCLUDE_FEATURE
#endif
