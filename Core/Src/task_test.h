/*****************************************************************************
* File Name: task_test.h
*
* Version 1.00
*
* Author: Ip_v1
* 
* Description:
*   Add a description like ... This file contains the code to 
*   
*****************************************************************************/

#ifndef TASK_TEST_H_
#define TASK_TEST_H_

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Included Headers
******************************************************************************/
#include "app_threadx.h"
#include "main.h"

/******************************************************************************
* Defines : Key Assignment Constants
*****************************************************************************/ 
    
/*****************************************************************************
*   Function Prototypes
*****************************************************************************/

VOID tx_btn_thread_entry(ULONG thread_input);
UINT tx_create_thread_btn(void);
void tx_uart_interrupt_callback(void);

#ifdef __cplusplus
}
#endif

#endif /* TASK_TEST_H_ */

/****************************End of File*************************************/
