 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.c
 *
 * Description:  Det stores the development errors reported by other modules.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Det.h"
uint8 Module_Id=0;
uint8 Instance_Id=0;
uint8 Api_Id=0;
uint8 Error_Id=0;
Std_ReturnType Det_ReportError( uint16 ModuleId,
                      uint8 InstanceId,
                      uint8 ApiId,
                      uint8 ErrorId )
{
    /*Assign error Report Parameters to Global Variables To be Able to Watch it in the Debugger*/
    Module_Id=ModuleId;
    Instance_Id=InstanceId;
    Api_Id=ApiId;
    Error_Id=ErrorId;
    while(1)
    {

    }
    return E_OK;
}

