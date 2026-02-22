#include "st7735s_ll.h"
#include "delay.h"
#include "string.h"
#include <stdlib.h>



// --- Command defines (same as original lib) ---
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_NORON   0x13
#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_VSCSAD  0x37
#define ST7735_SCRLAR  0x33

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// MADCTL bits
#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
//#define ST7735_MADCTL_RGB 0x00
//#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_RGB 0x08
//#define ST7735_MADCTL_BGR 0xA0
// --- GPIO mapping (your wiring) ---
#define ST7735_RES_PORT   GPIOB
#define ST7735_RES_PIN    LL_GPIO_PIN_4

#define ST7735_CS_PORT    GPIOA
#define ST7735_CS_PIN     LL_GPIO_PIN_15

#define ST7735_DC_PORT    GPIOB
#define ST7735_DC_PIN     LL_GPIO_PIN_6

#define ST7735_BL_PORT    GPIOA
#define ST7735_BL_PIN     LL_GPIO_PIN_6   // driven by TIM3_CH1, but we can force ON via GPIO mode if needed

static uint8_t _width  = ST7735_WIDTH;
static uint8_t _height = ST7735_HEIGHT;
static uint8_t _xstart = ST7735_XSTART;
static uint8_t _ystart = ST7735_YSTART;

// --- Low-level helpers ---

static void ST7735_Select(void)   { LL_GPIO_ResetOutputPin(ST7735_CS_PORT, ST7735_CS_PIN); }
static void ST7735_Unselect(void) { LL_GPIO_SetOutputPin(ST7735_CS_PORT, ST7735_CS_PIN); }

static void ST7735_DC_Command(void) { LL_GPIO_ResetOutputPin(ST7735_DC_PORT, ST7735_DC_PIN); }
static void ST7735_DC_Data(void)    { LL_GPIO_SetOutputPin(ST7735_DC_PORT, ST7735_DC_PIN); }

static void ST7735_ResetHW(void)
{
    LL_GPIO_ResetOutputPin(ST7735_RES_PORT, ST7735_RES_PIN);
    delay_ms(10);
    LL_GPIO_SetOutputPin(ST7735_RES_PORT, ST7735_RES_PIN);
    delay_ms(10);
}

static void ST7735_WriteSPI(const uint8_t *data, uint16_t size)
{
    while (size--) {
        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData8(SPI1, *data++);
    }
    while (LL_SPI_IsActiveFlag_BSY(SPI1));
}

static void ST7735_WriteCommand(uint8_t cmd)
{
    ST7735_DC_Command();
    ST7735_WriteSPI(&cmd, 1);
}

static void ST7735_WriteData(const uint8_t *data, uint16_t size)
{
    ST7735_DC_Data();
    ST7735_WriteSPI(data, size);
}


#if 1
void ST7735_SetAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    x0 += ST7735_XSTART;
    x1 += ST7735_XSTART;
    y0 += ST7735_YSTART;
    y1 += ST7735_YSTART;

    ST7735_WriteCommand(0x2A);
    uint8_t caset[] = {0x00, x0, 0x00, x1};
    ST7735_WriteData(caset, 4);

    ST7735_WriteCommand(0x2B);
    uint8_t raset[] = {0x00, y0, 0x00, y1};
    ST7735_WriteData(raset, 4);

    ST7735_WriteCommand(0x2C);
}
#endif


