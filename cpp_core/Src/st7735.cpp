/* vim: set ai et ts=4 sw=4: */
#include "stm32f4xx_hal.h"
#include "st7735.hpp"
#include "string.h"

#define DELAY 0x80

static uint8_t init_cmds3[] =
    {                       // Init for 7735R, part 3 (red or green tab)
        4,                  //  4 commands in list:
        ST7735_GMCTRP1, 16, //  1: Gamma Adjustments (pos. polarity), 16 args, no delay:
        0x02, 0x1c, 0x07, 0x12,
        0x37, 0x32, 0x29, 0x2d,
        0x29, 0x25, 0x2B, 0x39,
        0x00, 0x01, 0x03, 0x10,
        ST7735_GMCTRN1, 16, //  2: Gamma Adjustments (neg. polarity), 16 args, no delay:
        0x03, 0x1d, 0x07, 0x06,
        0x2E, 0x2C, 0x29, 0x2D,
        0x2E, 0x2E, 0x37, 0x3F,
        0x00, 0x00, 0x02, 0x10,
        ST7735_NORON, DELAY,  //  3: Normal display on, no args, w/delay
        10,                   //     10 ms delay
        ST7735_DISPON, DELAY, //  4: Main screen turn on, no args w/delay
        100};                 //     100 ms delay

uint8_t *init_cmds1(DisplayType *dt)
{

  static uint8_t cmds[] = {                       // Init for 7735R, part 1 (red or green tab)
                           15,                    // 15 commands in list:
                           ST7735_SWRESET, DELAY, //  1: Software reset, 0 args, w/delay
                           150,                   //     150 ms delay
                           ST7735_SLPOUT, DELAY,  //  2: Out of sleep mode, 0 args, w/delay
                           255,                   //     500 ms delay
                           ST7735_FRMCTR1, 3,     //  3: Frame rate ctrl - normal mode, 3 args:
                           0x01, 0x2C, 0x2D,      //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
                           ST7735_FRMCTR2, 3,     //  4: Frame rate control - idle mode, 3 args:
                           0x01, 0x2C, 0x2D,      //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
                           ST7735_FRMCTR3, 6,     //  5: Frame rate ctrl - partial mode, 6 args:
                           0x01, 0x2C, 0x2D,      //     Dot inversion mode
                           0x01, 0x2C, 0x2D,      //     Line inversion mode
                           ST7735_INVCTR, 1,      //  6: Display inversion ctrl, 1 arg, no delay:
                           0x07,                  //     No inversion
                           ST7735_PWCTR1, 3,      //  7: Power control, 3 args, no delay:
                           0xA2,
                           0x02,             //     -4.6V
                           0x84,             //     AUTO mode
                           ST7735_PWCTR2, 1, //  8: Power control, 1 arg, no delay:
                           0xC5,             //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
                           ST7735_PWCTR3, 2, //  9: Power control, 2 args, no delay:
                           0x0A,             //     Opamp current small
                           0x00,             //     Boost frequency
                           ST7735_PWCTR4, 2, // 10: Power control, 2 args, no delay:
                           0x8A,             //     BCLK/2, Opamp current small & Medium low
                           0x2A,
                           ST7735_PWCTR5, 2, // 11: Power control, 2 args, no delay:
                           0x8A, 0xEE,
                           ST7735_VMCTR1, 1, // 12: Power control, 1 arg, no delay:
                           0x0E,
                           ST7735_INVOFF, 0, // 13: Don't invert display, no args, no delay
                           ST7735_MADCTL, 1, // 14: Memory access control (directions), 1 arg:
                           dt->rotation,     //     row addr/col addr, bottom to top refresh
                           ST7735_COLMOD, 1, // 15: set color mode, 1 arg, no delay:
                           0x05};            //     16-bit color
  return cmds;
}

uint8_t *init_cmds2(DisplayType *dt)
{
  static uint8_t cmds[] = {                       // Init for 7735R, part 2 (1.44" display)
                           2,                     //  2 commands in list:
                           ST7735_CASET, 4,       //  1: Column addr set, 4 args, no delay:
                           0x00, 0x00,            //     XSTART = 0
                           0x00, dt->width - 1,   //     XEND = 127
                           ST7735_RASET, 4,       //  2: Row addr set, 4 args, no delay:
                           0x00, 0x00,            //     XSTART = 0
                           0x00, dt->height - 1}; //     XEND = 159

  static uint8_t cmds_inverted[] = {                     // Init for 7735R, part 2 (1.44" display)
                                    3,                   //  2 commands in list:
                                    ST7735_CASET, 4,     //  1: Column addr set, 4 args, no delay:
                                    0x00, 0x00,          //     XSTART = 0
                                    0x00, dt->width - 1, //     XEND = 127
                                    ST7735_RASET, 4,     //  2: Row addr set, 4 args, no delay:
                                    0x00, 0x00,          //     XSTART = 0
                                    0x00, dt->height - 1,
                                    ST7735_INVON, 0}; //     XEND = 159

  return (dt->need_color_inversion) ? cmds_inverted : cmds;
}

ST7735::ST7735(DisplayType *dt, SPI_HandleTypeDef *spi,
               uint16_t res_pin, uint16_t cs_pin, uint16_t dc_pin,
               GPIO_TypeDef *res_port, GPIO_TypeDef *cs_port, GPIO_TypeDef *dc_port)
{
  this->dt = dt;
  this->spi = spi;
  this->res_pin = res_pin;
  this->cs_pin = cs_pin;
  this->dc_pin = dc_pin;
  this->res_port = res_port;
  this->cs_port = cs_port;
  this->dc_port = dc_port;
};

void ST7735::select()
{
  HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
}

void ST7735::unselect()
{
  HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
}

