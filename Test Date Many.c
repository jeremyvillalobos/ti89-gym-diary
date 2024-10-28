// C Source File
// Created 8/9/2003; 1:36:41 AM
//Author: Jeremy F Villalobos
#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

// #define OPTIMIZE_ROM_CALLS // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files
#include "DateMani.h"
#include <stdio.h>

// Main Function
void _main(void)
{
	// data
	char input[INPUT_SIZE] = {};		// input receiver
	char key;												// used to get input from keyboard
	int loop = 0;										// used to get input from keyboard
	struct date_t fecha = {0, 0, 0};
	int NumOfDays = 0;
	enum day_t Dday;
	char *WeekDaysstr[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	//code
	clrscr();
	printf("enter a date and I will \ntell you what day of \nthe week is it and number of day\n");
	while((key = getchar()) != '\n'){
		if(loop >= INPUT_SIZE)
			break;
		input[loop] = key;
		loop++;
	}
//	printf("\n printed %s", input);
	if(getDate(&fecha, input)){
		printf("%s", input);
		printf("\n Date: %d/%d/%d", fecha.m, fecha.d, fecha.y);
		}
	else 
		printf("\n invalid date");
	if(validDate(&fecha)){
		NumOfDays = DateNum(&fecha);
		printf("\n Day ID: %d",NumOfDays);
		Dday = findDayOfWeek(&fecha);
		printf("\n %s", WeekDaysstr[Dday]);
	}
	ngetchx();
}
