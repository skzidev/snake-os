/*
Game.h; The game.

Unlike the other header files, this is not a driver. This is the game code.
(Some of it. The rest is in kernel.c).

Here we keep track of things like score, and also store other information about the game.
We also keep track of the used color palettes here.

*/

enum game_colors {
	WHITE   = 0x0f,
	BLACK   = 0x00,
	GREEN   = 0x0a
};

int game_logoHeight = 5;
int game_logoWidth  = 26;
unsigned char game_Logo[5][26] = {
	" XXX  XX    X XXXXX X  X",
	"X     X X   X X     X X ",
	" XXX  X  X  X XXXXX XX  ",
	"    X X   X X X     X X ",
	" XXX  X    XX XXXXX X  X"
};
