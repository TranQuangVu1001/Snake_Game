/**
 * @file       snake.h
 * @version    1.0.0
 * @date       2022-08-04
 * @author     Vinh Le, Hieu Ha, Vu Tran
 *
 * @brief      A library for play snake
 *
 * @note
 */
/*************************************************************************/


#include "snake.h"

/* Public define ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
uint8_t snake_x[128];
uint8_t snake_y[64];
uint8_t long_snake = 5;
uint8_t fruit_x = 0;
uint8_t fruit_y = 0;
ttp229_key_t direc;
uint8_t score = 0;

/**
  * @brief  dral wal up.
  * @retval int
  */
/* Public function prototypes ----------------------------------------- */
uint8_t check_game_over(void)
{
	//check snake touch wall
	if(snake_x[POSITON_HEAD_SNAKE] == MAX_WALL_LEFT || snake_x[POSITON_HEAD_SNAKE] == MAX_WALL_RIGHT
			|| snake_y[POSITON_HEAD_SNAKE] == MAX_WALL_UP || snake_y[POSITON_HEAD_SNAKE] == MAX_WALL_DOWN)
	{
		return TOUCH_WALL;
	}
	else
	{
		return NO_TOUCH_WALL;
	}
	//check snake touch body
}

/**
  * @brief  check snake touch body.
  * @retval int
  */
uint8_t check_snake_touch_body(void)
{
	for(uint8_t i = 1; i < long_snake; i++)
	{
		if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
		{
			return SNAKE_TOUCH_BODY;
		}
	}
	return NO_SNAKE_TOUCH_BODY;
}

/**
  * @brief  check snake eat fruit.
  * @retval int
  */
uint8_t check_snake_eat_fruit(void)
{
	if(snake_x[POSITON_HEAD_SNAKE] == fruit_x && snake_y[POSITON_HEAD_SNAKE] == fruit_y)
	{
		return EAT_FRUIT;
	}
	return NO_EAT_FRUIT;
}
/**
  * @brief  check snake eat fruit.
  * @retval int
  */
uint8_t check_snake_lie_on_fruit(void)
{

	for(uint8_t i = 0; i < long_snake; i++)
	{
		if((fruit_x == snake_x[i] && fruit_y == snake_y[i]))
		{
			return SNAKE_LIE_ON_FRUIT;
		}
	}
	return NO_SNAKE_LIE_ON_FRUIT;
}
/**
  * @brief  handle snake eat fruit.
  * @retval int
  */
void handle_snake_eat_fruit(void)
{

	long_snake += 3;
	init_fruit();
	draw_fruit();
}
/**
  * @brief  draw create fruit.
  * @retval int
  */
void init_fruit(void)
{
	do
	{
		fruit_x  = (5 + (uint8_t)(rand() * (59 - 5 + 1.0) / (1.0 + RAND_MAX))) * FONT_WIDTH - 1;
		fruit_y  = (5 + (uint8_t)(rand() * (10 - 5 + 1.0) / (1.0 + RAND_MAX))) * FONT_HIGH - 1;
		HAL_Delay(50);
	}
	while(check_snake_lie_on_fruit() == SNAKE_LIE_ON_FRUIT);

}
/**
  * @brief  draw fruit.
  * @retval int
  */
void draw_fruit(void)
{
	  HAL_Delay(50);
	  ssd1306_drawfilled_rectangle(fruit_x, fruit_y, 2, 2, 1);
	  ssd1306_update_screen();
}
/**
  * @brief  draw wal up.
  * @retval int
  */
void draw_wall_up(void)
{
	ssd1306_draw_line(MAX_WALL_LEFT, MAX_WALL_UP, MAX_WALL_RIGHT, MAX_WALL_UP, 1);
	ssd1306_update_screen();
}
/**
  * @brief  draw wal down.
  * @retval int
  */
void draw_wall_down(void)
{
	ssd1306_draw_line(MAX_WALL_LEFT, MAX_WALL_DOWN, MAX_WALL_RIGHT, MAX_WALL_DOWN, 1);
	ssd1306_update_screen();
}
/**
  * @brief  draw wal left.
  * @retval int
  */
void draw_wall_left(void)
{
	ssd1306_draw_line(MAX_WALL_LEFT,MAX_WALL_UP , MAX_WALL_LEFT, MAX_WALL_DOWN, 1);
	ssd1306_update_screen();
}
/**
  * @brief  draw wal right.
  * @retval int
  */
void draw_wall_right(void)
{
	ssd1306_draw_line(MAX_WALL_RIGHT, MAX_WALL_UP, MAX_WALL_RIGHT,MAX_WALL_DOWN , 1);
	ssd1306_update_screen();
}
/**
  * @brief  draw 4 wal.
  * @retval int
  */