#if 1
static void ST7735_InitSequence(void)
{
    ST7735_Select();
    ST7735_ResetHW();

    ST7735_WriteCommand(ST7735_SWRESET);
    delay_ms(150);

    ST7735_WriteCommand(ST7735_SLPOUT);
    delay_ms(120);

    uint8_t data1[] = { 0x01, 0x2C, 0x2D };
    ST7735_WriteCommand(ST7735_FRMCTR1);
    ST7735_WriteData(data1, 3);

    ST7735_WriteCommand(ST7735_FRMCTR2);
    ST7735_WriteData(data1, 3);

    uint8_t data2[] = { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D };
    ST7735_WriteCommand(ST7735_FRMCTR3);
    ST7735_WriteData(data2, 6);

    uint8_t invctr = 0x07;
    ST7735_WriteCommand(ST7735_INVCTR);
    ST7735_WriteData(&invctr, 1);

    uint8_t pwctr1[] = { 0xA2, 0x02, 0x84 };
    ST7735_WriteCommand(ST7735_PWCTR1);
    ST7735_WriteData(pwctr1, 3);

    uint8_t pwctr2 = 0xC5;
    ST7735_WriteCommand(ST7735_PWCTR2);
    ST7735_WriteData(&pwctr2, 1);

    uint8_t pwctr3[] = { 0x0A, 0x00 };
    ST7735_WriteCommand(ST7735_PWCTR3);
    ST7735_WriteData(pwctr3, 2);

    uint8_t pwctr4[] = { 0x8A, 0x2A };
    ST7735_WriteCommand(ST7735_PWCTR4);
    ST7735_WriteData(pwctr4, 2);

    uint8_t pwctr5[] = { 0x8A, 0xEE };
    ST7735_WriteCommand(ST7735_PWCTR5);
    ST7735_WriteData(pwctr5, 2);

    uint8_t vmctr1 = 0x0E;
    ST7735_WriteCommand(ST7735_VMCTR1);
    ST7735_WriteData(&vmctr1, 1);

    //ST7735_WriteCommand(ST7735_INVOFF);
    ST7735_WriteCommand(ST7735_INVON);

    uint8_t colmod = 0x05; // 16-bit color
    ST7735_WriteCommand(ST7735_COLMOD);
    ST7735_WriteData(&colmod, 1);
    delay_ms(10);

    uint8_t madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
    ST7735_WriteCommand(ST7735_MADCTL);
    ST7735_WriteData(&madctl, 1);



    // Column/row set for 160x80 mini
    uint8_t caset[] = { 0x00, 0x00, 0x00, 0x4F }; // 0..79
    uint8_t raset[] = { 0x00, 0x00, 0x00, 0x9F }; // 0..159
    //uint8_t raset[] = { 0x00, 0x18, 0x00, 0xB7 }; // 24..183

    ST7735_WriteCommand(ST7735_CASET);
    ST7735_WriteData(caset, 4);
    ST7735_WriteCommand(ST7735_RASET);
    ST7735_WriteData(raset, 4);

    ST7735_WriteCommand(ST7735_NORON);
    delay_ms(10);

    ST7735_WriteCommand(ST7735_DISPON);
    delay_ms(100);

    ST7735_Unselect();
}
#endif
// --- Public API ---

void ST7735_Init(void)
{
    // Assume GPIO + SPI1 already configured by CubeMX (LL)
    // Ensure CS, DC, RES, BL are outputs and default states
    LL_GPIO_SetOutputPin(ST7735_CS_PORT, ST7735_CS_PIN);
    LL_GPIO_SetOutputPin(ST7735_DC_PORT, ST7735_DC_PIN);
    LL_GPIO_SetOutputPin(ST7735_RES_PORT, ST7735_RES_PIN);

    // Backlight ON (if PA6 is GPIO; if it's AF for TIM3, PWM will drive it)
    // If needed, you can force it as GPIO output and set high.
    // LL_GPIO_SetOutputPin(ST7735_BL_PORT, ST7735_BL_PIN);

    ST7735_InitSequence();
    ST7735_FillScreen(ST7735_BLACK);
}

void ST7735_SetRotation(uint8_t rot)
{
    uint8_t madctl = 0x08;
    switch (rot & 3) {



#if 1
    case 0:
        madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
        _width  = ST7735_WIDTH;
        _height = ST7735_HEIGHT;
        _xstart = ST7735_XSTART;
        _ystart = ST7735_YSTART;
        break;
#endif
    case 1:
        madctl = ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
        _width  = ST7735_HEIGHT;
        _height = ST7735_WIDTH;
        _xstart = ST7735_YSTART;
        _ystart = ST7735_XSTART;
        break;
    case 2:
        madctl = ST7735_MADCTL_RGB;
        _width  = ST7735_WIDTH;
        _height = ST7735_HEIGHT;
        _xstart = ST7735_XSTART;
        _ystart = ST7735_YSTART;
        break;
    case 3:
        madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
        _width  = ST7735_HEIGHT;
        _height = ST7735_WIDTH;
        _xstart = ST7735_YSTART;
        _ystart = ST7735_XSTART;
        break;
    }

    ST7735_Select();
    ST7735_WriteCommand(ST7735_MADCTL);
    ST7735_WriteData(&madctl, 1);
    ST7735_Unselect();
}

