// C Source File
// Created 12/22/2002; 12:58:21 AM
// Author: Jeremy F Villalobos
#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

#define OPTIMIZE_ROM_CALLS    // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files
#include "module.h"

// Main Function


void _main(void)
{
	char letter = 0;
	int pos = 0;
	clrscr();
	DisplaySchedule();
	while( letter != 'c'){
			pos += 6;
			letter = ngetchx();
			DrawChar(pos, 20, letter, A_NORMAL);
			
	}
	// Place your code here.
}
