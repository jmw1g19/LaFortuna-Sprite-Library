/* Author: Joshua Wardle
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */

#include <avr/io.h>
#include <stdint.h>
#include "./lcd/lcd.h"

typedef struct{
    volatile uint16_t x, y;
    int pixelCount;
    int pixelsPerRow;
    uint16_t pixelSize;
} sprite;

void drawSprite(sprite s, uint16_t colours[]);

void eraseSprite(sprite s);

sprite moveSprite(sprite s, uint16_t colours[], uint16_t x, uint16_t y);

int areColliding(sprite s1, sprite s2);