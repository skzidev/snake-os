void main(){
	unsigned char* vram = (unsigned char*) 0xb8000;
	vram[0] = 'o';
	vram[1] = 0x0f;
	for(;;);
}

void _start(){
	return;
}
