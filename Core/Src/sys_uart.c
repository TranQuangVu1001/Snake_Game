/**
 * @file       sys_uart.c
 * @version    0.0.1
 * @date       2022-08-01
 * @author     Vu Tran
 */
/*************************************************************************/

/* Private include ------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
uint8_t tx_bufferf[] = "PROJECT SNAKE GAME ON STM32\n"; // Message transmit when the program begin
char rx_buffer[20];                                     // Array receive uart
char rx_data;                                           // Data receive uart
uint8_t rx_flag = 0;                                    // Receive uart flag check interupt
uint8_t tx_flag = 0;                                    // Transmit uart flag check interupt
/*subfunction ----------------------------------------------------------------*/
/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
void SYS_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
  return ch;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  // Check carriage return character "<CR>" or "space" to signal the finish of data receiving//
  if (rx_data != 13)
  {
    rx_buffer[rx_flag++] = rx_data; // Transfer data to buffer.
  }
  else if (rx_data == 13)
  {
    rx_flag = 0; // reset receive flag check.
    tx_flag = 1; // turn on transmit flag check.
  }
  HAL_UART_Receive_IT(&huart2,(uint8_t *)&rx_data, 1);
}

void menu_option_for_uart()
{
  printf("====================SNAKE GAME==================\n");
  printf("1. Start game... \n");
  printf("x. Exit game \n");
  printf("Type your option here : \n");
  printf("================================================\n");
}
void transmit_message_begin()
{
    HAL_UART_Transmit(&huart2, tx_bufferf, sizeof(tx_bufferf), 100); // Transmit the message when the program begin
}
/* End of file -------------------------------------------------------- */
