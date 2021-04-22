/* Author: Joshua Wardle
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */

#include "sprite.h"

/* Draws a sprite 's' to the screen using colours for each pixel as defined in 'colours'. */
void drawSprite(sprite s, uint16_t colours[]){
    uint16_t drawX, drawY;
    drawX = s.x; drawY = s.y;
    int i;

    for(i = 0; i < s.pixelCount; ++i ){
        if(i % s.pixelsPerRow == 0 && i != 0) { drawX = s.x; drawY = drawY + s.pixelSize; }

        rectangle r;
        r.top = drawY; r.bottom = drawY + s.pixelSize;
        r.left = drawX; r.right = drawX + s.pixelSize;

        fill_rectangle(r, colours[i]);
        drawX = drawX + s.pixelSize;
    }
} 

/* Remove a sprite 's' from the screen. */
void eraseSprite(sprite s){
    int rows = s.pixelCount / s.pixelsPerRow;
    rectangle r;
    r.top = s.y; r.bottom = s.y + (s.pixelSize * rows);
    r.left = s.x; r.right = s.x + (fmin(s.pixelCount, s.pixelsPerRow) * s.pixelSize);

    fill_rectangle(r, BLACK);
}

/* Moves a sprite s by position x, y and draws it to screen. The updated sprite is returned. */
sprite moveSprite(sprite s, uint16_t colours[], uint16_t x, uint16_t y){
    eraseSprite(s);
    s.x = s.x + x;
    s.y = s.y + y;
    drawSprite(s, colours);
    return s;
}