int locations[8][2] = {
	{4, 0}, {4, 1},
	{5, 0}, {5, 1},
	{6, 0}, {6, 1},
	{7, 0}, {10,1},
};


int font_strlen(char* str){
	int length = 0;

	for(; str[length + 1]; length ++);

	return length;
}
