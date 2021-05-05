/* Author: Joshua Wardle
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */

#include "sprite.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

/* Draws a sprite to the screen given the palette and pixel colours. */
void drawSprite(sprite s, int colours[], uint16_t palette[]){
    uint16_t drawX, drawY;
    drawX = s.x; drawY = s.y;
    int i;

    for(i = 0; i < s.pixelCount; ++i ){
        if(i % s.pixelsPerRow == 0 && i != 0) { drawX = s.x; drawY = drawY + s.pixelSize; }

        rectangle r;
        r.top = drawY; r.bottom = drawY + s.pixelSize;
        r.left = drawX; r.right = drawX + s.pixelSize;

        fill_rectangle(r, palette[colours[i]]);
        drawX = drawX + s.pixelSize;
    }
} 

/* Remove a sprite from the screen. You should avoid calling this directly. */
void eraseSprite(sprite s){
    int rows = s.pixelCount / s.pixelsPerRow;
    rectangle r;
    r.top = s.y; r.bottom = s.y + (s.pixelSize * rows);
    r.left = s.x; r.right = s.x + (fmin(s.pixelCount, s.pixelsPerRow) * s.pixelSize);

    fill_rectangle(r, BLACK);
}

/* Moves a sprite by the supplied offset and draws it to screen. The updated sprite is returned. */
sprite moveSprite(sprite s, int colours[], int x, int y, uint16_t palette[]){
    int rows = s.pixelCount / s.pixelsPerRow;
    int erased = 0;
    int absX, absY; absX = x; absY = y;

    if(x < 0) {absX = x * -1;} if(y < 0) {absY = y * -1;}
    if((absX > (s.pixelsPerRow * s.pixelSize)) || absY > (rows * s.pixelSize)) { eraseSprite(s); erased = 1; }
    
    if(erased == 0) { 
        rectangle r1;
        rectangle r2;

        if(y == 0) { }
        else if(y > 0){
            r1.top = s.y; r1.bottom = s.y + y;
            r1.left = s.x; r1.right = s.x + (s.pixelCount * s.pixelsPerRow);
        }
        else if (y < 0){
            int oldBottom = s.y + (rows * s.pixelSize);
            int newBottom = s.y + y + (rows * s.pixelSize);
            r1.top = newBottom; r1.bottom = oldBottom;
            r1.left = s.x; r1.right = s.x + (s.pixelCount * s.pixelsPerRow);
        }

        fill_rectangle(r1, BLACK);

        if(x >= 0){
            r2.left = s.x; r2.right = s.x + x;
            r2.top = s.y; r2.bottom = s.y + (rows * s.pixelSize);
        }
        else if(x < 0){
           r2.right = s.x + (s.pixelsPerRow * s.pixelSize); r2.left = r2.right + x;
           r2.top = s.y; r2.bottom = s.y + (rows * s.pixelSize);
        }
    
        fill_rectangle(r2, BLACK);        
    }

    s.x = s.x + x;
    s.y = s.y + y;
    drawSprite(s, colours, palette);
    return s;
}

/* Calculates if two sprites are colliding. Returns 1 if true, and 0 if false.
   Both sprite types must a 'collider' or 'trigger'. */
int areColliding(sprite s1, sprite s2){
    int s1endingX = s1.x + s1.pixelsPerRow*s1.pixelSize;
    int s2endingX = s2.x + s2.pixelsPerRow*s2.pixelSize;

    int s1rows = s1.pixelCount / s1.pixelsPerRow;
    int s2rows = s2.pixelCount / s2.pixelsPerRow;
    int s1endingY = s1.y + s1.pixelSize*s1rows;
    int s2endingY = s2.y + s2.pixelSize*s2rows;

    int collidingX = 0; int collidingY = 0;

    if(s1.x >= s2.x && s1.x <= s2endingX) { collidingX = 1; }
    if(s2.x >= s1.x && s2.x <= s1endingX) { collidingX = 1; }

    if(s1endingX >= s2.x && s1.x <= s2.x) { collidingX = 1; }
    if(s2endingX >= s1.x && s2.x <= s1.x) { collidingX = 1; }

    if(s1.y >= s2.y && s1.y <= s2endingY) { collidingY = 1; }
    if(s2.y >= s1.y && s2.y <= s1endingY) { collidingY = 1; }

    if(s1endingY >= s2.y && s1.y <= s2.y) { collidingY = 1; }
    if(s2endingX >= s1.y && s2.y <= s1.y) { collidingY = 1; }

    if(collidingX == 1 && collidingY == 1){
        if(s1.spriteType == fixed || s2.spriteType == fixed) { return 0; }
        else { return 1; }
    }
    else{
        return 0;
    }
}

/* Create a new sprite with the specified parameters. The sprite is drawn to screen and returned. */
sprite createSprite(uint16_t x, uint16_t y, int pixelCount, int pixelsPerRow, uint16_t pixelSize, int colours[], uint16_t palette[], type spriteType){
    sprite s;
    s.x = x;
    s.y = y;
    s.pixelCount = pixelCount;
    s.pixelsPerRow = pixelsPerRow;
    s.pixelSize = pixelSize;
    s.spriteType = spriteType;
    drawSprite(s, colours, palette);
    return s;
}

/* Applies the effect of gravity to a sprite. Returns the new sprite. */
sprite applyGravityToSprite(sprite s, int colours[], uint16_t palette[]) {
    return moveSprite(s, colours, 0, s.gravity, palette);
}

/* Updates the gravity of a sprite. Returns the new sprite. */
sprite setSpriteGravity(sprite s, float g){
    if(g > 10) { g = 10;}
    s.gravity = g;
    return s;
}

/* Changes the gravity of a sprite. Returns the new sprite. */
sprite changeSpriteGravity(sprite s, float g){
    s.gravity += g;
    if(s.gravity > 10) { s.gravity = 10;}
    return s;
}

/* Checks if a sprite is overlapping wth a trigger, and if so, calls the supplied function.  
   Returns 1 if true, and 0 if false.*/
int areTriggering(sprite s1, sprite s2, void(*function)()){
    if(areColliding(s1, s2) == 1){
        if (s1.spriteType == trigger || s2.spriteType == trigger) { (*function)(); return 1; }
        else { return 0; }
    }
    else{
        return 0;
    }
}

/* Re-scales a sprite by a supplied factor, by changing the pixel size. Returns the new sprite. */
sprite rescaleSprite(sprite s, int delta, int colours[], uint16_t palette){
    s.pixelSize = s.pixelSize * delta;
    drawSprite(s, colours, palette);
    return s;
}