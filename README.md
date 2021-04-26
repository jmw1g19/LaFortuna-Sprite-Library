# LaFortuna Sprite Library v0.3
A sprite library for writing games for the LaFortuna, a microprocessor board running the AT90USB1286.

## Uses
This library is intended for those who want to create their own games. This library lets users create sprites, move them, and detect if two sprites are colliding.

## Example Use Code
This creates a 2x2 sprite with pixel size 30, gives it a red and green checkerboard pattern, and moves it to the right 10 times:
```	
sprite s;
s.x = 50;
s.y = 50;
s.pixelCount = 4;
s.pixelsPerRow = 2;
s.pixelSize = 10;

uint16_t cs[4];
cs[0] = RED;
cs[1] = GREEN;
cs[2] = GREEN;
cs[3] = RED;

drawSprite(s, cs);

for(int i = 0; i < 10; i++){
	_delay_ms(100);
	s = moveSprite(s, cs, 10, 0);
}
````

## Changelog
v0.0 - Initial commit

v0.3 - drawSprite(), eraseSprite() and moveSprite() written

v0.4 - areColliding() and createSprite() written

Next: palette support, more sprite manipulation functions

**This is still a work in progress.**