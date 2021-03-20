#ifndef PROD_H_
#define PROD_H_


#include "prod_defs.h"

/********************************************************************/
/* Platform feature Defines here */
#define PF_ADC                              INCLUDE_FEATURE
#define PF_GPIO                             INCLUDE_FEATURE
#define PF_ISR                              INCLUDE_FEATURE
#define PF_PWM                              INCLUDE_FEATURE
#define PF_SPI                              INCLUDE_FEATURE
#define PF_TIMER                            INCLUDE_FEATURE
#define PF_SCI                              INCLUDE_FEATURE
#define PF_XINTF                            INCLUDE_FEATURE
#define PF_FLASH                            INCLUDE_FEATURE
#define PF_ECAP								INCLUDE_FEATURE

#define PF_PWM_1A							INCLUDE_FEATURE
#define PF_PWM_1B							INCLUDE_FEATURE
#define PF_PWM_2A							INCLUDE_FEATURE
#define PF_PWM_2B							INCLUDE_FEATURE
#define PF_PWM_3A							INCLUDE_FEATURE
#define PF_PWM_3B							INCLUDE_FEATURE
#define PF_PWM_4A							EXCLUDE_FEATURE
#define PF_PWM_4B							EXCLUDE_FEATURE
#define PF_PWM_5A							EXCLUDE_FEATURE
#define PF_PWM_5B							EXCLUDE_FEATURE
#define PF_PWM_6A							EXCLUDE_FEATURE
#define PF_PWM_6B							EXCLUDE_FEATURE

#define PF_PWM_RVDT							EXCLUDE_FEATURE
#define PF_PWM_ECAP							INCLUDE_FEATURE

/********************************************************************/
/* Customre specific feature defines here */
#define SYS_DEBUG                           EXCLUDE_FEATURE

#define SPWM_DUTY_GRADUAL_CHANGE            INCLUDE_FEATURE
#define J150_SCI_PROTOCOL_RX                INCLUDE_FEATURE
#define J150_SCI_PROTOCOL_TX                INCLUDE_FEATURE
#define ARINC429_FEATURE                    EXCLUDE_FEATURE

/* If include AB_OTA_ENABLE_DEFAULT_FEATURE
 * No protocal switch to support AB OTA function by default
 */
#define AB_OTA_ENABLE_DEFAULT_FEATURE       INCLUDE_FEATURE

/* System reboot automatically after received the update FW image
 * If you want to reboot the system by yourself, please exclude this feature
 */
#define SYSTEM_REBOOT_AUTO_FEATURE          INCLUDE_FEATURE

#endif
