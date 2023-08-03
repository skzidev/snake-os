enum SupportedKeyCodes {
	NULLKEY    = 0,
	ENTERKEY   = 0x9C,
	UPKEY      = 0x75,
	DOWNKEY    = 0x50,
	RIGHTKEY   = 0x74,
	LEFTKEY    = 0x4B
};

void keyboard_init();
void keyboard_init(){
	// Init Keyboard Driver
}

unsigned char readportb(unsigned char portid);
unsigned char readportb(unsigned char portid){
	unsigned char res = 0;

	//__asm__("mov dx, portid");
	//__asm__("in ax, dx");
	//__asm__("mov [res], al");

	return res;
}

void keyboard_read();
void keyboard_read(){
	// Read from the PS/2 keyboard
	unsigned char scancode = readportb(0x60);

	switch(scancode){
		case NULLKEY:
			// Do nothing
			break;
		case ENTERKEY:
			// Enter key was pressed.
			break;
		case UPKEY:
			// Up was pressed
			break;
		case DOWNKEY:
			// Down was pressed
			break;
		case LEFTKEY:
			// Left was pressed
			break;
		case RIGHTKEY:
			// Right was pressed
			break;
		default:
			// We don't care about that.
			break;
	}
}
