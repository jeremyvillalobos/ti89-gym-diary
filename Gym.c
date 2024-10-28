// C Source File
// Created 10/2/2002; 12:04:59 AM
//Author: Jeremy F Villalobos
#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

// #define OPTIMIZE_ROM_CALLS // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files
#include "DateMani.h"
#include <DisplayMani.h>
#include <filemani.h>

// Main Function
// Archivo principal, implementar todas las funciones, Ques se vea simple y nitido !!

void InitSchedule();

void _main(void)
{
		FILE *WFile, *PData;
		char input[INPUT_SIZE];
		int pos = 1;  // position of the cursor
		struct Gym WorkOut;  // structure of a Gym to extract records and store data
		if( ( WFile = fopen( "Workout.inf", "r+" ) ) == NULL)			//WORK OUT INFORMATION
				DlgMessage("NOTICE", "File could not be opened", BT_OK,BT_NONE);	
		if( ( PData = fopen( "PData.dat", "r+") ) == NULL)	// PROGRAM DATA
				DlgMessage("NOTICE", "File could not be opened", BT_OK, BT_NONE);
		newDay(WFile, index, &WorkOut);
		ClrScr();
		DisplaySchedule();
		/// input checker
	int i = 0;
	while(input[i] = ngetchx() != 34)
	{
		switch (input[i]){
			case 	338:
				if(i == 0)
				{
					if(pos - 2 > 0)
						pos -= 2;
						break;
				}
				else
				{
				DecisionInput(input, &WorkOut , pos);
				if(pos - 2 > 0)
					pos -= 2;
					break;
				}
			case 340:
				 if(i == 0)
				{
					if(pos == 1)
					{
							
					}
					else
					{
					if(pos + 1 < 10)
						pos++;
						break;
					}
				}
				else
				{
				DecisionInput(input, &WorkOut , pos);
				if(pos + 1 < 10)
					pos++;
					break;
				}
			case 344:
				if(i == 0)
				{
					if(pos + 2 < 10)
						pos += 2;
						break;
				}
				else
				{
				DecisionInput(input, &WorkOut , pos);
				if(pos + 2 > 0)
					pos += 2;
					break;
				}
			case 337:
				if(i == 0)
				{
					if(pos - 1 > 0)
						pos--;
						break;
				}
				else
				{
				DecisionInput(input, &WorkOut , pos);
				if(pos - 1 > 0)
					pos--;
					break;
				}
			case 13:
				if(i == 0)
				{
					break;
				}
				else
				{
				DecisionInput(input, &WorkOut , pos);
				if(pos + 1 < 10)
					pos ++;
					break;
				}
				
		}
	}
	// Place your code here.
}

