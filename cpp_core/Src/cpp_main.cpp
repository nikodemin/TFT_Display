#include "cpp_main.hpp"

extern "C" int cpp_main(SPI_HandleTypeDef spi) 
{
    TEE_ST7735 display = TEE_ST7735(TFT_RST_Pin, TFT_CS_Pin, TFT_DC_Pin, *TFT_RST_GPIO_Port, *TFT_CS_GPIO_Port, *TFT_DC_GPIO_Port, spi);

    display.init(true);
    display.drawChar(100,100,'a', GREEN, 3);
    for (;;)
    {
    }
}