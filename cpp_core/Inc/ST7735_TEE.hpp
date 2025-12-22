#ifndef ST7735_Font_h
#define ST7735_Font_h
#include "stm32f4xx_hal.h"

#define swap(a, b)      \
	{                   \
		uint16_t t = a; \
		a = b;          \
		b = t;          \
	}

#define ST7735_NOP 0x0
#define ST7735_SWRESET 0x01
#define ST7735_RDDID 0x04
#define ST7735_RDDST 0x09

#define ST7735_SLPIN 0x10
#define ST7735_SLPOUT 0x11
#define ST7735_PTLON 0x12
#define ST7735_NORON 0x13

#define ST7735_INVOFF 0x20
#define ST7735_INVON 0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E

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

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

class TEE_ST7735
{
private:
	SPI_HandleTypeDef spi;
	uint16_t rst_pin, cs_pin, dc_pin;
	GPIO_TypeDef rst_port, cs_port, dc_port;
	void CS_H()
	{
		HAL_GPIO_WritePin(&cs_port, cs_pin, GPIO_PIN_SET);
	}
	void CS_L()
	{
		HAL_GPIO_WritePin(&cs_port, cs_pin, GPIO_PIN_RESET);
	}
	void AO_H()
	{
		HAL_GPIO_WritePin(&rst_port, rst_pin, GPIO_PIN_SET);
	}
	void AO_L()
	{
		HAL_GPIO_WritePin(&rst_port, rst_pin, GPIO_PIN_SET);
	}

public:
	uint8_t madctl;
	uint8_t width;	//= 160;//128;
	uint8_t height; // = 128;//160;

	static const uint8_t HORIZONTAL = 1;
	static const uint8_t VERTICAL = 0;

	TEE_ST7735(uint16_t rst_pin, uint16_t cs_pin, uint16_t dc_pin,
			   GPIO_TypeDef rst_port, GPIO_TypeDef cs_port, GPIO_TypeDef dc_port, SPI_HandleTypeDef spi);
	void init(bool horizontal_orientation);
	void spiwrite(uint8_t SPI_byte);
	void writecommand(uint8_t c);
	void writedata(uint8_t c);

	void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	void pushColor(uint16_t color);
	void drawPixel(uint8_t x, uint8_t y, uint16_t color);
	void fillScreen(uint16_t color);
	void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
	void drawFastLine(uint8_t x, uint8_t y, uint8_t length, uint16_t color, uint8_t rotflag);
	void drawVerticalLine(uint8_t x, uint8_t y, uint8_t length, uint16_t color);
	void drawHorizontalLine(uint8_t x, uint8_t y, uint8_t length, uint16_t color);
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	void fillCircle(uint8_t x0, uint8_t y0, uint8_t r, uint16_t color);
	void drawCircle(uint8_t x0, uint8_t y0, uint8_t r, uint16_t color);
	uint8_t getRotation();
	void setRotation(uint8_t m);
	void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
	void drawChar_th(uint8_t x, uint8_t y, char c, uint16_t color);
	void drawChar(uint8_t x, uint8_t y, char c, uint16_t color, uint8_t size);
	void drawString(uint8_t x, uint8_t y, char *c, uint16_t color, uint8_t size);
	void Printstr(uint8_t x, uint8_t y, char *c, uint16_t color);
	unsigned char up_state(unsigned char c1, unsigned char c2);
	unsigned char conv_to_uchar(char x);
	void showpic(const uint16_t *pic, uint8_t org_x, uint8_t org_y, uint8_t width, uint8_t high);
};
#endif
