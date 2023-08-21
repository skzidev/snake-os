/*

Font.h; The default system font.

This file will house the pixel font used for text displayed on-screen.
This includes error messages, call-to-actions, and scores.
*/

// My own implementation of the `strlen` function from the C library.
int font_strlen(char* str){
	int length = 0;

	for(; str[length + 1]; length ++);

	return length;
}
