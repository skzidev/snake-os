/*

Keyboard.h; The keyboard Driver

This is a non-interrupt based PS/2 keyboard driver.

Non-interrupt based because I haven't set up an IDT yet.

todo list:

TODO: Code is unable to recognize key-presses. Fix this madness.

Also if you want to learn more about this, I two resources that helped a lot.

OSDev Article: https://wiki.osdev.org/PS2_Keyboard
Ben Eater Video: https://www.youtube.com/watch?v=dL0GO9SeBh0

*/

// Global definitions
#define KEYBOARD 0x60

// Create our keyboard callback function type.
typedef void (*keyboard_callback)();
typedef unsigned char SupportedKeyCode;

// List of key codes we will register
enum SupportedKeyCodes {
	NULLKEY    = 0x00,          // NullKey; Might be a debugging thing? idk
	ENTERKEY   = 0x1C,         //  Enter; Used to start the game
	UPKEY      = 0x11,        //   Up arrow; Used to move the snake up
	DOWNKEY    = 0x1F,       //    Down arrow; Move the snake down
	RIGHTKEY   = 0x20,      //     Right Arrow; Move the snake right
	LEFTKEY    = 0x1E,     //      Left Arrow; Move the snake's head left
	KEYUP      = 0xF0     //       Keyboard sends this scancode on key up
};

// A struct that can be used to look up the callbacks to be fired.
typedef struct keyboard_callbackLookupTable {
	keyboard_callback NULLKEY;           // When "NULLKEY" is pressed
	keyboard_callback ENTERKEY;         //  When "Enter" is pressed
	keyboard_callback UPKEY;           //   When "Up Arrow" is pressed
	keyboard_callback DOWNKEY;        //    When "Down Arrow" is pressed
	keyboard_callback RIGHTKEY;      //     When "Right Arrow" is pressed
	keyboard_callback LEFTKEY;      //      When "Left Arrow" is pressed
	keyboard_callback NOKEYBOARD;  //       If there is no keyboard connected
} keyboard_cbTable;

// The global callback table
keyboard_cbTable keyboard_globalTable;

// Create a callback table; Returns the table
keyboard_cbTable keyboard_initiateCbTable(){
	struct keyboard_callbackLookupTable table;
	return table;
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

int keyboard_detect();
int keyboard_detect(){
	// Create an int representing a bool
	int keyboardConnected = 0;
	// Write a 0xEE command to port 0x60 (Echo command)
	writeportb(KEYBOARD, 0xEE);
	// Read the response
	unsigned char value = readportb(KEYBOARD);
	// Determine if it's connected. Reversed for debugging perposes
	keyboardConnected = value == 0x00 ? 0 : 1;
	// Run the error handler.
	if(keyboardConnected == 0){
		keyboard_globalTable.NOKEYBOARD();
	}
	// Return the value.
	return keyboardConnected;
}

// Initiator function
void keyboard_init(keyboard_cbTable table);
void keyboard_init(keyboard_cbTable table){
	// Init Keyboard Driver with callback table
	keyboard_globalTable = table;
	// Check if keyboard is there
	int keyboardPresent = keyboard_detect();
	if(keyboardPresent == 0) return;
	
	// I know later on, I may have to add bit delays, but better than nothing.

	// Disable Scanning. May cause triple faulting.
	writeportb(KEYBOARD, 0xF5);
	
	// Setting keyset, first the command byte
	writeportb(KEYBOARD, 0xF0);
	// Next we send the Data byte.
	writeportb(KEYBOARD, 1);
}


// Read the keys from the keyboard.
void keyboard_read();
void keyboard_read(){
	// Read from the PS/2 keyboard
	unsigned char scancode = readportb(KEYBOARD);

	switch(scancode){
		case NULLKEY:
			// Do nothing
			break;
		case ENTERKEY:
			// Enter key was pressed.
			keyboard_globalTable.ENTERKEY();
			break;
		case UPKEY:
			// W was pressed
			keyboard_globalTable.UPKEY();
			break;
		case DOWNKEY:
			keyboard_globalTable.DOWNKEY();
			// S was pressed
			break;
		case LEFTKEY:
			keyboard_globalTable.LEFTKEY();
			// A was pressed
			break;
		case RIGHTKEY:
			keyboard_globalTable.RIGHTKEY();
			// D was pressed
			break;
		case KEYUP:
			;
			break;
		default:
			// These keys are irrelevant (for now)
			break;
	}
}
