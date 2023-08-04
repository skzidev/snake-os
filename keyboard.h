typedef void (*keyboard_callback)();

enum SupportedKeyCodes {
	NULLKEY    = 0x00,
	ENTERKEY   = 0x9C,
	UPKEY      = 0x75,
	DOWNKEY    = 0x50,
	RIGHTKEY   = 0x74,
	LEFTKEY    = 0x4B
};

typedef struct keyboard_callbackLookupTable {
	keyboard_callback NULLKEY;       // When "NULLKEY" is pressed
	keyboard_callback ENTERKEY;     // When "Enter" is pressed
	keyboard_callback UPKEY;       // When "Up Arrow" is pressed
	keyboard_callback DOWNKEY;    // When "Down Arrow" is pressed
	keyboard_callback RIGHTKEY;  // When "Right Arrow" is pressed
	keyboard_callback LEFTKEY;  // When "Left Arrow" is pressed
} keyboard_cbTable;

keyboard_cbTable globalTable;

keyboard_cbTable keyboard_initiateCbTable(){
	struct keyboard_callbackLookupTable table;
	return table;
}

void keyboard_init(keyboard_cbTable table);
void keyboard_init(keyboard_cbTable table){
	// Init Keyboard Driver with callback table
	globalTable = table;
}

// Custom `inportb` function written in inline ASM.
unsigned char readportb(unsigned char portid);
unsigned char readportb(unsigned char portid){
	unsigned char ret;
	asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (portid));
	return ret;
}

void writeportb(unsigned char portid, unsigned char value);
void writeportb(unsigned char portid, unsigned char value){
	asm volatile ("outb %%al,%%dx": :"d" (portid), "a" (value));
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
			globalTable.ENTERKEY();
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
			// A key that isn't supported was pressed.
			break;
	}
}
