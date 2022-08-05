/**
 * @file       led.c
 * @version    0.0.1
 * @date       2022-08-1
 * @author     Vu Tran
 */
/*************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "led.h"
/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <Control led>
 *
 * @param[in]     <GPIOx, GPIO_Pin>
 * @param[out]    <SetPin led>
 *
 * @attention  <HAL_GPIO>
 *
 * @return
 *  - 0: //write low
 *  - 1: //write high
 */
/*******************************************************************************
 * FUNCTIONS - API
 ******************************************************************************/
/*!
 *******************************************************************************
 * @fn      led_status_t init_led(led_init_t *led, GPIO_Type *GPIO_Port, uint16_t GPIO_Pin);
 *
 * @brief   Init info for LED
 *
 * @param   led            - handle for led
 * @param   gpio_port      - Led gpio_port
 * @param   gpio_pin       - Led gpio_pin
 *
 * @return  LED_STATUS_OK
 * @return  LED_STATUS_ERROR_OPTION
 * @return  LED_STATUS_ERROR_NULL_PTR
 ******************************************************************************/
led_status_t led_init(led_t *led, gpio_type_t *gpio_port, uint16_t gpio_pin) // Init led
{
	assert_param(led != NULL && gpio_port != NULL && gpio_pin != NULL);
	led->gpio_port = gpio_port;
	led->gpio_pin = gpio_pin;
	return LED_STATUS_OK;
}
/*!
 *******************************************************************************
 * @fn      led_status_t configure_led_pins(led_t *led);
 *
 * @brief   The configuration pin led depend on HAL_GPIO API
 *
 * @param   led            - handle for led
 *
 * @return  LED_STATUS_OK
 * @return  LED_STATUS_ERROR_OPTION
 * @return  LED_STATUS_ERROR_NULL_PTR
 ******************************************************************************/
led_status_t configure_led_pins(led_t *led)
{
	assert_param(led != NULL);
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	GPIO_InitTypeDef myLEDConfig;
	myLEDConfig.Mode = GPIO_MODE_OUTPUT_PP;
	myLEDConfig.Pin = led->gpio_pin;
	myLEDConfig.Pull = GPIO_NOPULL;
	myLEDConfig.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(led->gpio_port, &myLEDConfig);
	HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, led->value = LED_VALUE_OFF);
	return LED_STATUS_OK;
}
/*!
 *******************************************************************************
 * @fn     led_status_t led_turn_off(led_init_t *led);
 *
 * @brief   The fuction handle led off
 *
 * @param   led            - handle for led
 * @return  LED_STATUS_OK
 * @return  LED_STATUS_ERROR_OPTION
 * @return  LED_STATUS_ERROR_NULL_PTR
 ******************************************************************************/
led_status_t led_turn_off(led_t *led) // turn off led
{
	assert_param(led != NULL);
	if (led == NULL)
	{
		return LED_STATUS_ERROR_NULL_PTR;
	}

	HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, led->value = LED_VALUE_OFF);
	return LED_STATUS_OK;
}
/*!
 *******************************************************************************
 * @fn      led_status_t led_turn_on(led_init_t *led);
 *
 * @brief   The fuction handle led on
 *
 * @param   led            - handle for led
 * @return  LED_STATUS_OK
 * @return  LED_STATUS_ERROR_OPTION
 * @return  LED_STATUS_ERROR_NULL_PTR
 ******************************************************************************/
led_status_t led_turn_on(led_t *led) // turn on led
{
	assert_param(led != NULL);
	if (led == NULL)
	{
		return LED_STATUS_ERROR_NULL_PTR;
	}
	HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, led->value = LED_VALUE_ON);
	return LED_STATUS_OK;
}
/*!
 *******************************************************************************
 * @fn      led_status_t led_toggle(led_init_t *led);
 *
 * @brief   The fuction handle toggle status led
 *
 * @param   led            - handle for led
 *
 * @return 	LED_STATUS_OK
 * @return  LED_STATUS_ERROR_OPTION
 * @return 	LED_STATUS_ERROR_NULL_PTR
 ******************************************************************************/
led_status_t led_toggle(led_t *led) // toggle led
{
	assert_param(led != NULL);
	if (led == NULL)
	{
		return LED_STATUS_ERROR_NULL_PTR;
	}
	HAL_GPIO_TogglePin(led->gpio_port, led->gpio_pin);
	return LED_STATUS_OK;
}
/*******************************************************************************
End of file -------------------------------------------------------- */
