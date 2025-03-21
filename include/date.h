#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAY_MAX 31
#define MONTH_MAX 12
#define INVALID "\033[0;31m[INVALID]\033[0m %s : %s\n"

typedef struct {
     int day, month, year, hour, minutes;
     char *day_name, *month_name;
} Date;
 
Date* create_day(int, int, int);
Date** create_month(int, int);
Date*** create_year(int);
 
int valid_date(Date);
int get_day_count(int, int);
#endif