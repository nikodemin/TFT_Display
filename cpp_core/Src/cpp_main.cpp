#include "cpp_main.hpp"
#include <testimg.hpp>

extern "C" int cpp_main(SPI_HandleTypeDef *spi)
{
    auto dt = display_types::Ali_left_160_128::instance();
    auto display = ST7735(dt, spi, TFT_RST_Pin, TFT_CS_Pin, TFT_DC_Pin, TFT_RST_GPIO_Port, TFT_CS_GPIO_Port, TFT_DC_GPIO_Port);

    display.init();
    display.fillScreenFast(ST7735_WHITE);
    display.drawHLine(50, 100, 20, ST7735_BLUE);
    display.drawHLine(50, 100, 120, ST7735_GREEN);
    display.drawVLine(20, 120, 50, ST7735_MAGENTA);
    display.drawVLine(20, 120, 100, ST7735_YELLOW);

    display.fillCircle(80, 64, 40, ST7735_BLUE);

    for (;;)
    {
    }
}