/*

Display.h; The display driver

Supports 256 color 320x200 VGA mode, as initiated in our bootloader.
(See boot_sect.asm for more detail)
*/

// VRAM starting memory address
#define VRAM 0xA0000

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
            //putpixel(vram, 64 + j, 64 + i, (r << 16) + (g << 8) + b);
            where[j*320] = color;
        }
        where ++;
    }
}
