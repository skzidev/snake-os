/*

Display.h; The display driver

Supports 256 color 320x200 VGA mode, as initiated in our bootloader.
(See boot_sect.asm for more detail)
*/

// VRAM starting memory address
#define VRAM 0xA0000
// Constant; Width of the snake
#define SNAKE_WIDTH 20
// Length of the snake. Starts same as width.
int snakeLength = 20;

// x and y coordinates of the snake's head.

// Details about our display mode
typedef struct DisplayModeDetails {
	int width;            // Width of one line of pixels
	int height;          //  Height of display in pixels
	int colors;         //   How many colors are supported
	int pitch;         //    How many bytes of VRAM to skip when going 1 pixel down
	int pixelWidth;   //     How many bytes of VRAM to skip when going 1 pixel right
} DisplayDetails;

// Create our details
struct DisplayModeDetails display_init(){
	struct DisplayModeDetails details; // Setup display mode details
	details.width      = 320;
	details.height     = 200;
	details.colors     = 256;
	details.pitch      = 1;
	details.pixelWidth = 1;
	return details;
}

// Place a pixel on the screen at the coordinates and color
static inline void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)VRAM + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}

// Fill a rectangle of a specified with and height
static void fillrect(unsigned char color, int x, int y, int w, int h) {
    unsigned char *where = (unsigned char*)VRAM;
    int i, j;
 
    for (i = y; i < w; i++) {
        for (j = x; j < h; j++) {
            where[j * 320] = color;
        }
        where ++;
    }
}

void display_drawErr(){
		/*
		Visualization; Converting this into pixel coordinates.
	
		XXXXX XXXX  XXXX    XXXXX
		X     X   X X   X        X
		XXXXX XXXX  XXXX    XXXXX
		X     X  X  X  X         X
		XXXXX X   X X   X   XXXXX
	*/
	// Show a crude E
	for(int i = 0; i < 8; i ++){
		// Create the straight 8px long line
		putpixel(0, i, 0x28);
	}
	for(int i = 0; i < 5; i ++){
		// Create the three other 5px long lines
		putpixel(i, 0, 0x28);
		putpixel(i, 4, 0x28);
		putpixel(i, 8, 0x28);
	}

	// Show a crude R or two
	for(int i = 0; i < 9; i ++){
		// Create the long straight line
		putpixel(10, i, 0x28);
		// Second R
		putpixel(20, i, 0x28);
	}
	for(int i = 0; i < 5; i ++){
		// Create part of the semi-circle
		putpixel(10 + i, 0, 0x28);
		putpixel(i + 10, 3, 0x28);
		// Second R
		putpixel(20 + i, 0, 0x28);
		putpixel(i + 20, 3, 0x28);
	}
	// Finish the semi-circles
	putpixel(15, 1, 0x28);
	putpixel(15, 2, 0x28);
	// Second R
	putpixel(25, 1, 0x28);
	putpixel(25, 2,0x28);
	// Create the diagnal line
	for(int i = 0; i < 6; i ++){
		int finalY = 7;
		int finalXOne = 15;
		int finalXTwo = 25;

		putpixel(finalXOne - i, finalY - i, 0x28);
		putpixel(finalXTwo - i, finalY - i, 0x28);
	}
}

void display_drawErrThree(){
	// Draw a crude 3
	for(int i = 0; i < 5; i ++){
		// Create the three 5px long lines
		putpixel(i + 30, 0, 0x28);
		putpixel(i + 30, 4, 0x28);
		putpixel(i + 30, 8, 0x28);
	}
	for(int i = 0; i < 2; i += 2){
		putpixel(35, i + 1, 0x28);
		putpixel(35, i + 2, 0x28);
		putpixel(35, i + 3, 0x28);
		// Second set
		putpixel(35, i + 5, 0x28);
		putpixel(35, i + 6, 0x28);
		putpixel(35, i + 7, 0x28);
	}
}

// Draw the snake
void display_drawSnake(){
	
}
