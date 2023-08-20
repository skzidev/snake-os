/*

Font.h; The default system font.

This file will house the pixel font used for text displayed on-screen.
This includes error messages, call-to-actions, and scores.
*/

typedef struct {
	unsigned char addr;
	unsigned char size;
} font_addr;

void load_font(font_addr data){
	int length = 256 * (int) data.size;
	if(length == 0){
		//
	}
	unsigned char* vmem  = (unsigned char*) 0xA0000;
	unsigned char* table = (unsigned char*) data.addr;
	*vmem = 0x0f;
}

// My own implementation of the `strlen` function from the C library.
int font_strlen(char* str){
	int length = 0;

	for(; str[length + 1]; length ++);

	return length;
}
