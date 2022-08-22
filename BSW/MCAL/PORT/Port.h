 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Hesham Elsedfy
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H
/*including a non-autosar file */
#include "Common_Macros.h"


/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*No. of Port Channels*/
#define PORT_CHANNLES_NO (43U)

/*including std_Types.h*/
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

 /* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Init API */
#define PORT_INIT_SID                                     (uint8)0x00
   
/* Service ID for PORT Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_SID                        (uint8)0x01
   
/* Service ID for PORT Refresh port Direction API */
#define PORT_REFRESH_PORT_DIRECTION_SID                   (uint8)0x02

/* Service ID for PORT GET VERSION INFO API */
#define PORT_GET_VERSION_INFO_SID                         (uint8)0x03

/* Service ID for PORT Set Pin Mode API */
#define PORT_SET_PIN_MODE_SID                             (uint8)0x04
   
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
 
/*Port_Init API service called called with wrong parameter.  */
#define PORT_E_PARAM_CONFIG             (uint8)0x0C
   
/*Invalid Port Pin ID Request */
#define PORT_E_PARAM_PIN                (uint8)0x0A
   
/*API Port_SetPinMode Service called with an invalid mode or mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE       (uint8)0x0D

/*API Port_SetPinMode Service called while mode is unchangable */
#define PORT_E_MODE_UNCHANGEABLE        (uint8)0x0E

/*Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE   (uint8)0x0B

/*API Service called without module initialization */
#define PORT_E_UNINIT                   (uint8)0x0F
   
/*APIs Called with a Null Pointer */
#define PORT_E_PARAM_POINTER            (uint8)0x10

   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModeType;

/* Type definition for Port_LevelType used by the Port APIs */
typedef uint8 Port_LevelType;

/*definition of pin Modes*/

#define PORT_PIN_MODE_DIO       (0U)
#define PORT_PIN_MODE_AF1       (1U)
#define PORT_PIN_MODE_AF2       (2U)
#define PORT_PIN_MODE_AF3       (3U)
#define PORT_PIN_MODE_AF4       (4U)
#define PORT_PIN_MODE_AF5       (5U)
#define PORT_PIN_MODE_AF6       (6U)
#define PORT_PIN_MODE_AF7       (7U)
#define PORT_PIN_MODE_AF8       (8U)
#define PORT_PIN_MODE_AF9       (9U)
#define PORT_PIN_MODE_AF10      (10U)
#define PORT_PIN_MODE_AF11      (11U)
#define PORT_PIN_MODE_AF12      (12U)
#define PORT_PIN_MODE_AF13      (13U)
#define PORT_PIN_MODE_AF14      (14U)
#define PORT_PIN_MODE_AF15      (15U)
#define PORT_PIN_MODE_ANALOG    (16U)

/************************/
/*definition of AF modes*/

#define PORT_PIN_MODE_ADC               PORT_PIN_MODE_ANALOG
#define PORT_PIN_MODE_CAN               PORT_PIN_MODE_AF8
#define PORT_PIN_MODE_CAN0_PF0_PF3      PORT_PIN_MODE_AF3
#define PORT_PIN_MODE_DIO_GPT           PORT_PIN_MODE_AF7
#define PORT_PIN_MODE_DIO_WDG           PORT_PIN_MODE_AF7               
#define PORT_PIN_MODE_M0PWM             PORT_PIN_MODE_AF4
#define PORT_PIN_MODE_M1PWM             PORT_PIN_MODE_AF5
#define PORT_PIN_MODE_SPI               PORT_PIN_MODE_AF2
#define PORT_PIN_MODE_UART              PORT_PIN_MODE_AF1
#define PORT_PIN_MODE_UART1_PC4_PC5     PORT_PIN_MODE_AF2
#define PORT_PIN_MODE_I2C               PORT_PIN_MODE_AF3
#define PORT_PIN_MODE_USB_DM_ID_VBUS_DP PORT_PIN_MODE_ANALOG
#define PORT_PIN_MODE_USB               PORT_PIN_MODE_AF8
#define PORT_PIN_MODE_NMI               PORT_PIN_MODE_AF8
/************************/


/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;


/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/*Configuration Structure for each PIN*/
typedef struct 
{
    Port_PinModeType mode;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_LevelType initial_level;
    Std_ReturnType pin_direction_changable;
    Std_ReturnType pin_mode_changeable;
}Port_ConfigType;


/*Defintion of PIN Numbers*/
/*PORTA*/
#define PORT_PIN_NO_PA0 (Port_PinType)0U 
#define PORT_PIN_NO_PA1 (Port_PinType)1U  
#define PORT_PIN_NO_PA2 (Port_PinType)2U
#define PORT_PIN_NO_PA3 (Port_PinType)3U
#define PORT_PIN_NO_PA4 (Port_PinType)4U
#define PORT_PIN_NO_PA5 (Port_PinType)5U
#define PORT_PIN_NO_PA6 (Port_PinType)6U
#define PORT_PIN_NO_PA7 (Port_PinType)7U
   /*PORTB*/
