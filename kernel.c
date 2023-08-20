/*
	 __             _          ___  __
	/ _\_ __   __ _| | _____  /___\/ _\   
	\ \| '_ \ / _` | |/ / _ \//  //\ \    
	_\ \ | | | (_| |   <  __/ \_// _\ \   
	\__/_| |_|\__,_|_|\_\___\___/  \__/ 

			Built by skzidev.
		   Licensed under MIT.
*/

 //  All these files come with the prefix of the filename
//   This modulates the OS so code can be easily traced.
#include "display.h"    // Include Default VGA Display Driver
#include "constants.h" //  Include constants in the std lib.
#include "keyboard.h" //   Include The PS2 keyboard driver
#include "font.h"    //    Include system font.
#include "game.h"   //     Include the game code library
// #include "idt.h"   //      Include Interrupt Descriptor Table.

DisplayDetails globalDisplayDetails; // The display details.
font_addr fontData;

  // Gets called before `main`.
 //  Loads the address and size into a struct, so it doesn't get lost.
//   The font will be retrieved in `main`.
void load_crumbs(){
	unsigned int address = (unsigned int) 0x0600 + 0x0601;
	unsigned char size = (unsigned char) 0x06002;
	fontData.addr = address;
	fontData.size = size;
}

// Keypress Callbacks
void enterPressed(){
	// Enter was pressed
	putpixel(10, 10, 0x0E);
}
void upPressed(){
	// Up Arrow was pressed
	putpixel(10, 10, 0x0f);
}
void leftPressed(){
	// Left arrow was pressed
	putpixel(10, 10, 0x0a);
}
void downPressed(){
	// Down arrow pressed
	putpixel(10, 10, 0x00);
}
void rightPressed(){
	// Right arrow was pressed
	putpixel(10, 10, 0x67);
}

// Error messages
void keyboardNotPresent(){
	// Print "Err 3" very crudely
	display_drawErr();
	display_drawErrThree();
}

// Entrypoint main
int main(){
	// Init the display details
	DisplayDetails details = display_init();
	globalDisplayDetails = details;

	// Init the IDT
	// idt_init();

	// Init the keyboard driver.
	keyboard_cbTable callbackTable = keyboard_initiateCbTable();
	// Assign all the key callbacks to their correct members.
	callbackTable.ENTERKEY = &enterPressed;
	callbackTable.UPKEY = &upPressed;
	callbackTable.DOWNKEY = &downPressed;
	callbackTable.RIGHTKEY = &rightPressed;
	callbackTable.LEFTKEY = &leftPressed;
	callbackTable.NOKEYBOARD = &keyboardNotPresent;
	keyboard_init(callbackTable);

	// Create the running variable
	bool running = true;

	load_font(fontData);
		
	while(running){
	     // This is the OS loop
		//  Here the code refreshes the screen and keyboard here.

		// Check for key presses and releases.
		keyboard_read();
	}
}
