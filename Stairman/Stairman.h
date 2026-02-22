/*
 * Stairman.h
 *
 *  Created on: Feb 18, 2026
 *      Author: andyx
 */

#ifndef STAIRMAN_H_
#define STAIRMAN_H_


#include <stdint.h>

typedef struct {
    const uint8_t *data;
    uint16_t width;
    uint16_t height;
    uint8_t dataSize;
} tImage;

// Declare all 28 frames
extern const tImage stairman1;
extern const tImage stairman2;
extern const tImage stairman3;
extern const tImage stairman4;
extern const tImage stairman5;
extern const tImage stairman6;
extern const tImage stairman7;
extern const tImage stairman8;
extern const tImage stairman9;
extern const tImage stairman10;
extern const tImage stairman11;
extern const tImage stairman12;
extern const tImage stairman13;
extern const tImage stairman14;
extern const tImage stairman15;
extern const tImage stairman16;
extern const tImage stairman17;
extern const tImage stairman18;
extern const tImage stairman19;
extern const tImage stairman20;
extern const tImage stairman21;
extern const tImage stairman22;
extern const tImage stairman23;
extern const tImage stairman24;
extern const tImage stairman25;
extern const tImage stairman26;
extern const tImage stairman27;
extern const tImage stairman28;
extern const tImage stairmanfront;
// Pointer table for animation
extern const tImage* StairmanFrames[29];




#endif /* STAIRMAN_H_ */