#define PORT_PIN_NO_PB0 (Port_PinType)8U
#define PORT_PIN_NO_PB1 (Port_PinType)9U
#define PORT_PIN_NO_PB2 (Port_PinType)10U
#define PORT_PIN_NO_PB3 (Port_PinType)11U
#define PORT_PIN_NO_PB4 (Port_PinType)12U
#define PORT_PIN_NO_PB5 (Port_PinType)13U
#define PORT_PIN_NO_PB6 (Port_PinType)14U
#define PORT_PIN_NO_PB7 (Port_PinType)15U
   /*PORTC*/
#define PORT_PIN_NO_PC0 (Port_PinType)16U /*PC0 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED- */
#define PORT_PIN_NO_PC1 (Port_PinType)17U /*PC1 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED- */
#define PORT_PIN_NO_PC2 (Port_PinType)18U /*PC2 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED- */
#define PORT_PIN_NO_PC3 (Port_PinType)19U /*PC3 -WARNING: JTAG PINS SHOULD NOT BE CONFIGURED- */
#define PORT_PIN_NO_PC4 (Port_PinType)20U
#define PORT_PIN_NO_PC5 (Port_PinType)21U
#define PORT_PIN_NO_PC6 (Port_PinType)22U
#define PORT_PIN_NO_PC7 (Port_PinType)23U
      /*PORTD*/
#define PORT_PIN_NO_PD0 (Port_PinType)24U
#define PORT_PIN_NO_PD1 (Port_PinType)25U
#define PORT_PIN_NO_PD2 (Port_PinType)26U
#define PORT_PIN_NO_PD3 (Port_PinType)27U
#define PORT_PIN_NO_PD4 (Port_PinType)28U
#define PORT_PIN_NO_PD5 (Port_PinType)29U
#define PORT_PIN_NO_PD6 (Port_PinType)30U
#define PORT_PIN_NO_PD7 (Port_PinType)31U /*PD7 -NMI PIN- */
      /*PORTE*/
#define PORT_PIN_NO_PE0 (Port_PinType)32U
#define PORT_PIN_NO_PE1 (Port_PinType)33U
#define PORT_PIN_NO_PE2 (Port_PinType)34U
#define PORT_PIN_NO_PE3 (Port_PinType)35U
#define PORT_PIN_NO_PE4 (Port_PinType)36U
#define PORT_PIN_NO_PE5 (Port_PinType)37U
      /*PORTF*/
#define PORT_PIN_NO_PF0 (Port_PinType)38U /*PF0 -NMI PIN-*/
#define PORT_PIN_NO_PF1 (Port_PinType)39U
#define PORT_PIN_NO_PF2 (Port_PinType)40U
#define PORT_PIN_NO_PF3 (Port_PinType)41U
#define PORT_PIN_NO_PF4 (Port_PinType)42U
   
 /*definition of PORT Numbers */
#define PORT_PORT_NO_PA (uint8)0U
#define PORT_PORT_NO_PB (uint8)1U
#define PORT_PORT_NO_PC (uint8)2U
#define PORT_PORT_NO_PD (uint8)3U
#define PORT_PORT_NO_PE (uint8)4U
#define PORT_PORT_NO_PF (uint8)5U
   

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB Array of Port_ConfigType Structures to be used by Port and other modules */
extern const Port_ConfigType Port_Config[PORT_CHANNLES_NO];

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_SetupGpioPin
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
void Port_SetupGpioPin(const Port_ConfigType *ConfigPtr );


/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module
************************************************************************************/
void Port_Init( 
 const Port_ConfigType* ConfigPtr 
);

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): PIN - Port Pin ID
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets port pin dierction
************************************************************************************/
#if PORT_SET_PIN_DIRECTION_API == STD_ON
  void Port_SetPinDirection( 
   Port_PinType Pin, 
   Port_PinDirectionType Direction 
  ); 
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes pin dierction
************************************************************************************/

void Port_RefreshPortDirection( 
 void 
); 

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): Version info
* Return value: None
* Description: Returns version info
************************************************************************************/
#if PORT_VERSION_INFO_API == STD_ON
  void Port_GetVersionInfo( 
   Std_VersionInfoType* versioninfo 
  );
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): PIN - Port Pin ID
*                  Mode - New Port Pin mode to be set on Port Pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode
************************************************************************************/
#if PORT_SET_PIN_MODE_API == STD_ON
  void Port_SetPinMode( 
   Port_PinType Pin, 
   Port_PinModeType Mode 
  );
#endif
  
#endif /* PORT_H */
