// C Header File
// Created 10/5/2002; 1:47:33 AM
//Author: Jeremy F Villalobos
#include <tigcclib.h>
#include "DateMani.h"
#define EXER_NUM 10
#define SET_NUM 4

struct Set{
		unsigned int rep:6, weight:10;
};
struct exercise {
	int ExerciseID;
	struct Set DSet[SET_NUM];
};
struct Day {
		struct date_t date;
		unsigned short int MGroup:3, index:13;		// de 1 al 3 para especificar chest, back o legs
		struct exercise IndividualExercise [EXER_NUM];
		};
struct Sexercise{						///EXERCIS TO SAVE DATA
	int ExerciseID;
	struct Set DSet1;
	struct Set DSet2;
	struct Set DSet3;
	struct Set DSet4;
	
};
struct DaySave{							//DAY TO SAVE DATA
	struct date_t date;
	unsigned short int MGroup: 3, index:13;
		struct Sexercise IdEx1;
		struct Sexercise IdEx2;
		struct Sexercise IdEx3;
		struct Sexercise IdEx4;
		struct Sexercise IdEx5;
		struct Sexercise IdEx6;
		struct Sexercise IdEx7;
		struct Sexercise IdEx8;
		struct Sexercise IdEx9;
		struct Sexercise IdEx10;
	
};
struct ProgramData {  //gravar a un archivo distinto
		unsigned int CurrentIndex;
};

int newDay   (FILE* , struct Day * );
int saveDay  (FILE* , int, struct Day *);
int  readDay  (FILE* , int, struct Day *);
int deleteDay(FILE* , int);
void PointToMem(struct Day*, struct DaySave *);
void MenToPoint(struct Day *, struct DaySave *);
