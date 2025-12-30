#include "cpp_main.hpp"
#include <testimg.hpp>

extern "C" int cpp_main(SPI_HandleTypeDef *spi)
{
    auto dt = display_types::Ali_left_160_128::instance();
    auto display = ST7735(dt, spi, TFT_RST_Pin, TFT_CS_Pin, TFT_DC_Pin, TFT_RST_GPIO_Port, TFT_CS_GPIO_Port, TFT_DC_GPIO_Port);

    display.init();
    display.fillScreenFast(ST7735_WHITE);
    display.drawLine(80,64,0,0, ST7735_BLUE);
    display.drawLine(80,64,160,128, ST7735_GREEN);

    for (;;)
    {
    }
}