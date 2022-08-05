/**
 * @file       button.c
 * @version    0.0.1
 * @date       2022-08-01
 * @author     Vu Tran
 */
/*************************************************************************
*** Includes ----------------------------------------------------------- */
#include "button.h"

#include "main.h"

#include "../led/led.h"
/* Private variables-------------------------------------------------------- */

uint16_t HOLD_TIME = 2500;
uint16_t DEBOUNCE_TIME = 50;
uint32_t finish_time_press = 0;
/*Function ----------------------------------------------------------------*/
void button_init(button_name_t *button_name, GPIO_TypeDef *gpio_x, uint16_t gpio_pin)
{
    assert_param(button_name != NULL);
    assert_param(gpio_x != NULL);
    assert_param(gpio_pin != NULL);
    button_name->button_port = gpio_x;
    button_name->button_pin = gpio_pin;
    button_name->event = BUTTON_EVT_NON;
}

void configure_button_pins(button_name_t *button_name, int priority_exti)
{
    assert_param(button_name != NULL);
    assert_param(priority_exti != NULL);
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();


    GPIO_InitTypeDef my_button_config;
    my_button_config.Mode = GPIO_MODE_IT_RISING;
    my_button_config.Pin = button_name->button_pin;
    my_button_config.Pull = GPIO_NOPULL;
    my_button_config.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(button_name->button_port, &my_button_config);
    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, priority_exti, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void button_get_state(button_name_t *button_name)
{
    assert_param(button_name != NULL);
    if (HAL_GPIO_ReadPin(button_name->button_port, button_name->button_pin) == 1)
    {
        button_name->state = BUTTON_STATE_ACTIVE;
    }
    if (HAL_GPIO_ReadPin(button_name->button_port, button_name->button_pin) == 0)
    {
        button_name->state = BUTTON_STATE_DEACTIVE;
    }
    assert_param(HAL_GPIO_ReadPin(button_name->button_port, button_name->button_pin) == SET);
    assert_param(HAL_GPIO_ReadPin(button_name->button_port, button_name->button_pin) == RESET);
}

void get_event_from_sys_button(button_name_t *button, uint32_t start_time_press)
{
    assert_param(button != NULL);
    assert_param(start_time_press != NULL);
    button_get_state(button); // Check button had ACTIVE or DEACTIVE
    finish_time_press = HAL_GetTick();
    if ((finish_time_press - start_time_press) > HOLD_TIME) // check HOLD event
    {
        button->event = BUTTON_EVT_HOLD;
        finish_time_press = start_time_press;
    }
    if (button->state == BUTTON_STATE_DEACTIVE)
    {
        if ((finish_time_press - start_time_press) > DEBOUNCE_TIME && (finish_time_press - start_time_press) < HOLD_TIME) // check CLICK event
        {
            button->event = BUTTON_EVT_CLICK;
            finish_time_press = start_time_press;
        }
    }
    assert_param(button_get_state(button->button_port, button->button_pin) == BUTTON_STATE_ACTIVE);
    assert_param(button_get_state(button->button_port, button->button_pin) == RBUTTON_STATE_DECTIVE);
}



/* End of file -------------------------------------------------------- */
