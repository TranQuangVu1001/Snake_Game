/**
 * @file       sys_ssd1306.h
 * @version    0.0.1
 * @date       2022-08-02
 * @author     Vu Tran
 */
/*************************************************************************/
/* Define ------------------------------------------------------------*/
#ifndef INC_SYS_SSD1306_H_
#define INC_SYS_SSD1306_H_
#ifdef __cplusplus
extern "C"
{
#endif
/* Private include -------------------------------------------------------*/
#include "ssd1306.h"
#include "sys_led.h"
#include "stdio.h"
#include "sys_uart.h"
#include "snake.h"
#include "ttp229.h"
/* Public function prototypes ----------------------------------------- */
/*!
 *******************************************************************************
 * @fn      void display_menu_on_oled(void);
 *
 * @brief   The fuction display menu on oled
 *
 * @param   NULL
 * @return 	NULL
 * @return  NULL
 ******************************************************************************/
void display_menu_on_oled(void);
/*!
 *******************************************************************************
 * @fn      void ssd1306_test_circles(uint8_t radius, uint16_t color);
 *
 * @brief   The fuction draw circles
 *
 * @param   uint8_t radius
 * @param	uint16_t color
 * @return 	NULL
 * @return  NULL
 ******************************************************************************/
void ssd1306_draw_circles(uint8_t radius, uint16_t color);
/*!
 *******************************************************************************
 * @fn      void start_game(void);
 *
 * @brief   The fuction start game display on lcd
 *
 * @param   NULL
 * @return 	NULL
 * @return  NULL
 ******************************************************************************/
void start_game(void);
#ifdef __cplusplus
}
#endif
#endif /* INC_SYS_SSD1306_H_ */