void ST7735::reset()
{
  HAL_GPIO_WritePin(res_port, res_pin, GPIO_PIN_RESET);
  HAL_Delay(5);
  HAL_GPIO_WritePin(res_port, res_pin, GPIO_PIN_SET);
}

void ST7735::writeCommand(uint8_t cmd)
{
  HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(spi, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}

void ST7735::writeData(uint8_t *buff, size_t buff_size)
{
  HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_SET);
  HAL_SPI_Transmit(spi, buff, buff_size, HAL_MAX_DELAY);
}

void ST7735::executeCommandList(uint8_t *addr)
{
  uint8_t numCommands, numArgs;
  uint16_t ms;

  numCommands = *addr++;
  while (numCommands--)
  {
    uint8_t cmd = *addr++;
    writeCommand(cmd);

    numArgs = *addr++;
    // If high bit set, delay follows args
    ms = numArgs & DELAY;
    numArgs &= ~DELAY;
    if (numArgs)
    {
      writeData((uint8_t *)addr, numArgs);
      addr += numArgs;
    }

    if (ms)
    {
      ms = *addr++;
      if (ms == 255)
        ms = 500;
      HAL_Delay(ms);
    }
  }
}

void ST7735::setAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  // column address set
  writeCommand(ST7735_CASET);
  uint8_t data[] = {0x00, x0 + dt->x_start, 0x00, x1 + dt->x_start};
  writeData(data, sizeof(data));

  // row address set
  writeCommand(ST7735_RASET);
  data[1] = y0 + dt->y_start;
  data[3] = y1 + dt->y_start;
  writeData(data, sizeof(data));

  // write to RAM
  writeCommand(ST7735_RAMWR);
}

void ST7735::init()
{
  select();
  reset();
  executeCommandList(init_cmds1(dt));
  executeCommandList(init_cmds2(dt));
  executeCommandList(init_cmds3);
  unselect();
}

void ST7735::drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
  if ((x >= dt->width) || (y >= dt->height))
    return;

  select();

  setAddressWindow(x, y, x + 1, y + 1);
  uint8_t data[] = {color >> 8, color & 0xFF};
  writeData(data, sizeof(data));

  unselect();
}

void ST7735::writeChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
  uint32_t i, b, j;

  setAddressWindow(x, y, x + font.width - 1, y + font.height - 1);

  for (i = 0; i < font.height; i++)
  {
    b = font.data[(ch - 32) * font.height + i];
    for (j = 0; j < font.width; j++)
    {
      if ((b << j) & 0x8000)
      {
        uint8_t data[] = {color >> 8, color & 0xFF};
        writeData(data, sizeof(data));
      }
      else
      {
        uint8_t data[] = {bgcolor >> 8, bgcolor & 0xFF};
        writeData(data, sizeof(data));
      }
    }
  }
}

void ST7735::writeString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor)
{
  select();

  while (*str)
  {
    if (x + font.width >= dt->width)
    {
      x = 0;
      y += font.height;
      if (y + font.height >= dt->height)
      {
        break;
      }

      if (*str == ' ')
      {
        // skip spaces in the beginning of the new line
        str++;
        continue;
      }
    }

    writeChar(x, y, *str, font, color, bgcolor);
    x += font.width;
    str++;
  }

  unselect();
}

void ST7735::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  // clipping
  if ((x >= dt->width) || (y >= dt->height))
    return;
  if ((x + w - 1) >= dt->width)
    w = dt->width - x;
  if ((y + h - 1) >= dt->height)
    h = dt->height - y;

  select();
  setAddressWindow(x, y, x + w - 1, y + h - 1);

  uint8_t data[] = {color >> 8, color & 0xFF};
  HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_SET);
  for (y = h; y > 0; y--)
  {
    for (x = w; x > 0; x--)
    {
      HAL_SPI_Transmit(spi, data, sizeof(data), HAL_MAX_DELAY);
    }
  }

  unselect();
}

void ST7735::fillRectangleFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  // clipping
  if ((x >= dt->width) || (y >= dt->height))
    return;
  if ((x + w - 1) >= dt->width)
    w = dt->width - x;
  if ((y + h - 1) >= dt->height)
    h = dt->height - y;

  select();
  setAddressWindow(x, y, x + w - 1, y + h - 1);

  // Prepare whole line in a single buffer
  uint8_t pixel[] = {color >> 8, color & 0xFF};
  uint8_t line[(w * sizeof(pixel))];
  for (x = 0; x < w; ++x)
    memcpy(line + x * sizeof(pixel), pixel, sizeof(pixel));

  HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_SET);
  for (y = h; y > 0; y--)
    HAL_SPI_Transmit(spi, line, w * sizeof(pixel), HAL_MAX_DELAY);

  delete line;
  unselect();
}

void ST7735::fillScreen(uint16_t color)
{
  fillRectangle(0, 0, dt->width, dt->height, color);
}

void ST7735::fillScreenFast(uint16_t color)
{
  fillRectangleFast(0, 0, dt->width, dt->height, color);
}

void ST7735::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
{
  if ((x >= dt->width) || (y >= dt->height))
    return;
  if ((x + w - 1) >= dt->width)
    return;
  if ((y + h - 1) >= dt->height)
    return;

  select();
  setAddressWindow(x, y, x + w - 1, y + h - 1);
  writeData((uint8_t *)data, sizeof(uint16_t) * w * h);
  unselect();
}

void ST7735::invertColors(bool invert)
{
  select();
  writeCommand(invert ? ST7735_INVON : ST7735_INVOFF);
  unselect();
}

void ST7735::setGamma(GammaDef gamma)
{
  select();
  writeCommand(ST7735_GAMSET);
  writeData((uint8_t *)&gamma, sizeof(gamma));
  unselect();
}
