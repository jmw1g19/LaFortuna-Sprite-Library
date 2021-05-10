# LaFortuna Sprite Library v0.75
A sprite library for writing games for the LaFortuna, a microprocessor board running the AT90USB1286.

## Uses
This library is intended for those who want to create their own games. This library lets users:
- Create and modify (move and rescale) sprites
- Detect if two sprites are colliding
- Use sprite collisions as triggers for other functions
- Simulate gravity
- Trigger basic animations

## Example Use Code
This code draws a ball to the screen, and bounces it up and down, displaying a message each time and changing the colour of the ball.
```
// Flicker free demonstration
set_frame_rate_hz(61);

// Palette for this example
uint16_t pal[5] = {BLACK, WHITE, RED, BLUE, GREEN, MAGENTA};

// The two sprites
sprite s1;
sprite s2;

// Sprite colours for s1's animation
uint16_t cs1a[25];
cs1a[0] = 0; cs1a[1] = 1; cs1a[2] = 1; cs1a[3] = 1; cs1a[4] = 0; 
cs1a[5] = 1; cs1a[6] = 2; cs1a[7] = 2; cs1a[8] = 2; cs1a[9] = 1;
cs1a[10] = 1; cs1a[11] = 2; cs1a[12] = 2; cs1a[13] = 2; cs1a[14] = 1; 
cs1a[15] = 1; cs1a[16] = 2; cs1a[17] = 2; cs1a[18] = 2; cs1a[19] = 1; 
cs1a[20] = 0; cs1a[21] = 1; cs1a[22] = 1; cs1a[23] = 1; cs1a[24] = 0;

uint16_t cs1b[25];
cs1b[0] = 0; cs1b[1] = 1; cs1b[2] = 1; cs1b[3] = 1; cs1b[4] = 0; 
cs1b[5] = 1; cs1b[6] = 3; cs1b[7] = 3; cs1b[8] = 3; cs1b[9] = 1;
cs1b[10] = 1; cs1b[11] = 3; cs1b[12] = 3; cs1b[13] = 3; cs1b[14] = 1; 
cs1b[15] = 1; cs1b[16] = 3; cs1b[17] = 3; cs1b[18] = 3; cs1b[19] = 1; 
cs1b[20] = 0; cs1b[21] = 1; cs1b[22] = 1; cs1b[23] = 1; cs1b[24] = 0;

uint16_t cs1c[25];
cs1c[0] = 0; cs1c[1] = 1; cs1c[2] = 1; cs1c[3] = 1; cs1c[4] = 0; 
cs1c[5] = 1; cs1c[6] = 4; cs1c[7] = 4; cs1c[8] = 4; cs1c[9] = 1;
cs1c[10] = 1; cs1c[11] = 4; cs1c[12] = 4; cs1c[13] = 4; cs1c[14] = 1; 
cs1c[15] = 1; cs1c[16] = 4; cs1c[17] = 4; cs1c[18] = 4; cs1c[19] = 1; 
cs1c[20] = 0; cs1c[21] = 1; cs1c[22] = 1; cs1c[23] = 1; cs1c[24] = 0;

int * animFrames[3];
animFrames[0] = cs1a;
animFrames[1] = cs1b;
animFrames[2] = cs1c;

// Create the animation object
animation a = createAnimation(3, animFrames);

// Creates s1 and applies gravity to it
s1 = createSprite(137.5, 10, 25, 5, 5, getFrame(a), pal, collider);
s1 = setSpriteGravity(s1, 10);

// Sprite colour for s2
uint16_t cs2[1];
cs2[0] = 2;

// Creates s2
s2 = createSprite(100, 200, 1, 1, 100, cs2, pal, trigger);

for(;;){
    // Updates gravity and applies it to s1
    s1 = changeSpriteGravity(s1, 0.85);
    s1 = applyGravityToSprite(s1, getFrame(a), pal);

    drawSprite(s2, cs2, pal);

    // If s1 is touching s2, then function 'talk' triggered and bounce occurs
    if(areTriggering(s1, s2, &talk) == 1){
        s1 = setSpriteGravity(s1, -10);
        // Move forward animation
        a = nextFrame(a, loop);
    }

    _delay_ms(50);
}
```
```
void talk(){
	display_string("Bounce!\n");
}
```

## Changelog
v0.0 - Initial commit

v0.3 - drawSprite(), eraseSprite() and moveSprite() written

v0.4 - areColliding() and createSprite() written

v0.5 - palette support and gravity introduced

v0.6 - Sprite type support and code example written

v0.65 - rescaleSprite() and animation structs written

v0.75 - Animation support and starting configuration information

Next: sprite_init()

**This is still a work in progress.**