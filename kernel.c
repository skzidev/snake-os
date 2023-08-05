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
#include "constants.h" //  Include constants that C doesn't have included
#include "keyboard.h" //   Include the custom keyboard driver
#include "font.h"    //    Include custom font. Doesn't work yet.

DisplayDetails globalDisplayDetails; // The display details.

// On key press of enter
void enterPressed(){
	putpixel(10, 10, 0x0E);
}

// Entrypoint main
int main(){
	// Init the display details
	DisplayDetails details = display_init();
	globalDisplayDetails = details;

	// Init the keyboard driver.
	keyboard_cbTable callbackTable = keyboard_initiateCbTable();
	callbackTable.ENTERKEY = &enterPressed;
	keyboard_init(callbackTable);

	// Create our running variable
	bool running = true;
	
	while(running){
	     // This is the OS loop
		//  Here the code refreshes the screen and keyboard here.

		// Read a key
		keyboard_read();
	}
}
