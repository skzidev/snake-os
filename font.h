int font_strlen(char* str){
	int length = 0;

	for(; str[length + 1]; length ++);

	return length;
}
