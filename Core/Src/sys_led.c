/**
 * @file       sys_led.c
 * @version    0.0.1
 * @date       2022-08-01
 * @author     Vu Tran
 */
/*************************************************************************/

/* Private include ------------------------------------------------------------*/
#include "sys_led.h"

#include "../../Drivers/led/led.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
led_t led1;  // Declare led 1 to use detect
led_t led2;  // Declare led 2 to use detect
led_t led3;  // Declare led 3 to use detect
led_t led4;  // Declare led 4 to use detect
/*subfunction ----------------------------------------------------------------*/
void sys_led_init()
{
  led_init(&led1, GPIOD, GPIO_PIN_12);  // The initialization GPIO_PORT and GPIP_PIN Led 1
  led_init(&led2, GPIOD, GPIO_PIN_13);  // The initialization GPIO_PORT and GPIP_PIN Led 2
  led_init(&led3, GPIOD, GPIO_PIN_14);  // The initialization GPIO_PORT and GPIP_PIN Led 3
  led_init(&led4, GPIOD, GPIO_PIN_15);  // The initialization GPIO_PORT and GPIP_PIN Led 4
}
void sys_led_config()
{
  configure_led_pins(&led1);    // The configuration GPIO_PORT and GPIO_PIN Led 1
  configure_led_pins(&led2);    // The configuration GPIO_PORT and GPIO_PIN Led 2
  configure_led_pins(&led3);    // The configuration GPIO_PORT and GPIO_PIN Led 3
  configure_led_pins(&led4);    // The configuration GPIO_PORT and GPIO_PIN Led 4
}

void led_start_game()
{
  for(int i = 2; i >= 0 ; i--)
  {
    led_toggle(&led1);
    HAL_Delay(350);
    led_toggle(&led1);
    led_toggle(&led2);
    HAL_Delay(350);
    led_toggle(&led2);
    led_toggle(&led3);
    HAL_Delay(350);
    led_toggle(&led3);
    led_toggle(&led4);
    HAL_Delay(350);
    led_toggle(&led4);
  }
}
void set_off_leds()
{
	led_turn_off(&led1);
	led_turn_off(&led2);
	led_turn_off(&led3);
	led_turn_off(&led4);
}
void set_on_leds()
{
	led_turn_on(&led1);
	led_turn_on(&led2);
	led_turn_on(&led3);
	led_turn_on(&led4);
}
void set_toggle_all_leds()
{
	led_toggle(&led1);
	led_toggle(&led2);
	led_toggle(&led3);
	led_toggle(&led4);
}
/* End of file -------------------------------------------------------- */
