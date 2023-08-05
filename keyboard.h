/*

Keyboard.h; The keyboard Driver

This is a non-interrupt based PS/2 keyboard driver.

Non-interrupt based because I haven't set up an IDT yet.

TODO: Add USB Keyboard support.

The reason I'm not doing this out of the box is because of 2 reasons

1. I want to learn how PS/2 works
2. Lots of laptops use PS/2 to connect their keyboards internally,
and I'm planning on seeing if I can run this OS on an old laptop I have.

*/

 // Create our keyboard callback function type.
// I'm a JavaScript programmer, what did you expect?
typedef void (*keyboard_callback)();

// List of key codes we will register
enum SupportedKeyCodes {
	NULLKEY    = 0x00,       // NullKey; Might be a debugging thing? idk
	ENTERKEY   = 0x9C,      //  Enter; Used to start the game
	UPKEY      = 0x75,     //   Up arrow; Used to move the snake up
	DOWNKEY    = 0x50,    //    Down arrow; Move the snake down
	RIGHTKEY   = 0x74,   //     Right Arrow; Move the snake right
	LEFTKEY    = 0x4B   //      Left Arrow; Move the snake's head left
};

// A struct that can be used to look up the callbacks to be fired.
typedef struct keyboard_callbackLookupTable {
	keyboard_callback NULLKEY;       // When "NULLKEY" is pressed
	keyboard_callback ENTERKEY;     //  When "Enter" is pressed
	keyboard_callback UPKEY;       //   When "Up Arrow" is pressed
	keyboard_callback DOWNKEY;    //    When "Down Arrow" is pressed
	keyboard_callback RIGHTKEY;  //     When "Right Arrow" is pressed
	keyboard_callback LEFTKEY;  //      When "Left Arrow" is pressed
} keyboard_cbTable;

// The global callback table
keyboard_cbTable globalTable;

// Create a callback table; Returns the table
keyboard_cbTable keyboard_initiateCbTable(){
	struct keyboard_callbackLookupTable table;
	return table;
}

// Initiator function
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

// Custom `outportb` function written in inline ASM.
void writeportb(unsigned char portid, unsigned char value);
void writeportb(unsigned char portid, unsigned char value){
	asm volatile ("outb %%al,%%dx": :"d" (portid), "a" (value));
}

// Read the keys from the keyboard.
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
