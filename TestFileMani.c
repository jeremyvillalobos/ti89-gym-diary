// C Source File
// Created 8/10/2003; 4:07:31 AM
// Author: Jeremy F Villalobos

#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

// #define OPTIMIZE_ROM_CALLS // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files
#include "FileMani.h"
//#include "DateMani.h"

// Main Function
enum readmode {READ_WRITE, READ_ONLY}; 
int getKeyboardInput(char *, int size);
int getNumberFromStream(char *, int size);
int GetInfo(struct Day *, enum readmode);
void DisplayInfo(struct Day *, int );
char *WeekDays[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};
char *ExerIDStr[] = {  
		"NONE" ,"Chest Press", "Incline Presses", "Decline Dumbbell Press" , "Machine Dips", 			//CHEST 13
		"Tricep Curl",  "Tricep Pullover", "Dubbell Pull Over" ,  												//TRICEP			0-12
		"Subscapularis in", "Subscapularis out","TBA", "TBA" , "TBA" , "TBA",							//MICELANIOUS CHEST
		"Asisted Chin Ups", "Dumbbell Bent-Over Rows", "Machine Row", "Lat Machine Pull Down", 	//BACK 13
		"Dumbbell Bicep Curl",  "Bicep Curl", "TBA" , "TBA", "TBA" ,														//BICEPT	13-25
		"Dumbbell Side Lift", "Dumbbell Front Lift", "Straight Up Press", "Machine Side Lift",	//DELTS
		"Smith Machine Press", "Leg Press", "Leg Curl", "Leg Extencion", 												//PIERNAS 10   26-35
		"Leg Abduction In", "Leg Abduction Out","Calf Machine", "Back",	"TBA", "TBA",						//CALF AND MICS
		"Abs Crounches", "Abs sit up" , "Abs Side Crounch"	,"TBA", "TBA"											// ABS  5 36-40

};
char *MGroupStr[] = {
	"NONE",
	"CHEST",
	"BACK",
	"LEGS"
};
void _main(void)
{
	struct Day Blank;
	struct Day sched;
	char input[INPUT_SIZE] = {};
	int TrueSize =0 , menueSel = 1, index = 0;
	FILE *cfPtr;
	int i,j; // for the loop		
	//set up blank
	Blank.date.d = 0;  Blank.date.m = 0; Blank.date.y = 0;	/////////create blank Day
	Blank.MGroup = 0;																				//////
	// loop to set Blank day to 0
	for(i =0; i < EXER_NUM; i++)
	{
		Blank.IndividualExercise[i].ExerciseID = 0;
		for(j = 0; j < SET_NUM; j++)
			{
				Blank.IndividualExercise[i].DSet[j].rep = 0;
				Blank.IndividualExercise[i].DSet[j].weight = 0;
			}
	}
	sched = Blank;
	clrscr();
	//open file for editing
	if( ( cfPtr = fopen( "GymDiary", "a+") ) == NULL)
	{
			printf("File could not be opened.\n");
			
	}
	else
	{
		while(menueSel != 0){
			clrscr();
			printf("******WORKOUT DIARY*******\n\n\n   1.new day\n   2.Edit past day\n   3.delete day\n   4.read\n   0.exit\n\n\nMenue selected: ");
			TrueSize = getKeyboardInput(input, INPUT_SIZE);
			menueSel = getNumberFromStream(input, TrueSize);
			//if(menueSel){
			//printf("give index num:  ");
			//TrueSize = getKeyboardInput(input, INPUT_SIZE);
			//index = getNumberFromStream(input, TrueSize);
			//}
				sched = Blank;
				switch (menueSel)
				{
					case 1:			//new day
						if(GetInfo(&sched,READ_WRITE))
						{
							newDay(cfPtr, &sched);
						}	
						else
							printf("input fail");
						break;
							
					case 2:			//edit past day
						printf("give index num:  ");
						TrueSize = getKeyboardInput(input, INPUT_SIZE);
						index = getNumberFromStream(input, TrueSize);
						if(readDay(cfPtr, index, &sched))
						{
							if(GetInfo(&sched,READ_WRITE))
								saveDay(cfPtr, index, &sched);
							else
								printf("input fail");
						}
						else
						{
							printf("\nseek fail");
						}
						// Final de Dispaly input
					break;
					
					case 3:		//delete day
						printf("give index num:  ");
						TrueSize = getKeyboardInput(input, INPUT_SIZE);
						index = getNumberFromStream(input, TrueSize);
						if(deleteDay(cfPtr, index)){}
							else{printf("can't delete");}
					break;
					case 4:		//read day
						printf("give index num:  ");
						TrueSize = getKeyboardInput(input, INPUT_SIZE);
						index = getNumberFromStream(input, TrueSize);
						if(readDay(cfPtr, index, &sched)){
							GetInfo(&sched,READ_ONLY); 			
						}
						else
						{
							printf("no index found...");
							ngetchx();
						}
					break;
					case 0:
					break;
					default:
						menueSel = 0;
						break;
		
			}
		}
	}					
	fclose( cfPtr);
}


