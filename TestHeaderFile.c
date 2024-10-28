// C Source File
// Created 8/9/2003; 1:37:01 AM
#include "TestHeaderFile.h"
// Author: Jeremy F Villalobos
void testFunc(void){
	clrscr();
	printf("test function");
}
void changeSpace( struct space *Ospace, int one, int two, int three){
	(*Ospace).x = one;
	(*Ospace).y = two;
	(*Ospace).z = three;
}
