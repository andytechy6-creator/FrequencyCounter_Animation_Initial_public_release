#ifndef _GFXFONT_H_
#define _GFXFONT_H_

#include <stdint.h>

typedef struct {
    uint16_t bitmapOffset; // Pointer into GFXfont->bitmap
    uint8_t  width;        // Bitmap dimensions in pixels
    uint8_t  height;
    uint8_t  xAdvance;     // Distance to advance cursor (x axis)
    int8_t   xOffset;      // X dist from cursor pos to UL corner
    int8_t   yOffset;      // Y dist from cursor pos to UL corner
} GFXglyph;

typedef struct {
    const uint8_t  *bitmap; // Glyph bitmaps
    const GFXglyph *glyph;  // Glyph array
    uint8_t   first;        // ASCII extents (first char)
    uint8_t   last;         // ASCII extents (last char)
    uint8_t   yAdvance;     // Line spacing
} GFXfont;

#endif
