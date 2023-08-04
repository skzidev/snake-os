/*
	 __             _          ___  __
	/ _\_ __   __ _| | _____  /___\/ _\   
	\ \| '_ \ / _` | |/ / _ \//  //\ \    
	_\ \ | | | (_| |   <  __/ \_// _\ \   
	\__/_| |_|\__,_|_|\_\___\___/  \__/ 

			Built by skzidev.
		   Licensed under MIT.
*/

#include "display.h"    // Include Display Drivers
#include "constants.h" // Include constants that C doesn't have included
#include "keyboard.h" // Include the custom keyboard driver
#include "font.h"    // Custom 8x8 font, grabbed from github. Might need another.

DisplayDetails globalDisplayDetails; // The display details.

void enterPressed(){
	putpixel(10, 10, 0x0E);
}

int main(){
	// Init the display details
	DisplayDetails details = display_init();
	globalDisplayDetails = details;

	// Init the keyboard driver.
	keyboard_cbTable callbackTable = keyboard_initiateCbTable();
	callbackTable.ENTERKEY = &enterPressed;
	keyboard_init(callbackTable);
	
	bool running = true;

	keyboard_read();
	
	while(running){
		// This is the OS loop
	}
	
	// return 0;
}
