/* vim: set ai et ts=4 sw=4: */
#pragma once

#include "fonts.hpp"

#define ST7735_MADCTL_MY 0x80
#define ST7735_MADCTL_MX 0x40
#define ST7735_MADCTL_MV 0x20
#define ST7735_MADCTL_ML 0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH 0x04

// WaveShare ST7735S-based 1.8" display, default orientation
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB)
*/

// WaveShare ST7735S-based 1.8" display, rotate right
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 1
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB)
*/

// WaveShare ST7735S-based 1.8" display, rotate left
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 1
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB)
*/

// WaveShare ST7735S-based 1.8" display, upside down
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ST7735_ROTATION (ST7735_MADCTL_RGB)
*/

// 1.44" display, default orientation
/*#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 2
#define ST7735_YSTART 3
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_BGR)
*/

// 1.44" display, rotate right
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 3
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// 1.44" display, rotate left
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 1
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// 1.44" display, upside down
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ST7735_ROTATION (ST7735_MADCTL_BGR)
*/

// mini 160x80 display (it's unlikely you want the default orientation)
/*
#define ST7735_IS_160X80 1
#define ST7735_XSTART 26
#define ST7735_YSTART 1
#define ST7735_WIDTH  80
#define ST7735_HEIGHT 160
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_BGR)
*/

// mini 160x80, rotate left
/*
#define ST7735_IS_160X80 1
#define ST7735_XSTART 1
#define ST7735_YSTART 26
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 80
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// mini 160x80, rotate right
/*
#define ST7735_IS_160X80 1
#define ST7735_XSTART 1
#define ST7735_YSTART 26
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 80
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

/****************************/

#define ST7735_NOP 0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID 0x04
#define ST7735_RDDST 0x09

#define ST7735_SLPIN 0x10
#define ST7735_SLPOUT 0x11
#define ST7735_PTLON 0x12
#define ST7735_NORON 0x13

#define ST7735_INVOFF 0x20
#define ST7735_INVON 0x21
#define ST7735_GAMSET 0x26
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E

#define ST7735_PTLAR 0x30
#define ST7735_COLMOD 0x3A
#define ST7735_MADCTL 0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_RDID1 0xDA
#define ST7735_RDID2 0xDB
#define ST7735_RDID3 0xDC
#define ST7735_RDID4 0xDD

#define ST7735_PWCTR6 0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define ST7735_BLACK 0x0000
#define ST7735_BLUE 0x001F
#define ST7735_RED 0xF800
#define ST7735_GREEN 0x07E0
#define ST7735_CYAN 0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW 0xFFE0
#define ST7735_WHITE 0xFFFF
#define ST7735_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum
	{
		GAMMA_10 = 0x01,
		GAMMA_25 = 0x02,
		GAMMA_22 = 0x04,
		GAMMA_18 = 0x08
	} GammaDef;

	struct DisplayType
	{
		const uint8_t width;
		const uint8_t height;
		const uint8_t x_start;
		const uint8_t y_start;
		const uint8_t rotation;
		const bool need_color_inversion;

		DisplayType() = delete;

	protected:
		DisplayType(uint8_t w, uint8_t h, uint8_t xs, uint8_t ys, uint8_t r, bool ci) : width(w), height(h), x_start(xs), y_start(ys), rotation(r), need_color_inversion(ci) {};
	};

	namespace display_types
	{

		struct Ali_normal_160_128 : DisplayType
		{
			static Ali_normal_160_128 *instance()
			{
				static auto instance = Ali_normal_160_128();
				return &instance;
			};

		private:
			Ali_normal_160_128() : DisplayType(128, 160, 0, 0, ST7735_MADCTL_MX | ST7735_MADCTL_MY, false) {};
		};

		struct Ali_right_160_128 : DisplayType
		{
			static Ali_right_160_128 *instance()
			{
				static auto instance = Ali_right_160_128();
				return &instance;
			};

		private:
			Ali_right_160_128() : DisplayType(160, 128, 0, 0, ST7735_MADCTL_MY | ST7735_MADCTL_MV, false) {};
		};

		struct Ali_left_160_128 : DisplayType
		{
			static Ali_left_160_128 *instance()
			{
				static auto instance = Ali_left_160_128();
				return &instance;
			};

		private:
			Ali_left_160_128() : DisplayType(160, 128, 0, 0, ST7735_MADCTL_MX | ST7735_MADCTL_MV, false) {};
		};
		struct Ali_upside_down_160_128 : DisplayType
		{
			static Ali_upside_down_160_128 *instance()
			{
				static auto instance = Ali_upside_down_160_128();
				return &instance;
			};

		private:
			Ali_upside_down_160_128() : DisplayType(128, 160, 0, 0, 0, false) {};
		};
	}
	class ST7735
	{
		void writeCommand(uint8_t cmd);
		void writeData(uint8_t *buff, size_t buff_size);
		void executeCommandList(uint8_t *addr);
		void writeChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
		void setAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

	protected:
		SPI_HandleTypeDef *spi;
		DisplayType *dt;
		uint16_t res_pin;
		uint16_t cs_pin;
		uint16_t dc_pin;
		GPIO_TypeDef *res_port;
		GPIO_TypeDef *cs_port;
		GPIO_TypeDef *dc_port;

	public:
		ST7735(DisplayType *dt, SPI_HandleTypeDef *spi,
			   uint16_t res_pin, uint16_t cs_pin, uint16_t dc_pin,
			   GPIO_TypeDef *res_port, GPIO_TypeDef *cs_port, GPIO_TypeDef *dc_port);

		// call before initializing any SPI devices
		void unselect();
		void select();
		void reset();
		void init(void);
		void drawPixel(uint16_t x, uint16_t y, uint16_t color);
		void writeString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);
		void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
		void fillRectangleFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
		void fillScreen(uint16_t color);
		void fillScreenFast(uint16_t color);
		void drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data);
		void invertColors(bool invert);
		void setGamma(GammaDef gamma);
	};
#ifdef __cplusplus
}
#endif
