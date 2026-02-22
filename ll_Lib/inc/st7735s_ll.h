/*
 * st7735s_ll.h
 *
 *  Created on: Feb 15, 2026
 *      Author: andyx
 */

#ifndef INC_ST7735S_LL_H_
#define INC_ST7735S_LL_H_

#include "main.h"
#include <stdint.h>
#include <stdbool.h>
#include "fonts.h"
#include "picts.h"
#include "gfxfont.h"
// --- Panel config: 160x80 "mini China" ---

//this is correct
#if 1
#define ST7735_WIDTH   160
#define ST7735_HEIGHT   80
#define ST7735_XSTART    1
#define ST7735_YSTART   26
#endif

// this is wrong
#if 0
#define ST7735_WIDTH   80
#define ST7735_HEIGHT 160
#define ST7735_YSTART  26
#define ST7735_XSTART   1
#endif
// Color definitions
#define ST7735_BLACK   0x0000
#define ST7735_BLUE    0x001F
#define ST7735_RED     0xF800
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF

// Public API
void ST7735_Init(void);
void ST7735_SetRotation(uint8_t rot);

void ST7735_FillScreen(uint16_t color);
void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color);
void ST7735_DrawLine(int x0, int y0, int x1, int y1, uint16_t color);
void ST7735_DrawFastHLine(int x, int y, int w, uint16_t color);
void ST7735_FillRect(int x, int y, int w, int h, uint16_t color);
void ST7735_DrawRGBBitmap(int16_t x, int16_t y, const tImage_RGB *image);
void ST7735_DrawBitmapMonoBG(int x, int y, const tImage *img, uint16_t fg, uint16_t bg);
void ST7735_DrawBitmapMonoTransparent(int x, int y, const tImage *img, uint16_t fg);
void ST7735_DrawString(const char *str, int x, int y, const tFont *font, uint16_t fg, uint16_t bg);
void ST7735_WriteDataDMA(const uint8_t *buf, uint32_t len);
void DrawChar_GFX(int x, int y, char c, const GFXfont *font, uint16_t color, uint16_t bg);
void DrawString_GFX(int x, int y, const char *str, const GFXfont *font, uint16_t color, uint16_t bg);

#endif /* INC_ST7735S_LL_H_ */
