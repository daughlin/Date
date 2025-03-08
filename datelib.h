#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Date {
   int year;
   int month;
   int day;
} Date;

Date* new_Date(int year, int month, int day);
int init_Date(Date* date, int year, int month, int day);
void delete_Date(Date* date);
bool Date_isValid(Date* date);
int Date_compare(Date* a, Date* b);
char* Date_toString(Date* date);
int Date_increment(Date* date);
int Date_decrement(Date* date);
int Date_delta(Date* a, Date* b);