void draw_wall(void)
{
	draw_wall_down();
	draw_wall_left();
	draw_wall_up();
	draw_wall_right();

}
/**
  * @brief  init snake.
  * @retval int
  */
void init_snake(void)
{
	uint8_t x_start_snake = 31;
	uint8_t y_start_snake = 29;
	for(uint8_t i = 0; i < long_snake; i++)
	{
		snake_x[i] = x_start_snake;
		snake_y[i] = y_start_snake;
		x_start_snake = x_start_snake - FONT_WIDTH;
	}
}
/**
  * @brief  draw snake.
  * @retval int
  */
void draw_snake(void)
{
	for(uint8_t i = 0; i < long_snake; i++)
	{
//		ssd1306_goto_xy(snake_x[i], snake_y[i]);
		ssd1306_drawfilled_rectangle(snake_x[i], snake_y[i], 2, 2, 1);
	}
	HAL_Delay(50);
	ssd1306_update_screen();


}
/**
  * @brief handle move snake.
  * @retval int
  */
void handle_move_snake(uint8_t head_snake_x, uint8_t head_snake_y)  // add head segment into snake
{
	for(uint8_t i = long_snake; i > 0; i--)
	{
		snake_x[i] = snake_x[i - 1];
		snake_y[i] = snake_y[i - 1];
	}
	snake_x[POSITON_HEAD_SNAKE] = head_snake_x;
	snake_y[POSITON_HEAD_SNAKE] = head_snake_y;
}
/**
  * @brief  play snake.
  * @retval int
  */
snake_status_t play_snake()
{

	draw_wall();
	init_snake();
	init_fruit();
	draw_snake();

	uint8_t head_snake_x = snake_x[0];
	uint8_t head_snake_y = snake_y[0];
	uint8_t check_direction = GO_RIGHT;
	while(1)
	{
		ssd1306_drawfilled_rectangle(snake_x[long_snake], snake_y[long_snake], 2, 2, 0);
		draw_snake();
		draw_fruit();
		uint8_t key = get_key();
		HAL_Delay(2);
		if(key == KEY_UP && check_direction != GO_DOWN)
		{
			check_direction = GO_UP;
		}
		else if(key == KEY_DOWN && check_direction != GO_UP)
		{
			check_direction = GO_DOWN;
		}
		else if(key == KEY_LEFT && check_direction != GO_RIGHT)
		{
			check_direction = GO_LEFT;
		}
		else if(key == KEY_RIGHT && check_direction != GO_LEFT)
		{
			check_direction = GO_RIGHT;
		}
		switch (check_direction)
		{
		case GO_UP:
			head_snake_y -= FONT_HIGH;
			break;
		case GO_DOWN:
			head_snake_y += FONT_HIGH;
			break;
		case GO_LEFT:
			head_snake_x -= FONT_WIDTH;
			break;
		case GO_RIGHT:
			head_snake_x += FONT_WIDTH;
			break;
		default:
			break;
		}
		handle_move_snake(head_snake_x, head_snake_y);
		HAL_Delay(100);
		if(check_game_over() == TOUCH_WALL)
		{
			char score_game;
		    score_game = score + '0';
		    ssd1306_fill(SSD1306_COLOR_BLACK);
		    ssd1306_update_screen();
			ssd1306_goto_xy(15, 15);
			ssd1306_puts("GAME OVER", &Font_11x18, 1);
			ssd1306_goto_xy(40, 40);
			ssd1306_puts("SCORE: ", &Font_7x10, 1);
			ssd1306_goto_xy(90, 40);
			ssd1306_putc(&score_game, &Font_7x10, 1);
			ssd1306_update_screen();
			long_snake = 5;
			score = 0;
			fruit_x = 0;
			fruit_y = 0;
			set_off_leds();
			return GAME_OVER;
			break;
		}
		if(check_snake_touch_body() == SNAKE_TOUCH_BODY)
		{
			char score_game;
			score_game = score + '0';
			ssd1306_fill(SSD1306_COLOR_BLACK);
			ssd1306_update_screen();
			ssd1306_goto_xy(15, 15);
			ssd1306_puts("GAME OVER", &Font_11x18, 1);
			ssd1306_goto_xy(40, 40);
			ssd1306_puts("SCORE: ", &Font_7x10, 1);
			ssd1306_goto_xy(90, 40);
			ssd1306_putc(&score_game, &Font_7x10, 1);
			ssd1306_update_screen();
			long_snake = 5;
			score = 0;
			fruit_x = 0;
			fruit_y = 0;
			set_off_leds();
			return GAME_OVER;
			break;
		}
		if(check_snake_eat_fruit() == EAT_FRUIT)
		{
			score ++;
			handle_snake_eat_fruit();
		}
	}

}
