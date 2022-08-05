/**
 * @file       sys_uart.h
 * @version    0.0.1
 * @date       2022-08-02
 * @author     Vu Tran
 */
/*************************************************************************/
/* Private include ------------------------------------------------------------*/
#include "main.h"
#ifndef INC_SYS_UART_H_
#define INC_SYS_UART_H_
/* Public function prototypes ----------------------------------------- */

void SYS_USART2_UART_Init();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void menu_option_for_uart();

void transmit_message_begin();

#endif /* INC_SYS_BUTTON_H_ */
