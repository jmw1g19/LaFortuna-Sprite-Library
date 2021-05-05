/* Author: Joshua Wardle
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */

#include <avr/io.h>
#include <stdint.h>
#include "./lcd/lcd.h"

typedef enum {fixed, collider, trigger} type;

typedef struct{
    volatile uint16_t x, y;
    int pixelCount;
    int pixelsPerRow;
    uint16_t pixelSize;
    float gravity;
    type spriteType;
} sprite;

typedef struct{
    int currentFrame;
    int frameCount;
    int * frames[32];
} animation;

typedef enum {loop, stop_on_end} animationProperty;

void drawSprite(sprite s, int colours[], uint16_t palette[]);

void eraseSprite(sprite s);

sprite moveSprite(sprite s, int colours[], int x, int y, uint16_t palette[]);

int areColliding(sprite s1, sprite s2);

sprite createSprite(uint16_t x, uint16_t y, int pixelCount, int pixelsPerRow, uint16_t pixelSize, int colours[], uint16_t palette[], type spriteType);

sprite applyGravityToSprite(sprite s, int colours[], uint16_t palette[]);

sprite setSpriteGravity(sprite s, float g);

sprite changeSpriteGravity(sprite s, float g);

int areTriggering(sprite s1, sprite s2, void(*function)());

sprite rescaleSprite(sprite s, int delta, int colours[], uint16_t palette);

animation createAnimation(int frameCount, int * frames[]);

sprite moveAnimatedSprite(sprite s, animation a, int x, int y, uint16_t palette[], animationProperty property);

sprite applyGravityToAnimatedSprite(sprite s, animation a, uint16_t palette[]);