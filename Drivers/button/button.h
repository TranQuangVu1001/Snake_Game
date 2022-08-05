/**
 * @file       button.h
 * @version    0.0.1
 * @date       2022-08-01
 * @author     Vu Tran
 */
/* Define --------------------------------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H
#ifdef __cplusplus
extern "C"
{
#endif
/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
/*******************************************************************************
 *  TYPEDEFS
 ******************************************************************************/
/* Public typedef enum  ----------------------------------------------- */
/**
 * @brief <state button>
 */
typedef enum
{
	BUTTON_STATE_ACTIVE = 1,
	BUTTON_STATE_DEACTIVE = 0
}
button_state_t;
/* Public enum  ----------------------------------------- */
/**
 * @brief <state press button>
 */
/* typedef ------------------------------------------------------------*/
typedef enum
{
	BUTTON_EVT_NON,
	BUTTON_EVT_CLICK,
	BUTTON_EVT_HOLD
}
button_evt_t;
/* Public typedef stryct  ----------------------------------------------- */
/**
 * @brief <button>
 */
typedef struct
{
	GPIO_TypeDef *button_port;
	uint16_t button_pin;
	button_state_t state;
	button_evt_t event;
}
button_name_t;

/* Private variables ----------------------------------------------------*/

/*******************************************************************************
 * FUNCTIONS - API
 *******************************************************************************/
/*!
 *******************************************************************************
 * @fn      void button_init(button_name_t *button, GPIO_TypeDef *gpio_x, uint16_t gpio_pin);
 *
 * @brief   Init information of Button
 *
 * @param   button  	- Handle of Button
 * @param   GPIOx  		- Button GPIO PORT
 * @param   GPIO_Pin  	- Button GPIO PIN
 *
 ******************************************************************************/
void button_init(button_name_t *button, GPIO_TypeDef *gpio_x, uint16_t gpio_pin);
/*!
 *******************************************************************************
 * @fn      void configure_button_pins(button_name_t *button_name, int priority_exti);
 *
 * @brief   Init information of Button
 *
 * @param   button  			- Handle of Button
 * @param   priority_EXTI  		- The priority of interupt
 *
 ******************************************************************************/
void configure_button_pins(button_name_t *button_name, int priority_exti);
/*!
 *******************************************************************************
 * @fn      button_get_state(button_name_t *button);
 *
 * @brief   Read status of Button
 *
 * @param   button  - Handle of Button
 *
 * @return  current state of Button
 ******************************************************************************/
void button_get_state(button_name_t *button);
/*!
 *******************************************************************************
 * @fn      button_name_t  get_event_from_sys_button(button_name_t *button, uint32_t start_time_press);
 *
 * @brief   Get event handle of button
 *
 * @param   button  			- Handle of Button
 * @param   start_time_press 	- Time get to check event
 *
 * @return  BUTTON_STATUS_OK
 * @return  BUTTON_STATUS_ERROR
 ******************************************************************************/
void get_event_from_sys_button(button_name_t *button, uint32_t start_time_press);
#ifdef __cplusplus
}
#endif
#endif // __BUTTON_H
/* End of file -------------------------------------------------------- */