void ST7735_FillScreen(uint16_t color)
{
    ST7735_Select();
    ST7735_SetAddrWindow(0, 0, _width - 1, _height - 1);

    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;
    uint8_t buf[32];
    for (int i = 0; i < 32; i += 2) {
        buf[i]   = hi;
        buf[i+1] = lo;
    }

    uint32_t total = (uint32_t)_width * _height;
    while (total) {
        uint16_t chunk = (total > 16) ? 16 : total;
        ST7735_WriteData(buf, chunk * 2);
        total -= chunk;
    }

    ST7735_Unselect();
}


#if 1
void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color)
{
    if (x < 0 || y < 0 || x >= _width || y >= _height)
        return;

    ST7735_Select();
    ST7735_SetAddrWindow(x, y, x, y);
    uint8_t data[2] = { color >> 8, color & 0xFF };
    ST7735_WriteData(data, 2);
    ST7735_Unselect();
}


void ST7735_DrawLine(int x0, int y0, int x1, int y1, uint16_t color)
{
    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;  // error term

    while (1)
    {
        ST7735_DrawPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void ST7735_DrawFastHLine(int x, int y, int w, uint16_t color)
{
    if (y < 0 || y >= _height || w <= 0) return;
    if (x < 0) { w += x; x = 0; }
    if (x + w > _width) w = _width - x;
    if (w <= 0) return;

    ST7735_Select();
    ST7735_SetAddrWindow(x, y, x + w - 1, y);

    uint8_t d[2] = { color >> 8, color & 0xFF };
    for (int i = 0; i < w; i++)
        ST7735_WriteData(d, 2);

    ST7735_Unselect();
}

#if 0
void ST7735_FillRect(int x, int y, int w, int h, uint16_t color)
{
    if (x >= _width || y >= _height || w <= 0 || h <= 0) return;
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > _width)  w = _width  - x;
    if (y + h > _height) h = _height - y;

    ST7735_Select();
    ST7735_SetAddrWindow(x, y, x + w - 1, y + h - 1);

    // --- Build a DMA buffer ---
    #define DMA_BUF_SIZE 64
    static uint8_t buf[DMA_BUF_SIZE];

    for (int i = 0; i < DMA_BUF_SIZE; i += 2) {
        buf[i]   = color >> 8;
        buf[i+1] = color & 0xFF;
    }

    int total = w * h;
    while (total > 0) {
        int chunk = (total > (DMA_BUF_SIZE/2)) ? (DMA_BUF_SIZE/2) : total;
        ST7735_WriteDataDMA(buf, chunk * 2);
        total -= chunk;
    }

    ST7735_Unselect();
}
#endif
void ST7735_FillRect(int x, int y, int w, int h, uint16_t color)
{
    if (x >= _width || y >= _height || w <= 0 || h <= 0) return;
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > _width)  w = _width  - x;
    if (y + h > _height) h = _height - y;

    ST7735_Select();
    ST7735_SetAddrWindow(x, y, x + w - 1, y + h - 1);

    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;

    // Write pixel-by-pixel (slow but perfect)
    for (int i = 0; i < w * h; i++) {
        uint8_t data[2] = { hi, lo };
        ST7735_WriteData(data, 2);
    }

    ST7735_Unselect();
}


void ST7735_DrawRGBBitmap(int16_t x, int16_t y, const tImage_RGB *image)
{
    uint16_t w = image->width;
    uint16_t h = image->height;

    if (x >= _width || y >= _height)
        return;
    if (x + w > _width)  w = _width  - x;
    if (y + h > _height) h = _height - y;

    ST7735_Select();
    ST7735_SetAddrWindow(x, y, x + w - 1, y + h - 1);
    ST7735_WriteData((const uint8_t*)image->data, w * h * 2);
    ST7735_Unselect();
}
#endif
// --- Text / mono bitmap using your existing font types ---

