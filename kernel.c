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
#include "constants.h" //  Include constants which are in the std lib.
#include "keyboard.h" //   Include the custom keyboard driver
#include "font.h"    //    Include custom font. Doesn't work yet.
#include "game.h"   //     Include game code library

DisplayDetails globalDisplayDetails; // The display details.

// Callbacks

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
	// Print "Err 3"
	/*
	Pixel Arrangement:
	
		XXXXX XXXX  XXXX    XXXXX
		X     X   X X   X        X
		XXXXX XXXX  XXXX    XXXXX
		X     X  X  X  X         X
		XXXXX X   X X   X   XXXXX
	*/
	// Show an error message
	putpixel(0, 0, 0x28);
	putpixel(0, 1, 0x28);
	putpixel(0, 2, 0x28);
	putpixel(0, 3, 0x28);
	putpixel(0, 4, 0x28);
	putpixel(0, 5, 0x28);
}

// Entrypoint main
int main(){
	// Init the display details
	DisplayDetails details = display_init();
	globalDisplayDetails = details;

	// Init the keyboard driver.
	keyboard_cbTable callbackTable = keyboard_initiateCbTable();
	callbackTable.ENTERKEY = &enterPressed;
	callbackTable.UPKEY = &upPressed;
	callbackTable.DOWNKEY = &downPressed;
	callbackTable.RIGHTKEY = &rightPressed;
	callbackTable.LEFTKEY = &leftPressed;
	callbackTable.NOKEYBOARD = &keyboardNotPresent;
	keyboard_init(callbackTable);

	// Draw our logo
	for(int y = 0; y < game_logoHeight; y ++){
		for(int x = 0; x < game_logoWidth; x ++){
			putpixel(x, y, 0x0f);
		}
	}

	// Create our running variable
	bool running = true;
	
	while(running){
	     // This is the OS loop
		//  Here the code refreshes the screen and keyboard here.

		// Check for key presses and releases.
		keyboard_read();
	}
}
