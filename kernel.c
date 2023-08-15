/*
	 __             _          ___  __
	/ _\_ __   __ _| | _____  /___\/ _\   
	\ \| '_ \ / _` | |/ / _ \//  //\ \    
	_\ \ | | | (_| |   <  __/ \_// _\ \   
	\__/_| |_|\__,_|_|\_\___\___/  \__/ 

			Built by skzidev.
		   Licensed under MIT.
*/

 // All these files come with the prefix of the filename
// This modulates the OS so code can be easily traced.
#include "display.h"    // Include Display Drivers
#include "constants.h" //  Include constants in the std lib.
#include "keyboard.h" //   Include the keyboard driver
#include "font.h"    //    Include custom font.
#include "game.h"   //     Include game code library

DisplayDetails globalDisplayDetails; // The display details.

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

	// Sanity check
	putpixel(5, 5, 0x0f);

	// Create the running variable
	bool running = true;
	
	while(running){
	     // This is the OS loop
		//  Here the code refreshes the screen and keyboard here.

		// Check for key presses and releases.
		keyboard_read();
	}
}
