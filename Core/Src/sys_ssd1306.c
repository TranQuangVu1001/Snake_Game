/**
 * @file       sys_ssd1306.c
 * @version    0.0.1
 * @date       2022-08-02
 * @author     Vu Tran
 */
/*************************************************************************/
/* Private include ------------------------------------------------------*/
#include "sys_ssd1306.h"
#include "bitmap.h"
/* Public variables --------------------------------------------------- */
ttp229_key_t temp;
snake_status_t snake;
/* Function definitions ----------------------------------------------- */
void ssd1306_draw_circles(uint8_t radius, uint16_t color)
{
	ssd1306_clear();

	uint8_t x, y, r2 = radius * 2,
				  w = SSD1306_WIDTH + radius,
				  h = SSD1306_HEIGHT + radius;

	for (x = 0; x < w; x += r2)
	{
		for (y = 0; y < h; y += r2)
		{
			ssd1306_draw_circle(x, y, radius, color);
			ssd1306_update_screen();
			HAL_Delay(10);
		}
	}
}
void display_menu_on_oled(void)
{
	ssd1306_draw_circles(15, 1);
	HAL_Delay(1000);
	ssd1306_fill(SSD1306_COLOR_BLACK);
	ssd1306_update_screen();
	HAL_Delay(500);
	ssd1306_goto_xy(55, 20);
	ssd1306_puts("3", &Font_16x26, 1);
	ssd1306_update_screen();
	HAL_Delay(1000);
	ssd1306_fill(SSD1306_COLOR_BLACK);
	ssd1306_update_screen();
	HAL_Delay(1000);
	ssd1306_goto_xy(55, 20);
	ssd1306_puts("2", &Font_16x26, 1);
	ssd1306_update_screen();
	HAL_Delay(1000);
	ssd1306_fill(SSD1306_COLOR_BLACK);
	ssd1306_update_screen();
	HAL_Delay(1000);
	ssd1306_goto_xy(55, 20);
	ssd1306_puts("1", &Font_16x26, 1);
	ssd1306_update_screen();
	HAL_Delay(1000);
	ssd1306_fill(SSD1306_COLOR_BLACK);
	ssd1306_update_screen();
	HAL_Delay(1000);
	ssd1306_goto_xy(11, 0);
	ssd1306_puts("SNAKE GAME", &Font_11x18, 1);
	ssd1306_goto_xy(10, 30);
	ssd1306_puts("6.Start Game", &Font_7x10, 1);
	ssd1306_goto_xy(30, 50);
	ssd1306_puts("~~~~~~~~~", &Font_7x10, 1);
	ssd1306_update_screen();
	while (1)
	{
		temp = get_key();
		HAL_Delay(2);
		if (temp == KEY_START)
		{
			start_game();
		}
	}
}
void start_game(void)
{
	set_on_leds();
	ssd1306_fill(SSD1306_COLOR_BLACK);
	ssd1306_update_screen();
	HAL_Delay(1000);
	ssd1306_goto_xy(45, 18);
	ssd1306_puts("GO", &Font_16x26, 1);
	ssd1306_update_screen();
	HAL_Delay(2500);
	ssd1306_fill(SSD1306_COLOR_BLACK);
	ssd1306_update_screen();
	HAL_Delay(700);
	printf("GO GO GO\n");
	snake = play_snake();
}
/* End of file -------------------------------------------------------- */
