// C Source File
// Created 10/5/2002; 1:44:39 AM
// Manipulacion de archivo, gravar a... leer... controlar index etc...
//Author: Jeremy F Villalobos
#include "FileMani.h"


char notice[] = "NOTICE";
/*			string de todos los ejecicios no BORRAR!
char *ExerIDStr[] = {  
		"Chest Press", "Incline Presses", "Decline Dumbbell Press" , "Machine Dips", 			//CHEST 13
		"Tricep Curl",  "Tricep Pullover", "Dubbell Pull Over" ,  												//TRICEP			0-12
		"Subscapularis in", "Subscapularis out","TBA", "TBA" , "TBA" , "TBA",							//MICELANIOUS CHEST
		"Asisted Chin Ups", "Dumbbell Bent-Over Rows", "Machine Row", "Lat Machine Pull Down", 	//BACK 13
		"Dumbbell Bicep Curl",  "Bicep Curl", "TBA" , "TBA", "TBA" ,														//BICEPT	13-25
		"Dumbbell Side Lift", "Dumbbell Front Lift", "Straight Up Press", "Machine Side Lift"	//DELTS
		"Smith Machine Press", "Leg Press", "Leg Curl", "Leg Extencion", 												//PIERNAS 10   26-35
		"Leg Abduction In", "Leg Abduction Out","Calf Machine", "Back",	"TBA", "TBA",						//CALF AND MICS
		"Abs Crounches", "Abs sit up" , "Abs Side Crounch"	,"TBA", "TBA"											// ABS  5 36-40

};
*/
int newDay (FILE *WorkOut, struct Day *ptrG){
	struct DaySave DayS;
	struct ProgramData PData = {0};
	FILE *PDataPtr;
	if( ( PDataPtr = fopen( "Prog", "a+") ) == NULL)
	{
		printf( "File could not be opened.\n");		//try opening file...
		return 0;
	}
	else
	{
		PointToMem(ptrG, &DayS);
		//get current index
		fseek(PDataPtr, 0,SEEK_SET);
		fread(&PData,sizeof(struct ProgramData),1, PDataPtr);
		//create new Day
		DayS.index = PData.CurrentIndex;
		fseek(WorkOut, (PData.CurrentIndex)* sizeof(struct DaySave), SEEK_SET);
		fwrite(&DayS, sizeof( struct DaySave), 1, WorkOut);
		//increase CurrentIndex and save the information
		PData.CurrentIndex++;
		fseek(PDataPtr,0,SEEK_SET);
		fwrite(&PData, sizeof(struct ProgramData), 1, PDataPtr);
	}
	fclose(PDataPtr);
	return 1;
}
int saveDay(FILE * WorkOut, int index, struct Day * ptrG){
	struct DaySave tempDay;
	struct DaySave DayS;
	PointToMem(ptrG, &DayS);
	if(fseek(WorkOut , index * sizeof(struct DaySave), SEEK_SET))
	{
		DlgMessage(notice, "Seek fail", BT_OK,BT_NONE);		
		rewind(WorkOut);
		return 0;	
	}
	else
	{		
		fread(&tempDay, sizeof(struct Day),1 , WorkOut);
		if(tempDay.index == index)
			{
				fseek(WorkOut , index * sizeof(struct DaySave), SEEK_SET);
				fwrite(&DayS, sizeof(struct DaySave), 1 , WorkOut);
			}
		else
			DlgMessage(notice, "Aborting, possible data curruption", BT_OK,BT_NONE);
	}
	return 1;
}

