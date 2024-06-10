/*****************************************************************************
 * File Name: task_test.c
 *
 * Version 1.00
 *
 * Author: Ip_v1
 *
 * Description:
 *   Add a description like ... This file contains the code to
 *
 *****************************************************************************/

/******************************************************************************
 * Included headers
 ******************************************************************************/
#include "task_test.h"
#include "app_threadx.h"
#include "main.h"

#ifndef THREAD_STACK_SIZE
#define THREAD_STACK_SIZE 1024
#endif

/*****************************************************************************
 *   Extern Global Variables
 ******************************************************************************/
extern uint8_t flag;
extern UART_HandleTypeDef hlpuart1;

/*****************************************************************************
 *   Global Variables
 ******************************************************************************/
TX_THREAD tx_btn_thread;
uint8_t thread_stack_btn_task[THREAD_STACK_SIZE];
volatile uint8_t f_uart_interrupt;
uint8_t buf[10];

/******************************************************************************
 *   Function Code
 ******************************************************************************/

/**
 * Function to create a new thread for reading a button
 */
UINT tx_create_thread_btn(void)
{
	if ( tx_thread_create(&tx_btn_thread,
			"tx_btn_thread",
			tx_btn_thread_entry,
			0,
			thread_stack_btn_task,
			THREAD_STACK_SIZE,
			10,
			10,
			1,
			TX_APP_THREAD_AUTO_START ) != TX_SUCCESS) {
		return TX_THREAD_ERROR;
	} else {
		return 0;
	}

}

/**
 * ThreadX thread function to poll GPIO on an STM32
 *
 */
VOID tx_btn_thread_entry(ULONG thread_input)
{
	while (1) {
		HAL_UART_Receive_IT(&hlpuart1, buf, 1);
		/*
		ATOMIC_SET_BIT(hlpuart1.Instance->CR1, USART_CR1_RXNEIE_RXFNEIE);
		*/
		tx_thread_sleep(1);
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1) {
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
			tx_thread_sleep(10);
		}
	}
}

/**
 * Callback function for USART
 */
void tx_uart_interrupt_callback(void)
{
	f_uart_interrupt = 1;
	HAL_UART_Receive_IT(&hlpuart1, buf, 1);
	/*
	ATOMIC_CLEAR_BIT(hlpuart1.Instance->CR1, (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE));
	ATOMIC_CLEAR_BIT(hlpuart1.Instance->CR1, USART_CR1_RTOIE);
	ATOMIC_CLEAR_BIT(hlpuart1.Instance->CR1, USART_CR1_IDLEIE);
	__HAL_UART_SEND_REQ(&hlpuart1, UART_RXDATA_FLUSH_REQUEST);
	*/
	if (flag == 0)
		flag = 1;
	else
		flag = 0;
}
