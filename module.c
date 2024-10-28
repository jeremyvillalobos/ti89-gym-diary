// C Source File
// Created 1/6/2003; 2:34:54 AM
//Author: Jeremy F Villalobos
#include "module.h"
	void DisplaySchedule(void){
		DrawLine( 0,15 ,WIDTH,15,A_NORMAL);
		DrawLine( 0,30 ,WIDTH , 30,A_NORMAL);
		DrawLine( 0,45 ,WIDTH ,45 ,A_NORMAL);
		DrawLine( 0,60 ,WIDTH ,60 ,A_NORMAL);
		DrawLine(0 ,75 ,WIDTH ,75 ,A_NORMAL);
		DrawLine( 0,90 ,WIDTH ,90 ,A_NORMAL);
		DrawLine( 80,0 ,80 ,HEIGHT ,A_NORMAL);
		DrawLine( 20,15 , 20,HEIGHT ,A_NORMAL);
}