static const tChar *find_char_by_code(int code, const tFont *font)
{
    int16_t count = font->length;
    int16_t first = 0;
    int16_t last  = count - 1;
    int16_t mid   = 0;

    if (count > 0) {
        if ((code >= font->chars[0].code) && (code <= font->chars[count - 1].code)) {
            while (last >= first) {
                mid = first + ((last - first) / 2);
                if (font->chars[mid].code < code)
                    first = mid + 1;
                else if (font->chars[mid].code > code)
                    last = mid - 1;
                else
                    break;
            }
            if (font->chars[mid].code == code)
                return &font->chars[mid];
        }
    }
    return 0;
}

static int utf8_next_char(const char *str, int16_t start, int16_t *resultCode, int16_t *nextIndex)
{
    uint16_t len = 0;
    uint16_t index = 0;
    *resultCode = 0;

    while (*(str + index) != 0) {
        len++;
        index++;
    }

    uint8_t c;
    uint8_t code = 0;
    int8_t result = 0;
    uint8_t skip = 0;

    *resultCode = 0;
    *nextIndex = -1;

    if (start >= 0 && start < len) {
        index = start;
        while (index < len) {
            c = *(str + index);
            index++;

            if (skip == 0) {
                if ((c & 0xf8) == 0xf0) {
                    skip = 3;
                    code = c;
                } else if ((c & 0xf0) == 0xe0) {
                    skip = 2;
                    code = c;
                } else if ((c & 0xe0) == 0xc0) {
                    skip = 1;
                    code = c;
                } else {
                    skip = 0;
                    code = c;
                }
            } else {
                code = (code << 8) | c;
                skip--;
            }
            if (skip == 0) {
                *resultCode = code;
                *nextIndex = index;
                result = 1;
                break;
            }
        }
    }
    return result;
}

void ST7735_DrawBitmapMonoBG(int x, int y, const tImage *img, uint16_t fg, uint16_t bg)
{
    int w = img->width;
    int h = img->height;
    const uint8_t *data = img->data;

    ST7735_Select();
    ST7735_SetAddrWindow(x, y, x + w - 1, y + h - 1);

    int bitIndex = 0;

    for (int i = 0; i < w * h; i++) {
        uint8_t byte = data[bitIndex >> 3];
        uint8_t mask = 0x80 >> (bitIndex & 7);

        uint16_t c = (byte & mask) ? fg : bg;

        uint8_t out[2] = { c >> 8, c & 0xFF };
        ST7735_WriteData(out, 2);

        bitIndex++;
    }

    ST7735_Unselect();
}
#if 0
void ST7735_DrawBitmapMonoTransparent(int x, int y, const tImage *img, uint16_t fg)
{
    const uint8_t *data = img->data;
    int w = img->width;
    int h = img->height;

    for (int yy = 0; yy < h; yy++)
    {
        for (int xx = 0; xx < w; xx++)
        {
            int bitIndex = yy * w + xx;
            int byteIndex = bitIndex >> 3;
            int bit = 7 - (bitIndex & 7);

            if (data[byteIndex] & (1 << bit))
            {
                ST7735_DrawPixel(x + xx, y + yy, fg);
            }
        }
    }
}
#endif
#if 0
void ST7735_DrawBitmapMonoTransparent(int x, int y, const tImage *img, uint16_t fg)
{
    const uint8_t *data = img->data;
    int w = img->width;
    int h = img->height;

    int bytesPerRow = (w + 7) >> 3;   // ceil(width/8)

    for (int yy = 0; yy < h; yy++)
    {
        const uint8_t *row = data + yy * bytesPerRow;

        for (int xx = 0; xx < w; xx++)
        {
            int byteIndex = xx >> 3;
            int bitIndex  = 7 - (xx & 7);

            if (row[byteIndex] & (1 << bitIndex))
            {
                ST7735_DrawPixel(x + xx, y + yy, fg);
            }
        }
    }
}
#endif
void ST7735_DrawBitmapMonoTransparent(int x, int y, const tImage *img, uint16_t fg)
{
    int w = img->width;
    int h = img->height;
    const uint8_t *data = img->data;

    int bytesPerRow = (w + 7) >> 3;

    ST7735_Select();
    ST7735_SetAddrWindow(x, y, x + w - 1, y + h - 1);

    for (int yy = 0; yy < h; yy++)
    {
        const uint8_t *row = data + yy * bytesPerRow;

        for (int xx = 0; xx < w; xx++)
        {
            int byteIndex = xx >> 3;
            int bitIndex  = 7 - (xx & 7);

            if (row[byteIndex] & (1 << bitIndex))
            {
                uint8_t d[2] = { fg >> 8, fg & 0xFF };
                ST7735_WriteData(d, 2);
            }
            else
            {
                // Transparent pixel: send nothing, but we must still advance the window
                uint8_t dummy[2] = { 0x00, 0x00 }; // or background colour if needed
                ST7735_WriteData(dummy, 2);
            }
        }
    }

    ST7735_Unselect();
}

