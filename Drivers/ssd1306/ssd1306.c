/**
 * @file       ssd1306.c
 * @version    1.0
 * @date       2022-07-27
 * @author     Vinh Le
 *
 * @brief      a library aims to connect OLED with MCU using I2C protocol
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "ssd1306.h"

/* Private defines ---------------------------------------------------- */
#define SSD1306_RIGHT_HORIZONTAL_SCROLL					(0x26)
#define SSD1306_LEFT_HORIZONTAL_SCROLL					(0x27)
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL	(0x29)
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL		(0x2A)
#define SSD1306_DEACTIVATE_SCROLL						(0x2E)
#define SSD1306_ACTIVATE_SCROLL							(0x2F)
#define SSD1306_SET_VERTICAL_SCROLL_AREA				(0xA3)
#define SSD1306_NORMALDISPLAY 							(0xA6)
#define SSD1306_INVERTDISPLAY							(0xA7)



/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */
#define SSD1306_WRITECOMMAND(command)		ssd1306_i2c_write(SSD1306_I2C_ADDR, 0x00, (command))
#define SSD1306_WRITEDATA(data)				ssd1306_i2c_write(SSD1306_I2C_ADDR, 0x40, (data))
#define ABS(x)   ((x) > 0 ? (x) : -(x))

/* Public variables --------------------------------------------------- */
extern I2C_HandleTypeDef hi2c2;


/* Private variables -------------------------------------------------- */
static uint8_t ssd1306_buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
static ssd1306_name_t ssd1306;

/* Private function prototypes ---------------------------------------- */
uint8_t ssd1306_init(ssd1306_name_t* ssd1306, I2C_HandleTypeDef* i2c)
{
	ssd1306->i2c = i2c;
	if (HAL_I2C_IsDeviceReady(ssd1306->i2c, SSD1306_I2C_ADDR, 1, 20000) != HAL_OK)
	{
		return 0;
	}
	uint32_t p = 2500; //delay
	while(p>0)	p--;
	/* Init LCD */
	SSD1306_WRITECOMMAND(0xAE); //display off
	SSD1306_WRITECOMMAND(0x20); //Set Memory Addressing Mode
	SSD1306_WRITECOMMAND(0x10); //Page addressing mode
	SSD1306_WRITECOMMAND(0xB0); //Set Page Start Address
	SSD1306_WRITECOMMAND(0xC8); //Set COM Output Scan Direction
	SSD1306_WRITECOMMAND(0x00); //---set low column address
	SSD1306_WRITECOMMAND(0x10); //---set high column address
	SSD1306_WRITECOMMAND(0x40); //--set start line address
	SSD1306_WRITECOMMAND(0x81); //--set contrast control register
	SSD1306_WRITECOMMAND(0xFF);
	SSD1306_WRITECOMMAND(0xA1); //--set segment re-map 0 to 127
	SSD1306_WRITECOMMAND(0xA6); //--set normal display
	SSD1306_WRITECOMMAND(0xA8); //--set multiplex ratio(1 to 64)
	SSD1306_WRITECOMMAND(0x3F); //
	SSD1306_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	SSD1306_WRITECOMMAND(0xD3); //-set display offset
	SSD1306_WRITECOMMAND(0x00); //-not offset
	SSD1306_WRITECOMMAND(0xD5); //--set display clock divide ratio/oscillator frequency
	SSD1306_WRITECOMMAND(0xF0); //--set divide ratio
	SSD1306_WRITECOMMAND(0xD9); //--set pre-charge period
	SSD1306_WRITECOMMAND(0x22); //
	SSD1306_WRITECOMMAND(0xDA); //--set com pins hardware configuration
	SSD1306_WRITECOMMAND(0x12);
	SSD1306_WRITECOMMAND(0xDB); //--set vcomh
	SSD1306_WRITECOMMAND(0x20); //0x20,0.77xVcc
	SSD1306_WRITECOMMAND(0x8D); //--set DC-DC enable
	SSD1306_WRITECOMMAND(0x14); //
	SSD1306_WRITECOMMAND(0xAF); //--turn on SSD1306 panel
	SSD1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);
	/* Clear screen */
	ssd1306_fill(SSD1306_COLOR_BLACK);
	/* Update screen */
	ssd1306_update_screen();
	/* Set default values */
	ssd1306->current_x = 0;
	ssd1306->current_y = 0;
	/* Initialized OK */
	ssd1306->initialized = 1;
	/* Return OK */
	return 1;
}