int getKeyboardInput(char *stream, int size){
	int loop = 0; char key;
		while((key = getchar()) != '\n')
		{
			if(loop >= size)
				break;
			stream[loop] = key;
			loop++;
		}
	return loop;
}
/*
	while((key = getchar()) != '\n'){
		if(loop >= INPUT_SIZE)
			break;
		input[loop] = key;
		loop++;
	}
*/

int getNumberFromStream(char * inputNum, int size){
	int i;  // integer for the loop
	int output = 0;
	for(i = size-1; i >= 0; i--){
		if(isdigit(inputNum[i])){
			output += (inputNum[i] - 48) * pow(10, size - i - 1);
		}
		else{
			printf("not a valide number");
			return 0;
		}
	}
	return output;
}

int GetInfo(struct Day *sched, enum readmode r)
{
				int TrueSize = 0;
				char input[INPUT_SIZE] ={};
				int holdExerciseNum = 0;
				int i = 0;
				int loop = 0;
				//Ask for some input for testing
				if(!r){
					do
					{	
						for(i = 0; i < INPUT_SIZE; i++)
								input[i] = 0;
						DisplayInfo(sched, holdExerciseNum );
						printf("1.Date 2.MGroup 3.ExerNum\n4.Exercise ID 5.RepWeight\n6.ShowEx 0.exit ");
						TrueSize = getKeyboardInput(input, INPUT_SIZE);
						i = getNumberFromStream(input, TrueSize);
						switch (i)
						{
							case 1:
								printf("set date:  \n");
								getKeyboardInput(input, INPUT_SIZE);
								if(!getDate(&sched->date,input))
								{
									printf("bad date");
									return 0;
								}
							break;
							
							case 2:
								printf("set Muscle Group:  ");
								TrueSize = getKeyboardInput(input, INPUT_SIZE);
								sched->MGroup = getNumberFromStream(input, TrueSize);
							break;
							
							case 3:
								printf("\nNumber of exercise 1-10:  ");
								TrueSize = getKeyboardInput(input, INPUT_SIZE);
								holdExerciseNum = getNumberFromStream(input, TrueSize) - 1;
							break;
							
							case 4:
								printf("\nSet Exercise ID:  ");
								TrueSize = getKeyboardInput(input, INPUT_SIZE);
								sched->IndividualExercise[holdExerciseNum].ExerciseID = getNumberFromStream(input, TrueSize);
							break;
							
							case 5:
								for(loop =0 ; loop < SET_NUM; loop++)
								{
									printf("\nset rep number and Weight number:  ");
									TrueSize = getKeyboardInput(input, INPUT_SIZE);
									sched->IndividualExercise[holdExerciseNum].DSet[loop].rep = getNumberFromStream(input, TrueSize);	
									TrueSize = getKeyboardInput(input, INPUT_SIZE);
									sched->IndividualExercise[holdExerciseNum].DSet[loop].weight = getNumberFromStream(input, TrueSize);
								}
							break;
							
							case 6:
								showExerID();
							
						}
						
					}while(i != 0);
				}
				else
				{
					holdExerciseNum = 1;
					while(holdExerciseNum)
					{
						printf("\nNumber of exercise 1-10:  ");
						TrueSize = getKeyboardInput(input, INPUT_SIZE);
						holdExerciseNum = getNumberFromStream(input, TrueSize);
						if(!holdExerciseNum)
							break;
						DisplayInfo(sched, holdExerciseNum - 1);
					}
					
				}

				return 1;
				// final de interrogatorio
				
}
void DisplayInfo(struct Day *sched, int exerNum){
		int loop = 0;
		clrscr();
		printf("%d/%d/%d %s \n%s \n%s ENUM: %d Inx: %d\n       Rep  Weight\n",
		sched->date.m, sched->date.d, sched->date.y, WeekDays[findDayOfWeek(&(sched->date))],
		ExerIDStr[sched->IndividualExercise[exerNum].ExerciseID],
		MGroupStr[sched->MGroup], exerNum + 1,sched->index);
		for( loop = 0; loop < SET_NUM ; loop++)
		{
		printf("          %d    %d\n", sched->IndividualExercise[exerNum].DSet[loop].rep,
		sched->IndividualExercise[exerNum].DSet[loop].weight);
		}
}
void showExerID(){
	int i = 0;
	for (i = 1; i < 41; i++)
	{
			printf("\n%d %s", i,ExerIDStr[i]);
			if(!(i % 11))
			{
			ngetchx();
			}	
	}
	ngetchx();
}

