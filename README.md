# LaFortuna Sprite Library v0.65
A sprite library for writing games for the LaFortuna, a microprocessor board running the AT90USB1286.

## Uses
This library is intended for those who want to create their own games. This library lets users:
- Create and modify sprites
- Detect if two sprites are colliding
- Use sprite collisions as triggers for other functions
- Simulate gravity

## Example Use Code
This code draws a ball to the screen, and bounces it up and down, displaying a message each time.
```
// Palette for this example
uint16_t pal[3] = {BLACK, WHITE, RED};

// The two sprites
sprite s1;
sprite s2;

// Sprite colours for s1
uint16_t cs1[25];
cs1[0] = 0; cs1[1] = 1; cs1[2] = 1; cs1[3] = 1; cs1[4] = 0; 
cs1[5] = 1; cs1[6] = 2; cs1[7] = 2; cs1[8] = 2; cs1[9] = 1;
cs1[10] = 1; cs1[11] = 2; cs1[12] = 2; cs1[13] = 2; cs1[14] = 1; 
cs1[15] = 1; cs1[16] = 2; cs1[17] = 2; cs1[18] = 2; cs1[19] = 1; 
cs1[20] = 0; cs1[21] = 1; cs1[22] = 1; cs1[23] = 1; cs1[24] = 0;

// Creates s1 and applies gravity to it
s1 = createSprite(137.5, 10, 25, 5, 5, cs1, pal, collider);
s1 = setSpriteGravity(s1, 10);

// Sprite colour for s2
uint16_t cs2[1];
cs2[0] = 2;

// Creates s2
s2 = createSprite(100, 200, 1, 1, 100, cs2, pal, trigger);

for(;;){
    // Updates gravity and applies it to s1
    s1 = changeSpriteGravity(s1, 0.85);
    s1 = applyGravityToSprite(s1, cs1, pal);

    drawSprite(s2, cs2, pal);

    // If s1 is touching s2, then function 'talk' triggered and bounce occurs
    if(areTriggering(s1, s2, &talk) == 1){
        s1 = setSpriteGravity(s1, -10);
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

Next: Animations, prite_init() and configuration support

**This is still a work in progress.**