void ssd1306_update_screen(void)
{
	uint8_t m;
	for (m = 0; m < 8; m++)
	{
		SSD1306_WRITECOMMAND(0xB0 + m);
		SSD1306_WRITECOMMAND(0x00);
		SSD1306_WRITECOMMAND(0x10);
		/* Write multi data */
		ssd1306_i2c_write_multi(SSD1306_I2C_ADDR, 0x40, &ssd1306_buffer[SSD1306_WIDTH * m], SSD1306_WIDTH);
	}
}

void ssd1306_toggle_invert(void)
{
	uint16_t i;
	/* Toggle invert */
	ssd1306.inverted = !ssd1306.inverted;
	/* Do memory toggle */
	for (i = 0; i < sizeof(ssd1306_buffer); i++)
	{
		ssd1306_buffer[i] = ~ssd1306_buffer[i];
	}
}

void ssd1306_fill(ssd1306_color_t color)
{
	/* Set memory */
	memset(ssd1306_buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(ssd1306_buffer));
}

void ssd1306_draw_pixel(uint16_t x, uint16_t y, ssd1306_color_t color)
{
	if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		/* Error */
		return;
	}
	/* Check if pixels are inverted */
	if (ssd1306.inverted)
	{
		color = (ssd1306_color_t)!color;
	}
	/* Set color */
	if (color == SSD1306_COLOR_WHITE)
	{
		ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	}
	else
	{
		ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

void ssd1306_goto_xy(uint16_t x, uint16_t y)
{
	/* Set write pointers */
	ssd1306.current_x = x;
	ssd1306.current_y = y;
}

char ssd1306_putc(char ch, FontDef_t* Font, ssd1306_color_t color)
{
	uint32_t i, b, j;
	/* Check available space in LCD */
	if (SSD1306_WIDTH <= (ssd1306.current_x + Font->FontWidth) || SSD1306_HEIGHT <= (ssd1306.current_y + Font->FontHeight))
	{
		/* Error */
		return 0;
	}
	/* Go through font */
	for (i = 0; i < Font->FontHeight; i++)
	{
		b = Font->data[(ch - 32) * Font->FontHeight + i];
		for (j = 0; j < Font->FontWidth; j++)
		{
			if ((b << j) & 0x8000)
			{
				ssd1306_draw_pixel(ssd1306.current_x + j, (ssd1306.current_y + i), (ssd1306_color_t) color);
			}
			else
			{
				ssd1306_draw_pixel(ssd1306.current_x + j, (ssd1306.current_y + i), (ssd1306_color_t)!color);
			}
		}
	}
	/* Increase pointer */
	ssd1306.current_x += Font->FontWidth;
	/* Return character written */
	return ch;
}

char ssd1306_puts(char* str, FontDef_t* Font, ssd1306_color_t color)
{
	/* Write characters */
	while (*str) {
		/* Write character by character */
		if (ssd1306_putc(*str, Font, color) != *str)
		{
			/* Return error */
			return *str;
		}
		/* Increase string pointer */
		str++;
	}
	/* Everything OK, zero should be returned */
	return *str;
}

void ssd1306_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, ssd1306_color_t c) {
	int16_t dx, dy, sx, sy, err, e2, i, tmp;

	/* Check for overflow */
	if (x0 >= SSD1306_WIDTH)
	{
		x0 = SSD1306_WIDTH - 1;
	}
	if (x1 >= SSD1306_WIDTH)
	{
		x1 = SSD1306_WIDTH - 1;
	}
	if (y0 >= SSD1306_HEIGHT)
	{
		y0 = SSD1306_HEIGHT - 1;
	}
	if (y1 >= SSD1306_HEIGHT)
	{
		y1 = SSD1306_HEIGHT - 1;
	}

	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = ((dx > dy) ? dx : -dy) / 2;

	if (dx == 0)
	{
		if (y1 < y0)
		{
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0)
		{
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Vertical line */
		for (i = y0; i <= y1; i++)
		{
			ssd1306_draw_pixel(x0, i, c);
		}

		/* Return from function */
		return;
	}

	if (dy == 0)
	{
		if (y1 < y0)
		{
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0)
		{
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Horizontal line */
		for (i = x0; i <= x1; i++)
		{
			ssd1306_draw_pixel(i, y0, c);
		}
		/* Return from function */
		return;
	}
	while (1)
	{
		ssd1306_draw_pixel(x0, y0, c);
		if (x0 == x1 && y0 == y1)
		{
			break;
		}
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void ssd1306_draw_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ssd1306_color_t c) {
	/* Check input parameters */
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= SSD1306_WIDTH)
	{
		w = SSD1306_WIDTH - x;
	}
	if ((y + h) >= SSD1306_HEIGHT)
	{
		h = SSD1306_HEIGHT - y;
	}

	/* Draw 4 lines */
	ssd1306_draw_line(x, y, x + w, y, c);         /* Top line */
	ssd1306_draw_line(x, y + h, x + w, y + h, c); /* Bottom line */
	ssd1306_draw_line(x, y, x, y + h, c);         /* Left line */
	ssd1306_draw_line(x + w, y, x + w, y + h, c); /* Right line */
}

void ssd1306_drawfilled_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ssd1306_color_t c) {
	uint8_t i;

	/* Check input parameters */
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= SSD1306_WIDTH)
	{
		w = SSD1306_WIDTH - x;
	}
	if ((y + h) >= SSD1306_HEIGHT)
	{
		h = SSD1306_HEIGHT - y;
	}
	/* Draw lines */
	for (i = 0; i <= h; i++)
	{
		/* Draw lines */
		ssd1306_draw_line(x, y + i, x + w, y + i, c);
	}
}

