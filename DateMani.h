// C Header File
// Created 10/5/2002; 1:46:44 AM
// Author: Jeremy F Villalobos
#include <tigcclib.h>
#define DATE_OK 1
#define DATE_BAD 0
#define INPUT_SIZE 10
struct date_t {
  unsigned short int m:4, d:6 , y:6;
};
enum day_t
  {SUNDAY,
   MONDAY,
   TUESDAY,
   WEDNESDAY,
   THURSDAY,
   FRIDAY,
   SATURDAY
  };

getDate ( struct date_t *, char [INPUT_SIZE]);
enum day_t findDayOfWeek(struct date_t*);
int DateNum(struct date_t * );
int Day_OfYear( struct date_t,struct date_t, int);
int dayOfYear( struct date_t, struct date_t);
int validDate(struct date_t *);
int DateEqual(struct date_t*, struct date_t*);
