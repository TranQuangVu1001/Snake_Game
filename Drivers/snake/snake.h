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

#ifndef SNAKE_SNAKE_H_
#define SNAKE_SNAKE_H_
#ifdef __cplusplus
extern "C"
{
#endif
/* Includes ----------------------------------------------------------- */
#include"stm32f407xx.h"
#include "ssd1306.h"
#include "fonts.h"
#include "ttp229.h"
#include "sys_led.h"
#include <stdio.h>
/* Public define ------------------------------------------------------ */
#define MAX 						128
#define HEAD_SNAKE 					0
#define MAX_WALL_UP 				5
#define MAX_WALL_DOWN 				61
#define MAX_WALL_LEFT 				5
#define MAX_WALL_RIGHT 				123
#define EAT_FRUIT 					1
#define NO_EAT_FRUIT 				0
#define SNAKE_LIE_ON_FRUIT 			1
#define NO_SNAKE_LIE_ON_FRUIT 		0
#define SNAKE_TOUCH_BODY 			1
#define NO_SNAKE_TOUCH_BODY 		0
#define TOUCH_WALL 					1
#define NO_TOUCH_WALL 				0
#define FONT_HIGH 					2
#define FONT_WIDTH 					2
#define POSITON_HEAD_SNAKE 			0
/* Public typedef enum  ----------------------------------------------- */
/**
 * @brief <status snake>
 */
typedef enum
{
	PLAY,
	GAME_OVER
}
snake_status_t;
/**
 * @brief <direction_t>
 */
typedef enum
{
	GO_UP,
	GO_DOWN,
	GO_LEFT,
	GO_RIGHT
} direction_t;
/* Public function prototypes ----------------------------------------- */
/*!
 *******************************************************************************
 * @fn      uint8_t check_game_over(void);
 *
 * @brief   The fuction check snake play or game over
 *
 * @param   NULL
 * @return 	TOUCH_WALL
 * @return  NO_TOUCH_WALL
 ******************************************************************************/
uint8_t check_game_over(void);
/*!
 *******************************************************************************
 * @fn      uint8_t check_snake_eat_fruit(void);
 *
 * @brief   The fuction check snake eat fruit.
 *
 * @param   NULL
 * @return 	EAT_FRUIT
 * @return  NO_EAT_FRUIT
 ******************************************************************************/
uint8_t check_snake_eat_fruit(void);
/*!
 *******************************************************************************
 * @fn      void handle_snake_eat_fruit(void);
 *
 * @brief   The fuction handle snake eat fruit
 *
 * @param   NULL
 * @return  NULL
 ******************************************************************************/
void handle_snake_eat_fruit(void);
/*!
 *******************************************************************************
 * @fn      uint8_t check_snake_touch_body(void);
 *
 * @brief   The fuction handle check snake touch body.
 *
 * @param   NULL
 * @return  SNAKE_TOUCH_BODY
 * @return  NO_SNAKE_TOUCH_BODY
 ******************************************************************************/
uint8_t check_snake_touch_body(void);
/*!
 *******************************************************************************
 * @fn      uint8_t check_snake_touch_body(void);
 *
 * @brief   The fuction handle check snake touch body.
 *
 * @param   NULL
 * @return  SNAKE_TOUCH_BODY
 * @return  NO_SNAKE_TOUCH_BODY
 ******************************************************************************/
uint8_t check_snake_lie_on_fruit(void);
/*!
 *******************************************************************************
 * @fn      void init_fruit(void);
 *
 * @brief   The fuction initialize  create  co-ordinate fruit.
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void init_fruit(void);
/*!
 *******************************************************************************
 * @fn      void draw_fruit(void);
 *
 * @brief   The fuction draw fruit in LCD
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void draw_fruit(void);
/*!
 *******************************************************************************
 * @fn      void draw_wall_up(void);
 *
 * @brief   The fuction draw wall (frame) up
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void draw_wall_up(void);
/*!
 *******************************************************************************
 * @fn      void draw_wall_down(void);
 *
 * @brief   The fuction draw wall (frame) down
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void draw_wall_down(void);
/*!
 *******************************************************************************
 * @fn      void draw_wall_left(void);
 *
 * @brief   The fuction draw wall (frame) left
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void draw_wall_left(void);
/*!
 *******************************************************************************
 * @fn      void draw_wall_right(void);
 *
 * @brief   The fuction draw wall (frame) right
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void draw_wall_right(void);
/*!
 *******************************************************************************
 * @fn      void draw_wall(void);
 *
 * @brief   The fuction draw 4 wall
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void draw_wall(void);
/*!
 *******************************************************************************
 * @fn      void init_snake(void);
 *
 * @brief   The fuction initialize co-oridinate snake to draw
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void init_snake(void);
/*!
 *******************************************************************************
 * @fn     void draw_snake(void);
 *
 * @brief   The fuction draw snake
 *
 * @param   NULL
 * @return  NULL
 * @return  NULL
 ******************************************************************************/
void draw_snake(void);
/*!
 *******************************************************************************
 * @fn    snake_status_t play_snake();
 *
 * @brief   The fuction handle how to snake play
 *
 * @param   NULL
 * @return  GAME_OVER
 * @return  GO_UP, GO_RIGHT, GO_DOWN, GO_LEFT
 ******************************************************************************/
snake_status_t play_snake();


#ifdef __cplusplus
}
#endif
#endif /* SNAKE_SNAKE_H_ */
