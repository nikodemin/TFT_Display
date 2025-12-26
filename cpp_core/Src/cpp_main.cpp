#include "cpp_main.hpp"

extern "C" int cpp_main(SPI_HandleTypeDef spi)
{
    ST7735_Init();
    ST7735_FillScreen(ST7735_GREEN);
    ST7735_FillRectangle(0, 0, 50, 50, ST7735_WHITE);
    ST7735_WriteString(100, 0, "Hello world!", Font_7x10, ST7735_BLACK, ST7735_WHITE);

    for (;;){}
}