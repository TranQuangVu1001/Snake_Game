/**
 * @file       sys_button.h
 * @version    0.0.1
 * @date       2022-08-01
 * @author     Vu Tran
 */
/*************************************************************************/
/* Private include ------------------------------------------------------------*/
#include "sys_ssd1306.h"
#include "button.h"

#ifndef INC_SYS_BUTTON_H_
#define INC_SYS_BUTTON_H_
/* Public function prototypes ----------------------------------------- */
/*!
 *******************************************************************************
 * @fn     void button_get_event(button_t *button, uint32_t start_time_press_button);
 *
 * @brief   Get event handle of button
 *
 * @param   button  			- Handle of Button
 * @param   start_time_press 	- Time get to check event
 *
 * @return  BUTTON_STATUS_OK
 * @return  BUTTON_STATUS_ERROR
 ******************************************************************************/
void button_get_event(button_name_t *button, uint32_t start_time_press);
/*!
 *******************************************************************************
 * @fn     void button_handle_start();
 *
 * @brief   Handle when press button start program
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL 
 ******************************************************************************/
void button_handle_start();
/*!
 *******************************************************************************
 * @fn     void sys_button_init();
 *
 * @brief   Initialize system button, get port and pin
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void sys_button_init();
/*!
 *******************************************************************************
 * @fn     void sys_button_config();
 *
 * @brief   Configuration system port and pin button
 *
 * @param   NULL  			- NULL
 *
 * @return  NULL
 ******************************************************************************/
void sys_button_config();
#endif /* INC_SYS_BUTTON_H_ */
