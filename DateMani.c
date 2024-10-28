// C Source File
// Created 10/5/2002; 1:40:00 AM
//manipular la fechas aqui , averiguar dias, cuando es Martes ?? etc...
// Author: Jeremy F Villalobos

#include "DateMani.h"
//#include <"FileMani.h>
#define RefMonth 8
#define RefDay 3
#define RefYear 3


int IsALeap(int year){
	if(year % 4 == 0)
		return 1;
	else 
		return 0;
}
int getDate(struct date_t* date, char input[INPUT_SIZE]){
	int i, index = 0, move = 0;
	int moveArr[3] = {0,0,0};
	// Algorithmo para leer la fecha y ponerla en numeros
	for(i = 0; i < INPUT_SIZE; i++){
		if((input[i] == '/')||(input[i] == '\0'))
		{
			if(!(i - 2 < index))
				moveArr[move] += (input[i - 2] - 48) * 10;
			if(!(i - 1 < index))
				moveArr[move] += (input[i - 1] - 48);
			if(i <= 0) 
				return DATE_BAD;
			index = i+1;
			move++;
		}
	}
	(*date).m = moveArr[0];
	(*date).d = moveArr[1];
	(*date).y = moveArr[2];

	if(!validDate(date))
		return DATE_BAD;
	else
		return DATE_OK;
}

int validDate(struct date_t *date){
	int m = date->m;
	m--;
	switch(m){
	case 0: case 2: case 4: case 6: case 7: case 9: case 11:
		if((*date).d > 31){
			return 0;
		}else {break;}
	case 1:
		if(IsALeap((*date).y)){
			if((*date).d > 29)
				return 0;
		}
		else 
			if((*date).d > 28)
				return 0;
		
		break;
			
	case 3: case 5: case 8: case 10:
		if((*date).d > 30){
			return 0;
		}
	default:
		if(m > 11)
			return 0;
		}
	if(m < 0 || (*date).d <= 0 || (*date).y < 0)
		return 0;
	return 1;
}


enum day_t findDayOfWeek(struct date_t* date )
{
	enum day_t dayofweek = 0;
	struct date_t one, two = *date;
	int totalDays = 0, backWards_flag = 0;

	one.m = RefMonth;
	one.d = RefDay; 
	one.y = RefYear;

	//if (!validDate(&two) )						NO BORRAR
	//		DlgMessage("notice", "invalid date",BT_OK,BT_NONE);
	if (( two.y < one.y )||(two.m < one.m) ||(two.d < one.d))
	{
		backWards_flag = 1;
	}
	totalDays = DateNum(date);
	totalDays = totalDays % 7;

	if ( backWards_flag == 0 )
	{
	switch ( totalDays )
		{
		case 0:
			dayofweek = SUNDAY;
			break;
		case 1:
			dayofweek = MONDAY;
			break;
		case 2:
			dayofweek = TUESDAY;
			break;
		case 3:
			dayofweek = WEDNESDAY;
			break;
		case 4:
			dayofweek = THURSDAY;
			break;
		case 5:
			dayofweek = FRIDAY;
			break;
		case 6:
			dayofweek = SATURDAY;
			break;
		}
	}
	else
	{
		switch ( totalDays )
		{
		case 0:
			dayofweek = SUNDAY;
			break;
		case 1:
			dayofweek = SATURDAY;
			break;
		case 2:
			dayofweek = FRIDAY;
			break;
		case 3:
			dayofweek = THURSDAY;
			break;
		case 4:
			dayofweek = WEDNESDAY;
			break;
		case 5:
			dayofweek = TUESDAY;
			break;
		case 6:
			dayofweek = MONDAY;
			break;
		}
	}
	return dayofweek;
}
// return the amount of days between to years without counting the day iside the years in question
int dayOfYear(struct date_t one, struct date_t two){
	int years = (two.y / 4 - one.y / 4)- (two.y / 100 - one.y / 100) /*+ (two.y / 400 - one.y /400)*/;
	int temp = two.y - one.y - years;
	int answer = years * 366 + temp * 365 - (365 + IsALeap(two.y));
	if( answer < 0)
		return 0;
	else 
		return answer;

		
}
// day number inside a year   more like Day_inside_year
int Day_OfYear(struct date_t one,struct  date_t two, int sameYear){
	int count = 0, count2 = 0;
int dayOfMonth[] = {0,31,59, 90, 120, 151, 181, 212,243, 273,304, 334,365};
int leapDayOfMonth[] = {0,31,60, 91, 121, 152, 182, 213,244, 274,305, 335,366};
if(IsALeap(two.y))								
	count2 = leapDayOfMonth[two.m - 1]+two.d; 
else	
	count2 = dayOfMonth[two.m -1 ] + two.d;
if(IsALeap(one.y))								
	count = leapDayOfMonth[one.m -1 ] + one.d;
else
	count = dayOfMonth[one.m - 1] + one.d;
if (sameYear)
	return abs(count2 - count);
else
	return count2 + (365 + IsALeap(one.y)) - count;
}
// get the numerical value of a three number date from Month/day/year to int
int DateNum(struct date_t * date){
	int totalDays = 0;
	struct date_t one = {RefMonth, RefDay, RefYear};
	struct date_t temp, two;
	if ( date->y < one.y ){
	temp = one;
	one = *date;
	two = temp;	
	}
	else
	{
		two = *date;
	}
	totalDays = dayOfYear( one, two);
	totalDays += Day_OfYear( one, two, ( one.y == two.y ));
	return totalDays;
}
int DateEqual(struct date_t* one, struct date_t* two){
	if(one->y == two->y){
		if(one->m == two->m)
			if(one->d == two->d)
				return 1;
				}
	return 0;
}
//agregar mas tarde recuento de aucencias
// numero de semana de estar iendo al gym
// numero de mes de estar iendo al gym.
