 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Hesham Elsedfy
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H
/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)
/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)
   
/* Pre-compile option for Port Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-compile option for Port Set Pin Mode API */
#define PORT_SET_PIN_MODE_API                (STD_ON)

  
   
/* PORT Configured PIN ID's  */
#define PORT_CONF_LED1_PIN_NUM                PORT_PIN_NO_PF1
#define PORT_CONF_SW1_PIN_NUM                 PORT_PIN_NO_PF4

/* PORT Configured PORT ID's  */
#define PORT_CONF_LED1_PORT_NUM                PORT_PORT_NO_PF
#define PORT_CONF_SW1_PORT_NUM                 PORT_PORT_NO_PF

      /*PIN configurations 
   * mode;
   *direction;
   *resistor;
   *initial_level;
   *pin_direction_changable;
   *pin_mode_changeable;
   */
   
/*Default PORT Channel Pre-compiled configurations*/
   
#define PORT_CONF_DEFAULT_MODE                      PORT_PIN_MODE_DIO
#define PORT_CONF_DEFAULT_DIRECTION                 PORT_PIN_IN
#define PORT_CONF_DEFAULT_RESISTOR                  OFF
#define PORT_CONF_DEFAULT_INITIAL_LEVEL             STD_LOW
#define PORT_CONF_DEFAULT_DIRECTION_CHANGABLE       STD_ON
#define PORT_CONF_DEFAULT_MODE_CHANGEABLE           STD_ON
   
/*Pre-compiled configurations for LED1*/
   
#define PORT_CONF_LED1_MODE                      PORT_PIN_MODE_DIO
#define PORT_CONF_LED1_DIRECTION                 PORT_PIN_OUT
#define PORT_CONF_LED1_RESISTOR                  OFF
#define PORT_CONF_LED1_INITIAL_LEVEL             STD_LOW
#define PORT_CONF_LED1_DIRECTION_CHANGABLE       STD_ON
#define PORT_CONF_LED1_MODE_CHANGEABLE           STD_ON
   
/*Pre-compiled configurations for SW1*/
   
#define PORT_CONF_SW1_MODE                      PORT_PIN_MODE_DIO
#define PORT_CONF_SW1_DIRECTION                 PORT_PIN_IN
#define PORT_CONF_SW1_RESISTOR                  PULL_UP
#define PORT_CONF_SW1_INITIAL_LEVEL             STD_HIGH
#define PORT_CONF_SW1_DIRECTION_CHANGABLE       STD_ON
#define PORT_CONF_SW1_MODE_CHANGEABLE           STD_ON
   
/*Configuration Structures of Configured pins */
/*port_ConfigChannel default structure*/
#define PORT_CONFIG_CHANNEL_DEFAULT {\
                                                        PORT_CONF_DEFAULT_MODE,\
                                                        PORT_CONF_DEFAULT_DIRECTION,\
                                                        PORT_CONF_DEFAULT_RESISTOR,\
                                                        PORT_CONF_DEFAULT_INITIAL_LEVEL,\
                                                        PORT_CONF_DEFAULT_DIRECTION_CHANGABLE,\
                                                        PORT_CONF_DEFAULT_MODE_CHANGEABLE\
                                                        }


/*LED PIN Configurations structure*/
#define PORT_CONFIG_CHANNEL_LED1 {\
                                                        PORT_CONF_LED1_MODE,\
                                                        PORT_CONF_LED1_DIRECTION,\
                                                        PORT_CONF_LED1_RESISTOR,\
                                                        PORT_CONF_LED1_INITIAL_LEVEL,\
                                                        PORT_CONF_LED1_DIRECTION_CHANGABLE,\
                                                        PORT_CONF_LED1_MODE_CHANGEABLE\
                                                        }


/*Button PIN Configurations structure*/
#define PORT_CONFIG_CHANNEL_SW1 { \
                                                        PORT_CONF_SW1_MODE,\
                                                        PORT_CONF_SW1_DIRECTION,\
                                                        PORT_CONF_SW1_RESISTOR,\
                                                        PORT_CONF_SW1_INITIAL_LEVEL,\
                                                        PORT_CONF_SW1_DIRECTION_CHANGABLE,\
                                                        PORT_CONF_SW1_MODE_CHANGEABLE\
                                                        }             
   
#endif /*PORT_CFG_H*/