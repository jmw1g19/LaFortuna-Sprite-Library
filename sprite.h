/* Author: Joshua Wardle
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */

#include <avr/io.h>
#include <stdint.h>
#include "./lcd/lcd.h"

typedef struct{
    uint16_t x, y;
    uint16_t pixelSize;
    palette colours;
    uint16_t pixels[];
} sprite;

typedef struct{
    uint16_t col1, col2, col3, col4, col5, col6, col7, col8;
} palette;

void drawSprite(sprite s);

void eraseSprite(sprite s);

void moveSprite(sprite s, uint16_t x, uint16_t y);

int areColliding(sprite s1, sprite s2);