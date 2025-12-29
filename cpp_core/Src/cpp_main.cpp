#include "cpp_main.hpp"
#include <testimg.hpp>

extern "C" int cpp_main(SPI_HandleTypeDef *spi)
{
    auto dt = display_types::Ali_left_160_128::instance();
    auto display = ST7735(dt, spi, TFT_RST_Pin, TFT_CS_Pin, TFT_DC_Pin, TFT_RST_GPIO_Port, TFT_CS_GPIO_Port, TFT_DC_GPIO_Port);

    display.init();
    display.fillScreenFast(ST7735_WHITE);
    display.drawPixel(20, 20, ST7735_RED);
    display.drawPixel(21, 21, ST7735_RED);
    display.drawPixel(20, 21, ST7735_RED);
    display.drawPixel(21, 20, ST7735_RED);
    display.fillRectangle(20,20,20,20,ST7735_BLUE);
    display.writeString(0,0,"dskjfdslk", Font_11x18, ST7735_BLACK, ST7735_WHITE);

    for (;;)
    {
    }
}