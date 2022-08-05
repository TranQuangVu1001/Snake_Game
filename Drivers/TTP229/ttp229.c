/**
 * @file       ttp229.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2022-08-03
 * @author     Vinh Le
 *
 * @brief      A library for touch pad
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "ttp229.h"


/* Function definitions ----------------------------------------------- */
ttp229_key_t get_key()
{
	uint16_t key;
	HAL_SPI_Receive(&hspi1, &key, 1, HAL_MAX_DELAY);
	switch(key)
	{
	case NUM_2:
		return KEY_UP;
	case NUM_5:
		return KEY_LEFT;
	case NUM_7:
		return KEY_RIGHT;
	case NUM_10:
		return KEY_DOWN;
	case NUM_15:
		return KEY_START;
	case NUM_16:
		return KEY_MODE;
	default:
		return NO_PRESS;
	}
}

/* End of file -------------------------------------------------------- */
