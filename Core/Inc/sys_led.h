/**
 * @file       sys_led.h
 * @version    0.0.1
 * @date       2022-08-02
 * @author     Vu Tran
 */
/*************************************************************************/
/* Private include ------------------------------------------------------------*/
#include "../../Drivers/led/led.h"
#ifndef INC_SYS_LED_H_
#define INC_SYS_LED_H_
/* Public function prototypes ----------------------------------------- */

/*!
 *******************************************************************************
 * @fn     void sys_led_init();
 *
 * @brief   Initialize system button, get port and led
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void sys_led_init();
/*!
 *******************************************************************************
 * @fn     void sys_led_config();
 *
 * @brief   Configuration system port and pin led
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void sys_led_config();
/*!
 *******************************************************************************
 * @fn     void led_start_game();
 *
 * @brief   The function blink led when program start
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void led_start_game();
/*!
 *******************************************************************************
 * @fn     void set_off_leds();
 *
 * @brief   The function set all led turn on
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void set_off_leds();
/*!
 *******************************************************************************
 * @fn     void set_on_leds();
 *
 * @brief   The function set all led turn off
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void set_on_leds();
/*!
 *******************************************************************************
 * @fn     void set_toggle_all_leds();
 *
 * @brief   The function set all led toggle
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void set_toggle_all_leds();
#endif /* INC_SYS_BUTTON_H_ */
