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

void _start(){} // Remove LD Warning

DisplayDetails globalDisplayDetails; // The display details.

int main(){
	// Init the display details
	DisplayDetails details = display_init();
	globalDisplayDetails = details;
	bool running = true;

	fillrect(0x4e, 0, 0, 320, 200);
	
	while(running){
		// This is the OS loop
	}
	
	// return 0;
}
