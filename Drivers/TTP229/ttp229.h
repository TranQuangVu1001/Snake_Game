/**
 * @file       ttp229.h
 * @version    1.0.0
 * @date       2022-08-03
 * @author     Vinh Le
 *
 * @brief      A library for touch pad
 *
 * @note
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __TTP229_H
#define __TTP229_H
#ifdef __cplusplus
extern "C"
{
#endif
/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "stdint.h"
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief key
 */
typedef enum
{
	NUM_1  = 32767,
	NUM_2  = 49151,
	NUM_3  = 57343,
	NUM_4  = 61439,
	NUM_5  = 63487,
	NUM_6  = 64511,
	NUM_7  = 65023,
	NUM_8  = 65279,
	NUM_9  = 65407,
	NUM_10 = 65471,
	NUM_11 = 65503,
	NUM_12 = 65519,
	NUM_13 = 65527,
	NUM_14 = 65531,
	NUM_15 = 65533,
	NUM_16 = 65534
}
ttp229_num_t;
/* --------------------------------------------------------------------- */
/**
 * @brief key
 */
typedef enum
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_START,
	KEY_MODE,
	NO_PRESS
}
ttp229_key_t;

/* Public variables --------------------------------------------------- */
extern SPI_HandleTypeDef hspi1;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  detect key
 *
 *
 * @attention
 *
 * @return
 */
ttp229_key_t get_key();
#ifdef __cplusplus
}
#endif
#endif // __TTP229_H

/* End of file -------------------------------------------------------- */
