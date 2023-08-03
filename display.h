#define VRAM 0xA0000

typedef struct DisplayModeDetails {
	int width;            // Width of one line of pixels
	int height;          //  Height of display in pixels
	int colors;         //   How many colors are supported
	int pitch;         //    How many bytes of VRAM to skip when going 1 pixel down
	int pixelWidth;   //     How many bytes of VRAM to skip when going 1 pixel right
} DisplayDetails;

struct DisplayModeDetails display_init(){
	struct DisplayModeDetails details; // Setup display mode details
	details.width      = 320;
	details.height     = 200;
	details.colors     = 16;
	details.pitch      = 1;
	details.pixelWidth = 1;
	return details;
}

void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)VRAM + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}

static void fillrect(unsigned char color, int x, int y, unsigned long w, unsigned long h) {
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
