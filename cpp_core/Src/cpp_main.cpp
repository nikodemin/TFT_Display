#include "cpp_main.hpp"

extern "C" int cpp_main(SPI_HandleTypeDef *spi)
{
    auto dt = display_types::Ali_left_160_128::instance();
    auto display = ST7735(dt, spi, TFT_RST_Pin, TFT_CS_Pin, TFT_DC_Pin, TFT_RST_GPIO_Port, TFT_CS_GPIO_Port, TFT_DC_GPIO_Port);

    display.init();
    display.fillScreenFast(ST7735_MAGENTA);
    display.writeString(100, 0, "Hello world!", Font_7x10, ST7735_BLACK, ST7735_WHITE);

    for (;;)
    {
    }
}