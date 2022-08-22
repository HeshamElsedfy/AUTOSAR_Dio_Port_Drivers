 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Hesham Elsedfy
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_PBcfg.c does not match the expected version"
#endif
 
const Port_ConfigType Port_Config[PORT_CHANNLES_NO]={
                                                        /*PORT A*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA0*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA1*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA2*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA3*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA4*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA5*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA6*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PA7*/
                                                        /*PORT B*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB0*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB1*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB2*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB3*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB4*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB5*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB6*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PB7*/
                                                        /*PORT C*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC0 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED !!!*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC1 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED !!!*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC2 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED !!!*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC3 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED !!!*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC4*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC5*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC6*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PC7*/
                                                        /*PORT D*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD0*/ 
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD1*/ 
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD2*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD3*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD4*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD5*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD6*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PD7 -NMI PIN-*/
                                                        /*PORT E*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PE0*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PE1*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PE2*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PE3*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PE4*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PE5*/
                                                        /*PORT F*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PF0 -NMI PIN- */
                                                        PORT_CONFIG_CHANNEL_LED1   ,/*PF1*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PF2*/
                                                        PORT_CONFIG_CHANNEL_DEFAULT,/*PF3*/
                                                        PORT_CONFIG_CHANNEL_SW1     /*PF4*/
                                                      
};