void ssd1306_draw_triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, ssd1306_color_t color) {
	/* Draw lines */
	ssd1306_draw_line(x1, y1, x2, y2, color);
	ssd1306_draw_line(x2, y2, x3, y3, color);
	ssd1306_draw_line(x3, y3, x1, y1, color);
}


void ssd1306_drawfilled_triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, ssd1306_color_t color) {
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;
	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;
	if (x2 >= x1)
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else
	{
		xinc1 = -1;
		xinc2 = -1;
	}
	if (y2 >= y1)
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else
	{
		yinc1 = -1;
		yinc2 = -1;
	}
	if (deltax >= deltay)
	{
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	}
	else
	{
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}
	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		ssd1306_draw_line(x, y, x3, y3, color);
		num += numadd;
		if (num >= den)
		{
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void ssd1306_draw_circle(int16_t x0, int16_t y0, int16_t r, ssd1306_color_t c)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;
    ssd1306_draw_pixel(x0, y0 + r, c);
    ssd1306_draw_pixel(x0, y0 - r, c);
    ssd1306_draw_pixel(x0 + r, y0, c);
    ssd1306_draw_pixel(x0 - r, y0, c);
    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ssd1306_draw_pixel(x0 + x, y0 + y, c);
        ssd1306_draw_pixel(x0 - x, y0 + y, c);
        ssd1306_draw_pixel(x0 + x, y0 - y, c);
        ssd1306_draw_pixel(x0 - x, y0 - y, c);

        ssd1306_draw_pixel(x0 + y, y0 + x, c);
        ssd1306_draw_pixel(x0 - y, y0 + x, c);
        ssd1306_draw_pixel(x0 + y, y0 - x, c);
        ssd1306_draw_pixel(x0 - y, y0 - x, c);
    }
}

void ssd1306_drawfilled_circle(int16_t x0, int16_t y0, int16_t r, ssd1306_color_t c) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    ssd1306_draw_pixel(x0, y0 + r, c);
    ssd1306_draw_pixel(x0, y0 - r, c);
    ssd1306_draw_pixel(x0 + r, y0, c);
    ssd1306_draw_pixel(x0 - r, y0, c);
    ssd1306_draw_line(x0 - r, y0, x0 + r, y0, c);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ssd1306_draw_line(x0 - x, y0 + y, x0 + x, y0 + y, c);
        ssd1306_draw_line(x0 + x, y0 - y, x0 - x, y0 - y, c);

        ssd1306_draw_line(x0 + y, y0 + x, x0 - y, y0 + x, c);
        ssd1306_draw_line(x0 + y, y0 - x, x0 - y, y0 - x, c);
    }
}

