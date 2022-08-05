/**
 * @file       sys_button.c
 * @version    0.0.1
 * @date       2022-08-01
 * @author     Vu Tran
 */
/*************************************************************************/
/* Private include ------------------------------------------------------------*/
#include "sys_button.h"


#include "../../Drivers/button/button.h"
/* Private typedef ------------------------------------------------------------*/
typedef enum
{
	SYS_INIT = 0,
	SYS_OFF,
	SYS_ON
} sys_state_t;
/* Private variables ---------------------------------------------------------*/
uint32_t finish_time = 0;         // Time finish press 1 button
uint32_t HOLD = 2200;			  // Hold time
uint32_t DEBOUNCE = 50;			  // Debouncing time
button_name_t button_start_game;  // Declare button to use
uint32_t flag_interrupt_exti = 0; // Flag to check interrupt has appearence
uint32_t check_event_button = 0;  // Flag to check event button
uint32_t start_press_time = 0;	  // Time start press button
uint32_t finish_press_time = 0;	  // Time start press button
uint32_t check_state = SYS_INIT;  // Check system state

/* Function ------------------- ----------------------------------------------- */
void sys_button_init()
{
	button_init(&button_start_game, GPIOA, GPIO_PIN_0); // The initialization GPIO_PORT and GPIP_PIN button
}
void sys_button_config()
{
	int prority_interupt = 2;
	configure_button_pins(&button_start_game, prority_interupt); // The configuration GPIO_PORT and GPIO_PIN button
}
void button_get_event(button_name_t *button, uint32_t start_time_press)
{
	button_get_state(button); // Check button had ACTIVE or DEACTIVE
	finish_time = HAL_GetTick();

	if ((finish_time - start_time_press) > HOLD) // check HOLD event
	{
		button->event = BUTTON_EVT_HOLD;
	}
	if (button->state == BUTTON_STATE_DEACTIVE) // check button if release
	{
		if ((finish_time - start_time_press) > DEBOUNCE && (finish_time - start_time_press) < HOLD) // check CLICK event
		{
			button->event = BUTTON_EVT_CLICK;
		}
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	start_press_time = HAL_GetTick(); // time when button press
	while (GPIO_Pin == button_start_game.button_pin)
	{
		finish_press_time = HAL_GetTick();
		if (finish_press_time - start_press_time > 50)
		{
			flag_interrupt_exti = 1; // Turn on flag check interrupt button
			break;
		}
	}
}
void button_handle_start()
{
	while(1){
	while (flag_interrupt_exti == 1)
	{
		button_get_event(&button_start_game, start_press_time); // Get button event
		if (button_start_game.event != BUTTON_EVT_NON)
		{
			flag_interrupt_exti = 0;
			break;
		}
	}
	if (button_start_game.event == BUTTON_EVT_HOLD)
	{
		flag_interrupt_exti = 0;
		button_start_game.event = BUTTON_EVT_NON;
		menu_option_for_uart();
		led_start_game();
		HAL_Delay(1000);
		display_menu_on_oled();

	}
	else if (button_start_game.event == BUTTON_EVT_CLICK)
	{
		button_start_game.event = BUTTON_EVT_NON;
		printf("Please, hold button 3 seconds to start game\n");
	}
	}
}
/* End of file -------------------------------------------------------- */
