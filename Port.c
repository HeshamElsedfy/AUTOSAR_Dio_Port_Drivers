 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Hesham Elsedfy
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/**********************************************************************************************************/
/*NOTE: The Macro Like Function REG_WITH_OFFSET(BASE_ADRESS,OFFSET) is defined in the Common_Macros.h file*/
/**********************************************************************************************************/
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
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

void Port_Init( 
 const Port_ConfigType* ConfigPtr 
)
{
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
          /* check if the input configuration pointer is not a NULL_PTR */
          if (NULL_PTR == ConfigPtr)
          {
                  Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                       PORT_E_PARAM_CONFIG);
          }
          else
  #endif
          {
            volatile uint32 * PortGpio_Ptr = NULL_PTR; /* pointer to the required Port Registers base address */
            volatile uint32 delay = 0;
            uint8 PinNo=0;
            /* Enable clock for ALL ports and allow time for clock to start*/
            SYSCTL_REGCGC2_REG |= SYSCTL_REGCGC2_PORT_CLOCK_MASK;
            delay = SYSCTL_REGCGC2_REG;
            
            
            for(Port_PinType index=0;index<PORT_CHANNLES_NO;index++)
            {
              /*Assign the base address of the Port to PortGpio_Ptr*/
              if((index>=PORT_PIN_NO_PA0) && (index <= PORT_PIN_NO_PA7))
              {
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                PinNo=index-PORT_PIN_NO_PA0;
              }
              else if((index>=PORT_PIN_NO_PB0) && (index <= PORT_PIN_NO_PB7))
              {
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                PinNo=index-PORT_PIN_NO_PB0;
              }
              else if((index>=PORT_PIN_NO_PC0) && (index <= PORT_PIN_NO_PC7))
              {
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                PinNo=index-PORT_PIN_NO_PC0;
              }
              else if((index>=PORT_PIN_NO_PD0) && (index <= PORT_PIN_NO_PD7))
              {
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                PinNo=index-PORT_PIN_NO_PD0;
              }
              else if((index>=PORT_PIN_NO_PE0) && (index <= PORT_PIN_NO_PE5))
              {
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                PinNo=index-PORT_PIN_NO_PE0;
              }
              else if((index>=PORT_PIN_NO_PF0) && index <= (PORT_PIN_NO_PF4))
              {
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                PinNo=index-PORT_PIN_NO_PF0;
              }
              else
              {
              /*report invalid pin id to DET*/
              #if (PORT_DEV_ERROR_DETECT == STD_ON)
                        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                        PORT_E_PARAM_PIN);
              #endif
              }
              /*Unlocking commit register only for PD7 And PF0*/

              if((index == PORT_PIN_NO_PD7) || (index == PORT_PIN_NO_PF0)) /* PD7 or PF0 */
              {
                  REG_WITH_OFFSET(PortGpio_Ptr,PORT_LOCK_REG_OFFSET) = PORT_GPIOLOCK_KEY;                     /* Unlock the GPIOCR register */   
                  SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_COMMIT_REG_OFFSET) , PinNo);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
              }
              else if((index >= PORT_PIN_NO_PC0) && (index <= PORT_PIN_NO_PC3)) /* PC0 to PC3 */
              {
                  /* Do Nothing ...  these are the JTAG pins */
              }
              else
              {
                  /* Do Nothing ... No need to unlock the commit register for this pin */
              }
              /*Set Analog Mode Select Value*/
              CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNo);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
              CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ALT_FUNC_REG_OFFSET) , PinNo);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
              
              /*  if the direction of the pin is output*/
              if(PORT_PIN_OUT == ConfigPtr[index].direction )
              {
                  SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIR_REG_OFFSET), PinNo);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                  
                  if(STD_HIGH == ConfigPtr[index].initial_level)
                  {
                      SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DATA_REG_OFFSET) , PinNo);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                  }
                  else
                  {
                      CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DATA_REG_OFFSET) , PinNo);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                  }
              }
              /*  if the direction of the pin is input*/
              else if(PORT_PIN_IN == ConfigPtr[index].direction )
              {
                  CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIR_REG_OFFSET) , PinNo);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                  
                  if(PULL_UP == ConfigPtr[index].resistor )
                  {
                      SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_UP_REG_OFFSET) , PinNo);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                  }
                  else if(PULL_DOWN == ConfigPtr[index].resistor )
                  {
                      SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_DOWN_REG_OFFSET) , PinNo);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                  }
                  else
                  {
                      CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_UP_REG_OFFSET) , PinNo);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                      CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_DOWN_REG_OFFSET) , PinNo);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                  }
              }
              else
              {
              /*Do nothing*/
              }
              
              /*in case pin is not configred as a gpio pin*/
              if(PORT_PIN_MODE_DIO != ConfigPtr[index].mode)
              {
                SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ALT_FUNC_REG_OFFSET) , PinNo);             /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                /*in case pin is configred as an analog Alternate Function pin*/
                if(PORT_PIN_MODE_ANALOG == ConfigPtr[index].mode)
                {
                  SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNo);      /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
                }
                /*in case pin is configred as a digital Aletrnate function pin*/
                else if(((ConfigPtr[index].mode)<=PORT_PIN_MODE_AF15)&&((ConfigPtr[index].mode)>=PORT_PIN_MODE_AF1))
                {
                  SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIGITAL_ENABLE_REG_OFFSET) , PinNo);         /*Set Corresponding bit in GPIODEN to enable digital functionality on this pin*/
                  REG_WITH_OFFSET(PortGpio_Ptr,PORT_CTL_REG_OFFSET)|=((ConfigPtr[index].mode)<<((PinNo+1)*AF_SIZE));
                }
                else
                {
                  /*report invalid Mode Error to Det Module*/
                  #if (PORT_DEV_ERROR_DETECT == STD_ON)
                    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                    PORT_E_PARAM_INVALID_MODE);
                  #endif
                }
              }
              else
              {
                SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIGITAL_ENABLE_REG_OFFSET) , PinNo);         /*Set Corresponding bit in GPIODEN to enable digital functionality on this pin*/
              }
            }
          }
    Port_Status=PORT_INITIALIZED;      
}

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
     )
  {
    uint8 PinNo=0;
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    if(PORT_INITIALIZED==Port_Status){ 
      if((Pin>=PORT_PIN_NO_PA0) && (Pin <= PORT_PIN_NO_PA7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        PinNo=Pin-PORT_PIN_NO_PA0;
      }
      else if((Pin>=PORT_PIN_NO_PB0) && (Pin <= PORT_PIN_NO_PB7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        PinNo=Pin-PORT_PIN_NO_PB0;
      }
      else if((Pin>=PORT_PIN_NO_PC0) && (Pin <= PORT_PIN_NO_PC7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        PinNo=Pin-PORT_PIN_NO_PC0;
      }
      else if((Pin>=PORT_PIN_NO_PD0) && (Pin <= PORT_PIN_NO_PD7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        PinNo=Pin-PORT_PIN_NO_PD0;
      }
      else if((Pin>=PORT_PIN_NO_PE0) && (Pin <= PORT_PIN_NO_PE5))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        PinNo=Pin-PORT_PIN_NO_PE0;
      }
      else if((Pin>=PORT_PIN_NO_PF0) && Pin <= (PORT_PIN_NO_PF4))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        PinNo=Pin-PORT_PIN_NO_PF0;
      }
      else
      {
      /*report invalid pin id to DET*/
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                PORT_E_PARAM_PIN);
      #endif
      }
      if(STD_ON==Port_Config[Pin].pin_direction_changable)
      {
        if(PORT_PIN_OUT==Direction)
        {
          SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIR_REG_OFFSET),PinNo);
        }
        else if(PORT_PIN_IN==Direction)
        {
          CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIR_REG_OFFSET),PinNo);
        }
      }
      else
      {
      /*Port Pin Not Configured As Changeable*/
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                PORT_E_DIRECTION_UNCHANGEABLE);
      #endif
      }
    }
    else{
      /*Port Is not Initialized*/
       #if (PORT_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                PORT_E_UNINIT);
      #endif
    }
  }
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
)
{
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(PORT_NOT_INITIALIZED==Port_Status)
    {
               Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID,
               PORT_E_UNINIT);
    }
  #endif
  uint8 PinNo=0;
  volatile uint32 * PortGpio_Ptr = NULL_PTR;
  for(uint8 index=0;index<PORT_CHANNLES_NO;index++)
  {
    if(STD_OFF==Port_Config[index].pin_direction_changable){/*Check if PIN Direction is changeable*/
      if((index>=PORT_PIN_NO_PA0) && (index <= PORT_PIN_NO_PA7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        PinNo=index-PORT_PIN_NO_PA0;
      }
      else if((index>=PORT_PIN_NO_PB0) && (index <= PORT_PIN_NO_PB7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        PinNo=index-PORT_PIN_NO_PB0;
      }
      else if((index>=PORT_PIN_NO_PC0) && (index <= PORT_PIN_NO_PC7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        PinNo=index-PORT_PIN_NO_PC0;
      }
      else if((index>=PORT_PIN_NO_PD0) && (index <= PORT_PIN_NO_PD7))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        PinNo=index-PORT_PIN_NO_PD0;
      }
      else if((index>=PORT_PIN_NO_PE0) && (index <= PORT_PIN_NO_PE5))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        PinNo=index-PORT_PIN_NO_PE0;
      }
      else if((index>=PORT_PIN_NO_PF0) && index <= (PORT_PIN_NO_PF4))
      {
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        PinNo=index-PORT_PIN_NO_PF0;
      }
      else
      {
      /*report invalid pin id to DET*/
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID,
                PORT_E_PARAM_PIN);
      #endif
      }

      /*  if the direction of the pin is output*/
      if(PORT_PIN_OUT == Port_Config[index].direction )
      {
          SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIR_REG_OFFSET), PinNo);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
          
          if(STD_HIGH == Port_Config[index].initial_level)
          {
              SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DATA_REG_OFFSET) , PinNo);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
          }
          else
          {
              CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DATA_REG_OFFSET) , PinNo);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
          }
      }
      /*  if the direction of the pin is input*/
      else if(PORT_PIN_IN == Port_Config[index].direction )
      {
          CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIR_REG_OFFSET) , PinNo);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
          
          if(PULL_UP == Port_Config[index].resistor )
          {
              SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_UP_REG_OFFSET) , PinNo);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
          }
          else if(PULL_DOWN == Port_Config[index].resistor )
          {
              SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_DOWN_REG_OFFSET) , PinNo);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
          }
          else
          {
              CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_UP_REG_OFFSET) , PinNo);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
              CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_PULL_DOWN_REG_OFFSET) , PinNo);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
          }
      }
      else
      {
      /*Do nothing*/
      }
    }
    else
    {
    /*Do nothing - This Pin Direction is Changeable */
    }
  }
}

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
  )
  {
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
            /* Report  Null Pointer Error to DET Module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                            PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
  #endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
            /* Copy the vendor Id */
            versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
            /* Copy the module Id */
            versioninfo->moduleID = (uint16)PORT_MODULE_ID;
            /* Copy Software Major Version */
            versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
            /* Copy Software Minor Version */
            versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
            /* Copy Software Patch Version */
            versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
  }
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
     )
  {
   #if (PORT_DEV_ERROR_DETECT == STD_ON)
      if(PORT_NOT_INITIALIZED==Port_Status)
      {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                 PORT_E_UNINIT);
      }
      else
  #endif
      {
       /*Do nothing*/
      }
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
      if(STD_OFF==Port_Config[Pin].pin_mode_changeable)
      {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                 PORT_E_MODE_UNCHANGEABLE);
      }
      else
  #endif
      {
      /*Do Nothing*/
      }
    uint8 PinNo=0;
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    if((Pin>=PORT_PIN_NO_PA0) && (Pin <= PORT_PIN_NO_PA7))
    {
      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
      PinNo=Pin-PORT_PIN_NO_PA0;
    }
    else if((Pin>=PORT_PIN_NO_PB0) && (Pin <= PORT_PIN_NO_PB7))
    {
      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
      PinNo=Pin-PORT_PIN_NO_PB0;
    }
    else if((Pin>=PORT_PIN_NO_PC0) && (Pin <= PORT_PIN_NO_PC7))
    {
      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
      PinNo=Pin-PORT_PIN_NO_PC0;
    }
    else if((Pin>=PORT_PIN_NO_PD0) && (Pin <= PORT_PIN_NO_PD7))
    {
      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
      PinNo=Pin-PORT_PIN_NO_PD0;
    }
    else if((Pin>=PORT_PIN_NO_PE0) && (Pin <= PORT_PIN_NO_PE5))
    {
      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
      PinNo=Pin-PORT_PIN_NO_PE0;
    }
    else if((Pin>=PORT_PIN_NO_PF0) && (Pin <= PORT_PIN_NO_PF4))
    {
      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
      PinNo=Pin-PORT_PIN_NO_PF0;
    }
    else
    {
    /*report invalid pin ID to DET*/
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
              PORT_E_PARAM_PIN);
    #endif
    }

    if(PORT_PIN_MODE_DIO != Mode)
        {
          SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ALT_FUNC_REG_OFFSET) , PinNo);             /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
          /*in case pin is configred as an analog Alternate Function pin*/
          if(PORT_PIN_MODE_ANALOG == Mode)
          {
            SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNo);      /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
          }
          /*in case pin is configred as a digital Aletrnate function pin*/
          else if((Mode<=PORT_PIN_MODE_AF15)&&(Mode>=PORT_PIN_MODE_AF1))
          {
            
            CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNo);   /* Clear the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
            SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIGITAL_ENABLE_REG_OFFSET) , PinNo);      /* Setting the corresponding bit in the GPIODEN register to Enable Digital functionality on this pin */
            REG_WITH_OFFSET(PortGpio_Ptr,PORT_CTL_REG_OFFSET)|=(Mode<<((PinNo+1)*AF_SIZE));
          }
          else
          {
            /*report invalid Mode Error to Det Module*/
            #if (PORT_DEV_ERROR_DETECT == STD_ON)
              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
              PORT_E_PARAM_INVALID_MODE);
            #endif
          }
        }
    else
    {
    CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ALT_FUNC_REG_OFFSET) , PinNo);          /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    CLEAR_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNo);   /* Clear the corresponding bit in the GPIOAMSEL register to Disable analog functionality on this pin */
    SET_BIT(REG_WITH_OFFSET(PortGpio_Ptr,PORT_DIGITAL_ENABLE_REG_OFFSET) , PinNo);      /* Setting the corresponding bit in the GPIODEN register to Enable Digital functionality on this pin */
    }
#endif
  }