int deleteDay(FILE * WorkOut, int index){
	FILE  *PDataPtr;
	struct ProgramData PData;																////
	struct Day Blank ;	
	struct DaySave BlankS;																		//////
	Blank.date.d = 0;  Blank.date.m = 0; Blank.date.y = 0;	/////////create blank Day
	Blank.MGroup = 0;																				//////
	int i,j; // for the loop																//
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
	//struct Day tempDay;
	struct DaySave tempDayS;
	// open Program Data
	if( ( PDataPtr = fopen( "Prog", "a+") ) == NULL)
	{
		DlgMessage(notice, "File could not be opened.",BT_OK, BT_NONE);
		return 0;
	}
	else
	{
		fseek(PDataPtr, 0, SEEK_SET);
		fread(&PData, sizeof(struct ProgramData), 1 , PDataPtr);
		if(!PData.CurrentIndex)
			return 0; 
		PointToMem(&Blank, &BlankS);
		//PointToMem(&tempDayS, &tempDayS);
		while(!(fseek(WorkOut, (index+ 1) * sizeof(struct DaySave), SEEK_SET)))
			{
				//fseek(WorkOut, (index + 1) *sizeof(struct Day), SEEK_SET);
				fread(&tempDayS, sizeof(struct DaySave), 1 ,WorkOut);
				tempDayS.index--;
				fseek(WorkOut, index * sizeof(struct DaySave),SEEK_SET);
				fwrite(&tempDayS, sizeof(struct DaySave), 1 ,WorkOut);
				index++;
			}
			//set Day record to 0
			rewind(WorkOut);
			fseek(WorkOut, PData.CurrentIndex * sizeof(struct Day), SEEK_SET);
			fwrite(&BlankS, sizeof(struct DaySave),1, WorkOut);
			//setdeleted record to 0
			PData.CurrentIndex--;
			fseek(PDataPtr, 0, SEEK_SET);
			fwrite(&PData, sizeof(struct ProgramData), 1 ,PDataPtr);
	}
	return 1;

}
int readDay(FILE* WorkOut, int index, struct Day * ptrG){
	struct DaySave DayS;
	PointToMem(ptrG, &DayS);
	if(fseek(WorkOut, index * sizeof(struct DaySave), SEEK_SET))
	{
		DlgMessage(notice, "Seek fail!",BT_OK, BT_NONE);
		rewind(WorkOut);
		return 0;
	}
	else
	{
		fread(&DayS, sizeof(struct DaySave), 1, WorkOut);
		if(DayS.index != index)
		{
			DlgMessage(notice, "Day not in use!",BT_OK, BT_NONE);
			return 0;
		}
		MenToPoint(ptrG, &DayS);
	}
		return 1;
}
void PointToMem(struct Day *sched, struct DaySave *SaveSched)
{
  SaveSched->date.d = sched->date.d;
  SaveSched->date.m = sched->date.m;
  SaveSched->date.y = sched->date.y;
  SaveSched->MGroup = sched->MGroup;
  SaveSched->index = sched->index;
  SaveSched->IdEx1.ExerciseID = sched->IndividualExercise[0].ExerciseID;
  SaveSched->IdEx2.ExerciseID = sched->IndividualExercise[1].ExerciseID;
  SaveSched->IdEx3.ExerciseID = sched->IndividualExercise[2].ExerciseID;
  SaveSched->IdEx4.ExerciseID = sched->IndividualExercise[3].ExerciseID;
  SaveSched->IdEx5.ExerciseID = sched->IndividualExercise[4].ExerciseID;
  SaveSched->IdEx6.ExerciseID = sched->IndividualExercise[5].ExerciseID;
  SaveSched->IdEx7.ExerciseID = sched->IndividualExercise[6].ExerciseID;
  SaveSched->IdEx8.ExerciseID = sched->IndividualExercise[7].ExerciseID;
  SaveSched->IdEx9.ExerciseID = sched->IndividualExercise[8].ExerciseID;
  SaveSched->IdEx10.ExerciseID = sched->IndividualExercise[9].ExerciseID;
  
  SaveSched->IdEx1.DSet1.rep = sched->IndividualExercise[0].DSet[0].rep;
  SaveSched->IdEx2.DSet1.rep = sched->IndividualExercise[1].DSet[0].rep;
  SaveSched->IdEx3.DSet1.rep = sched->IndividualExercise[2].DSet[0].rep;
  SaveSched->IdEx4.DSet1.rep = sched->IndividualExercise[3].DSet[0].rep;
  SaveSched->IdEx5.DSet1.rep = sched->IndividualExercise[4].DSet[0].rep;			
  SaveSched->IdEx6.DSet1.rep = sched->IndividualExercise[5].DSet[0].rep;	///1 de 4
  SaveSched->IdEx7.DSet1.rep = sched->IndividualExercise[6].DSet[0].rep;
  SaveSched->IdEx8.DSet1.rep = sched->IndividualExercise[7].DSet[0].rep;
  SaveSched->IdEx9.DSet1.rep = sched->IndividualExercise[8].DSet[0].rep;
  SaveSched->IdEx10.DSet1.rep = sched->IndividualExercise[9].DSet[0].rep;
  
  SaveSched->IdEx1.DSet1.weight = sched->IndividualExercise[0].DSet[0].weight;
  SaveSched->IdEx2.DSet1.weight = sched->IndividualExercise[1].DSet[0].weight;
  SaveSched->IdEx3.DSet1.weight = sched->IndividualExercise[2].DSet[0].weight;
  SaveSched->IdEx4.DSet1.weight = sched->IndividualExercise[3].DSet[0].weight;
  SaveSched->IdEx5.DSet1.weight = sched->IndividualExercise[4].DSet[0].weight;		//1 d 4
  SaveSched->IdEx6.DSet1.weight = sched->IndividualExercise[5].DSet[0].weight;
  SaveSched->IdEx7.DSet1.weight = sched->IndividualExercise[6].DSet[0].weight;
  SaveSched->IdEx8.DSet1.weight = sched->IndividualExercise[7].DSet[0].weight;
  SaveSched->IdEx9.DSet1.weight = sched->IndividualExercise[8].DSet[0].weight;
  SaveSched->IdEx10.DSet1.weight = sched->IndividualExercise[9].DSet[0].weight;
  
  SaveSched->IdEx1.DSet2.rep = sched->IndividualExercise[0].DSet[1].rep;
  SaveSched->IdEx2.DSet2.rep = sched->IndividualExercise[1].DSet[1].rep;
  SaveSched->IdEx3.DSet2.rep = sched->IndividualExercise[2].DSet[1].rep;
  SaveSched->IdEx4.DSet2.rep = sched->IndividualExercise[3].DSet[1].rep;
  SaveSched->IdEx5.DSet2.rep = sched->IndividualExercise[4].DSet[1].rep;			
  SaveSched->IdEx6.DSet2.rep = sched->IndividualExercise[5].DSet[1].rep;		// 2 de 4
  SaveSched->IdEx7.DSet2.rep = sched->IndividualExercise[6].DSet[1].rep;
  SaveSched->IdEx8.DSet2.rep = sched->IndividualExercise[7].DSet[1].rep;
  SaveSched->IdEx9.DSet2.rep = sched->IndividualExercise[8].DSet[1].rep;
  SaveSched->IdEx10.DSet2.rep = sched->IndividualExercise[9].DSet[1].rep;
  
  SaveSched->IdEx1.DSet2.weight = sched->IndividualExercise[0].DSet[1].weight;
  SaveSched->IdEx2.DSet2.weight = sched->IndividualExercise[1].DSet[1].weight;
  SaveSched->IdEx3.DSet2.weight = sched->IndividualExercise[2].DSet[1].weight;
  SaveSched->IdEx4.DSet2.weight = sched->IndividualExercise[3].DSet[1].weight;
  SaveSched->IdEx5.DSet2.weight = sched->IndividualExercise[4].DSet[1].weight;
  SaveSched->IdEx6.DSet2.weight = sched->IndividualExercise[5].DSet[1].weight;		//2 de 4
  SaveSched->IdEx7.DSet2.weight = sched->IndividualExercise[6].DSet[1].weight;
  SaveSched->IdEx8.DSet2.weight = sched->IndividualExercise[7].DSet[1].weight;
  SaveSched->IdEx9.DSet2.weight = sched->IndividualExercise[8].DSet[1].weight;
  SaveSched->IdEx10.DSet2.weight = sched->IndividualExercise[9].DSet[1].weight;
  
  SaveSched->IdEx1.DSet3.rep = sched->IndividualExercise[0].DSet[2].rep;
  SaveSched->IdEx2.DSet3.rep = sched->IndividualExercise[1].DSet[2].rep;
  SaveSched->IdEx3.DSet3.rep = sched->IndividualExercise[2].DSet[2].rep;
  SaveSched->IdEx4.DSet3.rep = sched->IndividualExercise[3].DSet[2].rep;
  SaveSched->IdEx5.DSet3.rep = sched->IndividualExercise[4].DSet[2].rep;			
  SaveSched->IdEx6.DSet3.rep = sched->IndividualExercise[5].DSet[2].rep;			//3 de 4
  SaveSched->IdEx7.DSet3.rep = sched->IndividualExercise[6].DSet[2].rep;
  SaveSched->IdEx8.DSet3.rep = sched->IndividualExercise[7].DSet[2].rep;
  SaveSched->IdEx9.DSet3.rep = sched->IndividualExercise[8].DSet[2].rep;
  SaveSched->IdEx10.DSet3.rep = sched->IndividualExercise[9].DSet[2].rep;
  
  SaveSched->IdEx1.DSet3.weight = sched->IndividualExercise[0].DSet[2].weight;
  SaveSched->IdEx2.DSet3.weight = sched->IndividualExercise[1].DSet[2].weight;
  SaveSched->IdEx3.DSet3.weight = sched->IndividualExercise[2].DSet[2].weight;
  SaveSched->IdEx4.DSet3.weight = sched->IndividualExercise[3].DSet[2].weight;
  SaveSched->IdEx5.DSet3.weight = sched->IndividualExercise[4].DSet[2].weight;
  SaveSched->IdEx6.DSet3.weight = sched->IndividualExercise[5].DSet[2].weight;		//3 de 4
  SaveSched->IdEx7.DSet3.weight = sched->IndividualExercise[6].DSet[2].weight;
  SaveSched->IdEx8.DSet3.weight = sched->IndividualExercise[7].DSet[2].weight;
  SaveSched->IdEx9.DSet3.weight = sched->IndividualExercise[8].DSet[2].weight;
  SaveSched->IdEx10.DSet3.weight = sched->IndividualExercise[9].DSet[2].weight;
  
  SaveSched->IdEx1.DSet4.rep = sched->IndividualExercise[0].DSet[3].rep;
  SaveSched->IdEx2.DSet4.rep = sched->IndividualExercise[1].DSet[3].rep;
  SaveSched->IdEx3.DSet4.rep = sched->IndividualExercise[2].DSet[3].rep;
  SaveSched->IdEx4.DSet4.rep = sched->IndividualExercise[3].DSet[3].rep;
  SaveSched->IdEx5.DSet4.rep = sched->IndividualExercise[4].DSet[3].rep;			
  SaveSched->IdEx6.DSet4.rep = sched->IndividualExercise[5].DSet[3].rep;			//4 de 4
  SaveSched->IdEx7.DSet4.rep = sched->IndividualExercise[6].DSet[3].rep;
  SaveSched->IdEx8.DSet4.rep = sched->IndividualExercise[7].DSet[3].rep;
  SaveSched->IdEx9.DSet4.rep = sched->IndividualExercise[8].DSet[3].rep;
  SaveSched->IdEx10.DSet4.rep = sched->IndividualExercise[9].DSet[3].rep;
  
  SaveSched->IdEx1.DSet4.weight = sched->IndividualExercise[0].DSet[3].weight;
  SaveSched->IdEx2.DSet4.weight = sched->IndividualExercise[1].DSet[3].weight;
  SaveSched->IdEx3.DSet4.weight = sched->IndividualExercise[2].DSet[3].weight;
  SaveSched->IdEx4.DSet4.weight = sched->IndividualExercise[3].DSet[3].weight;
  SaveSched->IdEx5.DSet4.weight = sched->IndividualExercise[4].DSet[3].weight;
  SaveSched->IdEx6.DSet4.weight = sched->IndividualExercise[5].DSet[3].weight;		//4 de 4
  SaveSched->IdEx7.DSet4.weight = sched->IndividualExercise[6].DSet[3].weight;
  SaveSched->IdEx8.DSet4.weight = sched->IndividualExercise[7].DSet[3].weight;
  SaveSched->IdEx9.DSet4.weight = sched->IndividualExercise[8].DSet[3].weight;
  SaveSched->IdEx10.DSet4.weight = sched->IndividualExercise[9].DSet[3].weight;
  

}
void MenToPoint(struct Day *sched, struct DaySave *SaveSched)
{
	sched->date.d = SaveSched->date.d;
  sched->date.m = SaveSched->date.m;
  sched->date.y = SaveSched->date.y;
  sched->MGroup = SaveSched->MGroup;
  sched->index = SaveSched->index;
  sched->IndividualExercise[0].ExerciseID = SaveSched->IdEx1.ExerciseID;
  sched->IndividualExercise[1].ExerciseID = SaveSched->IdEx2.ExerciseID;
  sched->IndividualExercise[2].ExerciseID = SaveSched->IdEx3.ExerciseID;
  sched->IndividualExercise[3].ExerciseID = SaveSched->IdEx4.ExerciseID;
  sched->IndividualExercise[4].ExerciseID = SaveSched->IdEx5.ExerciseID;
  sched->IndividualExercise[5].ExerciseID = SaveSched->IdEx6.ExerciseID;
  sched->IndividualExercise[6].ExerciseID = SaveSched->IdEx7.ExerciseID;
  sched->IndividualExercise[7].ExerciseID = SaveSched->IdEx8.ExerciseID;
  sched->IndividualExercise[8].ExerciseID = SaveSched->IdEx9.ExerciseID;
  sched->IndividualExercise[9].ExerciseID = SaveSched->IdEx10.ExerciseID;
  
  sched->IndividualExercise[0].DSet[0].rep = SaveSched->IdEx1.DSet1.rep; 
  sched->IndividualExercise[1].DSet[0].rep = SaveSched->IdEx2.DSet1.rep; 
  sched->IndividualExercise[2].DSet[0].rep = SaveSched->IdEx3.DSet1.rep; 
  sched->IndividualExercise[3].DSet[0].rep = SaveSched->IdEx4.DSet1.rep; 
  sched->IndividualExercise[4].DSet[0].rep = SaveSched->IdEx5.DSet1.rep; 
  sched->IndividualExercise[5].DSet[0].rep = SaveSched->IdEx6.DSet1.rep; 				// 1 de 4
  sched->IndividualExercise[6].DSet[0].rep = SaveSched->IdEx7.DSet1.rep; 
  sched->IndividualExercise[7].DSet[0].rep = SaveSched->IdEx8.DSet1.rep; 
  sched->IndividualExercise[8].DSet[0].rep = SaveSched->IdEx9.DSet1.rep; 
  sched->IndividualExercise[9].DSet[0].rep = SaveSched->IdEx10.DSet1.rep; 
  
  sched->IndividualExercise[0].DSet[0].weight = SaveSched->IdEx1.DSet1.weight;
  sched->IndividualExercise[1].DSet[0].weight = SaveSched->IdEx2.DSet1.weight;
  sched->IndividualExercise[2].DSet[0].weight = SaveSched->IdEx3.DSet1.weight;
  sched->IndividualExercise[3].DSet[0].weight = SaveSched->IdEx4.DSet1.weight;
  sched->IndividualExercise[4].DSet[0].weight = SaveSched->IdEx5.DSet1.weight;
  sched->IndividualExercise[5].DSet[0].weight = SaveSched->IdEx6.DSet1.weight;		// 1 de 4
  sched->IndividualExercise[6].DSet[0].weight = SaveSched->IdEx7.DSet1.weight;
  sched->IndividualExercise[7].DSet[0].weight = SaveSched->IdEx8.DSet1.weight;
  sched->IndividualExercise[8].DSet[0].weight = SaveSched->IdEx9.DSet1.weight;
  sched->IndividualExercise[9].DSet[0].weight = SaveSched->IdEx10.DSet1.weight;
  
  sched->IndividualExercise[0].DSet[1].rep = SaveSched->IdEx1.DSet2.rep; 
  sched->IndividualExercise[1].DSet[1].rep = SaveSched->IdEx2.DSet2.rep; 
  sched->IndividualExercise[2].DSet[1].rep = SaveSched->IdEx3.DSet2.rep; 
  sched->IndividualExercise[3].DSet[1].rep = SaveSched->IdEx4.DSet2.rep; 
  sched->IndividualExercise[4].DSet[1].rep = SaveSched->IdEx5.DSet2.rep; 
  sched->IndividualExercise[5].DSet[1].rep = SaveSched->IdEx6.DSet2.rep; 				// 2 de 4
  sched->IndividualExercise[6].DSet[1].rep = SaveSched->IdEx7.DSet2.rep; 
  sched->IndividualExercise[7].DSet[1].rep = SaveSched->IdEx8.DSet2.rep; 
  sched->IndividualExercise[8].DSet[1].rep = SaveSched->IdEx9.DSet2.rep; 
  sched->IndividualExercise[9].DSet[1].rep = SaveSched->IdEx10.DSet2.rep; 
  
  sched->IndividualExercise[0].DSet[1].weight = SaveSched->IdEx1.DSet2.weight;
  sched->IndividualExercise[1].DSet[1].weight = SaveSched->IdEx2.DSet2.weight;
  sched->IndividualExercise[2].DSet[1].weight = SaveSched->IdEx3.DSet2.weight;
  sched->IndividualExercise[3].DSet[1].weight = SaveSched->IdEx4.DSet2.weight;
  sched->IndividualExercise[4].DSet[1].weight = SaveSched->IdEx5.DSet2.weight;
  sched->IndividualExercise[5].DSet[1].weight = SaveSched->IdEx6.DSet2.weight;		// 2 de 4
  sched->IndividualExercise[6].DSet[1].weight = SaveSched->IdEx7.DSet2.weight;
  sched->IndividualExercise[7].DSet[1].weight = SaveSched->IdEx8.DSet2.weight;
  sched->IndividualExercise[8].DSet[1].weight = SaveSched->IdEx9.DSet2.weight;
  sched->IndividualExercise[9].DSet[1].weight = SaveSched->IdEx10.DSet2.weight;
  
  sched->IndividualExercise[0].DSet[2].rep = SaveSched->IdEx1.DSet3.rep; 
  sched->IndividualExercise[1].DSet[2].rep = SaveSched->IdEx2.DSet3.rep; 
  sched->IndividualExercise[2].DSet[2].rep = SaveSched->IdEx3.DSet3.rep; 
  sched->IndividualExercise[3].DSet[2].rep = SaveSched->IdEx4.DSet3.rep; 
  sched->IndividualExercise[4].DSet[2].rep = SaveSched->IdEx5.DSet3.rep; 
  sched->IndividualExercise[5].DSet[2].rep = SaveSched->IdEx6.DSet3.rep; 				// 3 de 4
  sched->IndividualExercise[6].DSet[2].rep = SaveSched->IdEx7.DSet3.rep; 
  sched->IndividualExercise[7].DSet[2].rep = SaveSched->IdEx8.DSet3.rep; 
  sched->IndividualExercise[8].DSet[2].rep = SaveSched->IdEx9.DSet3.rep; 
  sched->IndividualExercise[9].DSet[2].rep = SaveSched->IdEx10.DSet3.rep; 
  
  sched->IndividualExercise[0].DSet[2].weight = SaveSched->IdEx1.DSet3.weight;
  sched->IndividualExercise[1].DSet[2].weight = SaveSched->IdEx2.DSet3.weight;
  sched->IndividualExercise[2].DSet[2].weight = SaveSched->IdEx3.DSet3.weight;
  sched->IndividualExercise[3].DSet[2].weight = SaveSched->IdEx4.DSet3.weight;
  sched->IndividualExercise[4].DSet[2].weight = SaveSched->IdEx5.DSet3.weight;
  sched->IndividualExercise[5].DSet[2].weight = SaveSched->IdEx6.DSet3.weight;		// 3 de 4
  sched->IndividualExercise[6].DSet[2].weight = SaveSched->IdEx7.DSet3.weight;
  sched->IndividualExercise[7].DSet[2].weight = SaveSched->IdEx8.DSet3.weight;
  sched->IndividualExercise[8].DSet[2].weight = SaveSched->IdEx9.DSet3.weight;
  sched->IndividualExercise[9].DSet[2].weight = SaveSched->IdEx10.DSet3.weight;
  
  sched->IndividualExercise[0].DSet[3].rep = SaveSched->IdEx1.DSet4.rep; 
  sched->IndividualExercise[1].DSet[3].rep = SaveSched->IdEx2.DSet4.rep; 
  sched->IndividualExercise[2].DSet[3].rep = SaveSched->IdEx3.DSet4.rep; 
  sched->IndividualExercise[3].DSet[3].rep = SaveSched->IdEx4.DSet4.rep; 
  sched->IndividualExercise[4].DSet[3].rep = SaveSched->IdEx5.DSet4.rep; 
  sched->IndividualExercise[5].DSet[3].rep = SaveSched->IdEx6.DSet4.rep; 				// 4 de 4
  sched->IndividualExercise[6].DSet[3].rep = SaveSched->IdEx7.DSet4.rep; 
  sched->IndividualExercise[7].DSet[3].rep = SaveSched->IdEx8.DSet4.rep; 
  sched->IndividualExercise[8].DSet[3].rep = SaveSched->IdEx9.DSet4.rep; 
  sched->IndividualExercise[9].DSet[3].rep = SaveSched->IdEx10.DSet4.rep; 
  
  sched->IndividualExercise[0].DSet[3].weight = SaveSched->IdEx1.DSet4.weight;
  sched->IndividualExercise[1].DSet[3].weight = SaveSched->IdEx2.DSet4.weight;
  sched->IndividualExercise[2].DSet[3].weight = SaveSched->IdEx3.DSet4.weight;
  sched->IndividualExercise[3].DSet[3].weight = SaveSched->IdEx4.DSet4.weight;
  sched->IndividualExercise[4].DSet[3].weight = SaveSched->IdEx5.DSet4.weight;
  sched->IndividualExercise[5].DSet[3].weight = SaveSched->IdEx6.DSet4.weight;		// 4 de 4
  sched->IndividualExercise[6].DSet[3].weight = SaveSched->IdEx7.DSet4.weight;
  sched->IndividualExercise[7].DSet[3].weight = SaveSched->IdEx8.DSet4.weight;
  sched->IndividualExercise[8].DSet[3].weight = SaveSched->IdEx9.DSet4.weight;
  sched->IndividualExercise[9].DSet[3].weight = SaveSched->IdEx10.DSet4.weight;
  
  
  

}