#if 1
void DrawChar_GFX(int x, int y, char c, const GFXfont *font, uint16_t color, uint16_t bg)
{
    if (c < font->first || c > font->last)
        return;

    c -= font->first;
    const GFXglyph *glyph = &font->glyph[(uint8_t)c];
    const uint8_t *bitmap = font->bitmap;

    uint16_t bo = glyph->bitmapOffset;
    uint8_t w = glyph->width;
    uint8_t h = glyph->height;
    int8_t xo = glyph->xOffset;
    int8_t yo = glyph->yOffset;

    uint8_t bits = 0, bit = 0;

    for (uint8_t yy = 0; yy < h; yy++)
    {
        for (uint8_t xx = 0; xx < w; xx++)
        {
            if (!(bit++ & 7))
                bits = bitmap[bo++];

            uint16_t px = (bits & 0x80) ? color : bg;
            bits <<= 1;

            ST7735_DrawPixel(x + xo + xx, y + yo + yy, px);
        }
    }
}

void DrawString_GFX(int x, int y, const char *str, const GFXfont *font, uint16_t color, uint16_t bg)
{
    int cursorX = x;

    while (*str)
    {
        char c = *str++;

        if (c < font->first || c > font->last)
            continue;

        const GFXglyph *glyph = &font->glyph[c - font->first];
        DrawChar_GFX(cursorX, y, c, font, color, bg);

        cursorX += glyph->xAdvance;
    }
}

#endif


void ST7735_DrawString(const char *str, int x, int y, const tFont *font, uint16_t fg, uint16_t bg)
{
    int16_t len = strlen(str);
    int16_t index = 0;
    int16_t code = 0;
    int16_t x1 = x;
    int16_t nextIndex;

    while (index < len) {
        if (utf8_next_char(str, index, &code, &nextIndex) != 0) {
            const tChar *ch = find_char_by_code(code, font);
            if (ch != 0) {
                // Draw the glyph with foreground + background
                ST7735_DrawBitmapMonoBG(x1, y, ch->image, fg, bg);
                x1 += ch->image->width;
            }
        }
        index = nextIndex;
        if (nextIndex < 0)
            break;
    }
}
#if 0
void ST7735_WriteDataDMA(const uint8_t *buf, uint32_t len)
{
    if (len == 0) return;

    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)buf);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, len);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    while (!LL_DMA_IsActiveFlag_TC3(DMA1)) { }
    LL_DMA_ClearFlag_TC3(DMA1);
}
#endif
#if 0
void ST7735_WriteDataDMA(const uint8_t *buf, uint32_t len)
{
    if (len == 0) return;

    // *** ADD THIS ***
    while (LL_SPI_IsActiveFlag_BSY(SPI1));

    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)buf);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, len);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    while (!LL_DMA_IsActiveFlag_TC3(DMA1)) { }
    LL_DMA_ClearFlag_TC3(DMA1);

    // *** AND THIS ***
    while (LL_SPI_IsActiveFlag_BSY(SPI1));
}
#endif

#if 1
void ST7735_WriteDataDMA(const uint8_t *buf, uint32_t len)
{
    if (len == 0) return;

    // *** WAIT FOR SPI TO BE COMPLETELY IDLE ***
    while (!LL_SPI_IsActiveFlag_TXE(SPI1));
    while (LL_SPI_IsActiveFlag_BSY(SPI1));

    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)buf);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, len);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    while (!LL_DMA_IsActiveFlag_TC3(DMA1)) {}
    LL_DMA_ClearFlag_TC3(DMA1);

    // *** WAIT AGAIN AFTER DMA ***
    while (!LL_SPI_IsActiveFlag_TXE(SPI1));
    while (LL_SPI_IsActiveFlag_BSY(SPI1));
}

#endif