void ssd1306_i2c_write_multi(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count)
{
	uint8_t dt[256];
	dt[0] = reg;
	uint8_t i;
	for(i = 0; i < count; i++) dt[i+1] = data[i];
	HAL_I2C_Master_Transmit(&hi2c2, address, dt, count+1, 10);
}


void ssd1306_i2cwrite(uint8_t address, uint8_t reg, uint8_t data)
{
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&hi2c2, address, dt, 2, 10);
}
void ssd1306_scroll_right(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND (SSD1306_RIGHT_HORIZONTAL_SCROLL);  // send 0x26
  SSD1306_WRITECOMMAND (0x00);  // send dummy
  SSD1306_WRITECOMMAND(start_row);  // start page address
  SSD1306_WRITECOMMAND(0X00);  // time interval 5 frames
  SSD1306_WRITECOMMAND(end_row);  // end page address
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(0XFF);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL); // start scroll
}

void ssd1306_scroll_left(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND (SSD1306_LEFT_HORIZONTAL_SCROLL);  // send 0x26
  SSD1306_WRITECOMMAND (0x00);  // send dummy
  SSD1306_WRITECOMMAND(start_row);  // start page address
  SSD1306_WRITECOMMAND(0X00);  // time interval 5 frames
  SSD1306_WRITECOMMAND(end_row);  // end page address
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(0XFF);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL); // start scroll
}

void ssd1306_scroll_diagright(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);  // sect the area
  SSD1306_WRITECOMMAND (0x00);   // write dummy
  SSD1306_WRITECOMMAND(SSD1306_HEIGHT);

  SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  SSD1306_WRITECOMMAND (0x00);
  SSD1306_WRITECOMMAND(start_row);
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(end_row);
  SSD1306_WRITECOMMAND (0x01);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL);
}


void ssd1306_scroll_diagleft(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);  // sect the area
  SSD1306_WRITECOMMAND (0x00);   // write dummy
  SSD1306_WRITECOMMAND(SSD1306_HEIGHT);

  SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  SSD1306_WRITECOMMAND (0x00);
  SSD1306_WRITECOMMAND(start_row);
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(end_row);
  SSD1306_WRITECOMMAND (0x01);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL);
}

void ssd1306_stop_scroll(void)
{
	SSD1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);
}

void ssd1306_invert_display (int i)
{
  if(i) SSD1306_WRITECOMMAND (SSD1306_INVERTDISPLAY);
  else SSD1306_WRITECOMMAND (SSD1306_NORMALDISPLAY);

}

void ssd1306_draw_bitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color)
{

    int16_t byte_width = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;
    for(int16_t j=0; j<h; j++, y++)
    {
        for(int16_t i=0; i<w; i++)
        {
            if(i & 7)
            {
               byte <<= 1;
            }
            else
            {
               byte = (*(const unsigned char *)(&bitmap[j * byte_width + i / 8]));
            }
            if(byte & 0x80) ssd1306_draw_pixel(x+i, y, color);
        }
    }
}

void ssd1306_clear (void)
{
	ssd1306_fill (0);
    ssd1306_update_screen();
}
void ssd1306_on(void) {
	SSD1306_WRITECOMMAND(0x8D);
	SSD1306_WRITECOMMAND(0x14);
	SSD1306_WRITECOMMAND(0xAF);
}
void ssd1306_off(void) {
	SSD1306_WRITECOMMAND(0x8D);
	SSD1306_WRITECOMMAND(0x10);
	SSD1306_WRITECOMMAND(0xAE);
}
void ssd1306_i2c_write(uint8_t address, uint8_t reg, uint8_t data) {
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&hi2c2, address, dt, 2, 10);
}

/* End of file -------------------------------------------------------- */

