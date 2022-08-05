/**
 * @file       ssd1306.h
 * @version    0.0.1
 * @date       2022-07-27
 * @author     Vinh Le
 *
 * @brief      a library aims to connect OLED with MCU using I2C protocol
 *
 * @attention
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SSD1306_H
#define __SSD1306_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "string.h"
#include "fonts.h"

/* Public defines ----------------------------------------------------- */
#define SSD1306_WIDTH		(128)
#define SSD1306_HEIGHT		(64)
#define SSD1306_I2C_ADDR	(0x78)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief two color: black and white
 */
typedef enum
{
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
}
ssd1306_color_t;

/**
 * @brief Initializes ssd1306 LCD
 */
typedef struct
{
	I2C_HandleTypeDef* i2c;
	uint16_t current_x;
	uint16_t current_y;
	uint8_t inverted;
	uint8_t initialized;
}
ssd1306_name_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Initializes ssd1306 LCD
 * @param  None
 * @return Initialization status:
 *           - 0: LCD was not detected on I2C port
 *           - > 0: LCD initialized OK and ready to use
 */
uint8_t ssd1306_init(ssd1306_name_t* ssd1306, I2C_HandleTypeDef* i2c);

/**
 * @brief  Updates buffer from internal RAM to LCD
 * @attention   This function must be called each time you do some changes to LCD, to update buffer from RAM to LCD
 * @param  None
 * @return None
 */
void ssd1306_update_screen(void);

/**
 * @brief  Toggles pixels invertion inside internal RAM
 * @attention   ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  None
 * @return None
 */
void ssd1306_toggle_invert(void);

/**
 * @brief  Fills entire LCD with desired color
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @return None
 */
void ssd1306_fill(ssd1306_color_t color);

/**
 * @brief  Draws pixel at desired location
 * @attention   @ref ssd1306_UpdateScreen() must called after that in order to see updated LCD screen
 * @param  color: Color to be used for screen fill. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_draw_pixel(uint16_t x, uint16_t y, ssd1306_color_t color);

/**
 * @brief  Sets cursor pointer to desired location for strings
 * @param  x: X location. This parameter can be a value between 0 and ssd1306_WIDTH - 1
 * @param  y: Y location. This parameter can be a value between 0 and ssd1306_HEIGHT - 1
 * @param  color: Color to be used for screen fill. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_goto_xy(uint16_t x, uint16_t y);

/**
 * @brief  Puts character to internal RAM
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: Character to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return Character written
 */
char ssd1306_putc(char ch, FontDef_t* Font, ssd1306_color_t color);

/**
 * @brief  Puts string to internal RAM
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  *ch: String to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return Zero on success or character value when function failed
 */
char ssd1306_puts(char* str, FontDef_t* Font, ssd1306_color_t color);

/**
 * @brief  Draws line on LCD
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x0: Line X start point. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y0: Line Y start point. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  x1: Line X end point. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y1: Line Y end point. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  c: Color to be used. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, ssd1306_color_t c);

/**
 * @brief  Draws rectangle on LCD
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: Top left X start point. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y: Top left Y start point. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  w: Rectangle width in units of pixels
 * @param  h: Rectangle height in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_draw_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ssd1306_color_t c);

/**
 * @brief  Draws filled rectangle on LCD
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: Top left X start point. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y: Top left Y start point. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  w: Rectangle width in units of pixels
 * @param  h: Rectangle height in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_drawfilled_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ssd1306_color_t c);

/**
 * @brief  Draws triangle on LCD
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x1: First coordinate X location. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y1: First coordinate Y location. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  x2: Second coordinate X location. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y2: Second coordinate Y location. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  x3: Third coordinate X location. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y3: Third coordinate Y location. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  c: Color to be used. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_draw_triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, ssd1306_color_t color);

/**
 * @brief  Draws circle to STM buffer
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: X location for center of circle. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y: Y location for center of circle. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  r: Circle radius in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_draw_circle(int16_t x0, int16_t y0, int16_t r, ssd1306_color_t c);

/**
 * @brief  Draws filled circle to STM buffer
 * @attention   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: X location for center of circle. Valid input is 0 to ssd1306_WIDTH - 1
 * @param  y: Y location for center of circle. Valid input is 0 to ssd1306_HEIGHT - 1
 * @param  r: Circle radius in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref ssd1306_color_t enumeration
 * @return None
 */
void ssd1306_drawfilled_circle(int16_t x0, int16_t y0, int16_t r, ssd1306_color_t c);

/**
 * @brief  Writes single byte to slave
 * @param  *I2Cx: I2C used
 * @param  address: 7 bit slave address, left aligned, bits 7:1 are used, LSB bit is not used
 * @param  reg: register to write to
 * @param  data: data to be written
 * @return None
 */
void ssd1306_i2c_write(uint8_t address, uint8_t reg, uint8_t data);

/**
 * @brief  Writes multi bytes to slave
 * @param  *I2Cx: I2C used
 * @param  address: 7 bit slave address, left aligned, bits 7:1 are used, LSB bit is not used
 * @param  reg: register to write to
 * @param  *data: pointer to data array to write it to slave
 * @param  count: how many bytes will be written
 * @return None
 */
void ssd1306_i2c_write_multi(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

/**
 * @brief  Draws the Bitmap
 * @param  X:  X location to start the Drawing
 * @param  Y:  Y location to start the Drawing
 * @param  *bitmap : Pointer to the bitmap
 * @param  W : width of the image
 * @param  H : Height of the image
 * @param  color : 1-> white/blue, 0-> black
 */
void ssd1306_draw_bitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);

/**
 * @brief  scroll the screen to the right
 *
 * @param  start_now: starting page
 * @param  end_row: ending page
 */
void ssd1306_scroll_right(uint8_t start_row, uint8_t end_row);

/**
 * @brief  scroll the screen to the left
 *
 * @param  start_now: starting page
 * @param  end_row: ending page
 */
void ssd1306_scroll_left(uint8_t start_row, uint8_t end_row);

/**
 * @brief  scroll the screen to the right and vertical
 *
 * @param  start_now: starting page
 * @param  end_row: ending page
 */
void ssd1306_scroll_diagright(uint8_t start_row, uint8_t end_row);

/**
 * @brief  scroll the screen to the left and vertical
 *
 * @param  start_now: starting page
 * @param  end_row: ending page
 */
void ssd1306_scroll_diagleft(uint8_t start_row, uint8_t end_row);

/**
 * @brief  stop scrolling
 */
void ssd1306_stop_scroll(void);

/**
 * @brief  invert the status of each pixel
 */
void ssd1306_invert_display(int i);

/**
 * @brief  clear the screen
 */
void ssd1306_clear (void);
#endif // __SSD1306_H
/* End of file -------------------------------------------------------- */


