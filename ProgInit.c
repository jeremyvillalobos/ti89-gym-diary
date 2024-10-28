// C Source File
// Created 8/16/2003; 5:27:18 AM
//Author: Jeremy F Villalobos
#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

// #define OPTIMIZE_ROM_CALLS // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files

// Main Function
struct ProgramData{
	int CurrentIndex;
	
};
void _main(void)
{
	struct ProgramData ProgData;
	ProgData.CurrentIndex = 0;
//	ProgData.deleted = 0;
	FILE *FPtr;
	if( ( FPtr = fopen( "Prog", "a+") ) == NULL)
		printf( "File could not be opened.\n");
	else
		{
			fseek(FPtr, 0, SEEK_SET);
			fwrite(&ProgData, sizeof(struct ProgramData), 1, FPtr);
		}
	clrscr();
	printf("Current Index: %d ", ProgData.CurrentIndex);
	printf("\nfile set up successful!");
	ngetchx();
}
