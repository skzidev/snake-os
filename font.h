/*

Font.h; The default system font.

This file will house the pixel font used for text displayed on-screen.
This includes error messages, call-to-actions, and scores.
*/

// My horrible attempt at a pixel coordinate font.
int locations[8][2] = {
	{4, 0}, {4, 1},
	{5, 0}, {5, 1},
	{6, 0}, {6, 1},
	{7, 0}, {10,1},
};

// My own implementation of the `strlen` function from the C library.
int font_strlen(char* str){
	int length = 0;

	for(; str[length + 1]; length ++);

	return length;
}
