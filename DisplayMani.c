// C Source File
// Created 10/5/2002; 1:40:16 AM
// manipular la informacion en la pantalla y asignarla a las respectivas variables
// Author: Jeremy F Villalobos
#include "DisplayMani.h" 
#include "FileMani.h"


void DisplaySchedule(void){
		DrawLine( 0,15 ,WIDTH,15,A_NORMAL);
		DrawLine( 0,30 ,WIDTH , 30,A_NORMAL);
		DrawLine( 0,45 ,WIDTH ,45 ,A_NORMAL);
		DrawLine( 0,60 ,WIDTH ,60 ,A_NORMAL);
		DrawLine(0 ,75 ,WIDTH ,75 ,A_NORMAL);
		DrawLine( 0,90 ,WIDTH ,90 ,A_NORMAL);
		DrawLine( 80,0 ,80 ,HEIGHT ,A_NORMAL);
		DrawLine( 20,15 , 15,HEIGHT ,A_NORMAL);
}
void DecisionInput(char input[INPUT_SIZE],struct Day* Gworkout, int pos){
	struct date_t date;
	switch (pos)
	{
		case 1:
					getdate(&date, input);
					if(validDate(&date))
						Gworkout->date = date;  // incluir else statement
			break;
		case 2:
			// handle instruction for exercise cell
			break;
		case 3:
			Gworkout->IndividualExercise.DSet[0].rep = stringNum(input);
			break;
		case 4:
			Gworkout->IndividualExercise.DSet[0].weight = stringNum(input);
			break;
		case 5:
			Gworkout->IndividualExercise.DSet[1].rep = stringNum(input);
			break;
		case 6:
			Gworkout->IndividualExercise.DSet[1].weight = stringNum(input);
			break;
		case 7:
			Gworkout->IndividualExercise.DSet[2].rep = stringNum(input);
			break;
		case 8:
			Gworkout->IndividualExercise.DSet[2].weight = stringNum(input);
			break;
		case 9:
			Gworkout->IndividualExercise.DSet[3].rep = stringNum(input);
			break;
		case 10:
			Gworkout->IndividualExercise.DSet[3].weight = stringNum(input);
			break;	
	}
}
int stringNum(char *str, int size)
{
	int i;  // integer for the loop
	int output = 0;
	for(i = size-1; i >= 0; i--){
		if(isdigit(str[i])){
			output += (str[i] - 48) * pow(10, size - i - 1);
		}
		else{
			printf("not a valide number");
			return 0;
		}
	}
	return output;
	
}
