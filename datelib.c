/**
 * @file datelib.c
 * @author Cole Amacker
 * @date 2025-02-25
 * @brief Setup for Date construct with many helper functions and other functionality such as increment, decrement, and checking the difference in days between dates.
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "datelib.h"
#include <errno.h>
#include <math.h>
#include <string.h>
#include <strings.h>

/**
 * @brief Checks if inputted date is in a leap year
 * 
 * @param date The date to be checked
 */
 bool isLeapYear(Date* date){
    if(date->year % 4 == 0){
        if(date->year % 100 != 0 || date->year % 400 == 0){
            return true;
        } else {
            return false;
        }
    }
    return false;
}

/**
 * @brief Allocates memory and initializes a new Date with given arguments
 * 
 * @param year The year value to store in the new Date
 * @param month The month value to store in the new Date
 * @param day The day value to store in the new Date
 * @return Date* A pointer to the newly allocated and initialized Date or NULL
 *         if the arguments do not represent a valid date.
 */
Date* new_Date(int year, int month, int day) {
    Date* date = (Date*) malloc(sizeof(Date));
    int val = init_Date(date,year,month,day);
    if(val == 1) {
        return NULL;
    }
    return date;
}

/**
 * @brief Initializes date with given arguments and indicates if date is valid
 * 
 * @param date A Date* where the given arguments should be stored
 * @param year The year value to store in the provided Date
 * @param month The month value to store in the provided Date
 * @param day The day value to store in the provided Date
 * @return 0 if year, month, and day represent a valid date, otherwise 1
 */
int init_Date(Date* date, int year, int month, int day) {
    date->year = year;
    date->month = month;
    date->day = day;
    if(Date_isValid(date)){
        return 0;
    } 
    return 1;
}

/**
 * @brief Deinitializes and frees memory from a date (or does nothing if null)
 * 
 * @param date The Date struct to be deleted
 */
void delete_Date(Date* date) {
    // TODO: Implement this function
    if (date == NULL) {
        return;
    }
    free(date);
}

/**
 * @brief Checks for valid Anno Domini dates on Gregorian calendar
 * 
 * @param date The date to be evaluated
 * @return true if the date is valid in anno domini and gregorian systems
 * @return false if the date is null or not valid in anno domini and gregorian systems
 */
bool Date_isValid(Date* date) {
    //check for proper input
    if(date->year == 0) {
        printf("invalid\n");
        return false;
    //checks for improper month
    } else if (date->month > 12 || date->month < 1) {
        return false;
    } else {
        //checks for day too low
        if (date->day < 1) {
            return false;
        }
        //multiple if statements to check if day is too high for each month
        if (date->month == 2){
            if (isLeapYear(date)){
                if (date->day > 29){
                    return false;
                }
            } else if (date->day > 28) {
                return false;
            }
        }
        if(date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) {
            if (date->day > 30){
                return false;
            }
        } else {
            if (date->day > 31) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Determines if one date occurs before or after another
 * 
 * This function should set errno to EINVAL to indicate an invalid argument if 
 * either of the two given dates is not a valid date.
 * 
 * @param a The first date for comparison
 * @param b The second date for comparison
 * @return 1 if a is after b | 0 if a and b are the same | -1 if a is before b
 */
int Date_compare(Date* a, Date* b) {
    errno = 0;
    //checks if inputted dates are valid, arbitrary return value for error
    if(!Date_isValid(a) || !Date_isValid(b)) {
        errno = EINVAL;
        return 5;
    }
    //checks if years are same
    if(a->year < b->year) {
        return -1;
    } else if (a->year> b->year) {
        return 1;
    } else {
        //checks if months are same if years are same
        if (a->month < b->month) {
            return -1;
        } else if (a->month > b->month) {
            return 1;
        } else {
            //checks if days are same if months are same
            if (a->day < b->day) {
                return -1;
            } else if (a->day > b->day) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @brief Allocates memory and creates a string of the given date
 * 
 * @param date The date to be represented as a string
 * @return char* Representing the date if valid, else NULL
 */
char* Date_toString(Date* date) {
    if(!Date_isValid(date)) {
        return NULL;
    }
    //num allows for appropriate amount of bits
    int bitCount = 11;
    int yrLn = floor(log10(date->year) + 1);
    int dayLn = floor(log10(date->day) + 1);
    bitCount = bitCount + yrLn + dayLn;
    int mon = date->month;
    //collection of months as strings to be referenced
    char months[12][10] = {"January","February","March","April", "May", "June", "July", "August", "September", "October", "November", "December"};
    bitCount += strlen(months[mon-1]);
    char cent[2][3]= {"AD","BC"};
    int period;
    //period 0 = ad, 1 = bc
    if (date->year > 0){
        period = 0;
    } else {
        period = 1;
    }
    //assembly of string to be returned
    char* returnStr = malloc(bitCount*sizeof(char));
    snprintf(returnStr, bitCount, "%s %d, %s %d\n", months[mon-1], date->day, cent[period], date->year);
    return returnStr;
}


/**
 * @brief Increments month forward once resetting the year and day as necessary, returns 0 always as only used with correct inputs inside the construct functions
 * 
 * @param date The Date struct to be incremented
 */
int nextMonth (Date* date) {
    //sets day to 1 because month is moving forwards
    date->day = 1;
    //if it is december, increments to next year
    if(date->month == 12){
        date->month = 1;
        date->year += 1;
    } else {
        //otherwise just goes forwards a month
        date->month = date->month+1;
    }
    return 0;
}

/**
 * @brief Increments the given date to the next valid date
 * 
 * Given a valid date, advance to the next valid date i.e. if given a date that 
 * represents March 3rd 2023, increment it to March 4th 2023. The value of the 
 * date argument itself is changed (this is our Date equivalent of i++)
 * 
 * @param date The date to be incremented
 * @return 0 if the operation was successful otherwise 1 (e.g. invalid date)
 */
int Date_increment(Date* date) {
    //check if date is valid (1 = error)
    if(!Date_isValid(date)){
        return 1;
    }
    //checks if month needs to be incremented for each month's last day
    if (date->month == 2){
        if (isLeapYear(date)){
            if (date->day == 29){
                return nextMonth(date);
            }
        } else if (date->day == 28) {
            return nextMonth(date);
        }
    } else if(date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) {
        if (date->day == 30){
            return nextMonth(date);
        }
    } else if (date->day == 31) {
            return nextMonth(date);
    }
    //otherwise just increments day
    date->day++;
    return 0;
}

/**
 * @brief Decrements the given date to most recent valid previous date
 * 
 * Given a valid date, go back to the previous valid date i.e. if given a date 
 * that represents March 1st 2023, decrement it to February 28th 2023. The value 
 * of the date argument itself is changed (this is our Date equivalent of i--)
 * 
 * @param date The date to be decremented
 * @return 0 if the operation was successful otherwise 1 (e.g. invalid date)
 */
int Date_decrement(Date* date) {
    //check for valid date
    if(!Date_isValid(date)){
        return 1;
    }
    //if month needs to be decremented, checks what day it should be set to for each month's last day
    if(date->day == 1){
        //if month is january, moves to december of previous year
        if (date->month == 1){
            date->year = date->year - 1;
            date->month = 12;
            date->day = 31;
        } else {
            date->month = date->month - 1;
            if (date->month == 2){
                if (isLeapYear(date)){
                    date->day = 29;      
                 } else {
                    date->day = 28;
                }
            } else if(date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) {
                date->day = 30;
            } else {
                date->day = 31;
            }
        }
    } else {
        //otherwise just decrements day
        date->day--;
    }
    return 0;
}

/**
 * @brief Determines the number of days to get from b to a
 * 
 * This function should set errno to EINVAL to indicate an invalid argument if 
 * either of the two given dates is not a valid date.
 * 
 * @param a The first date to evaluate
 * @param b The second date to evalute
 * @return int number of days from b to a (negative if a occurs before b)
 */
int Date_delta(Date* a, Date* b) {
    //copy of date b that can be incremented without 
    Date* dateToIncrement = new_Date(b->year,b->month,b->day);
    int counter = 0;
    //checks if inputted dates are valid
    if(!Date_isValid(a) || !Date_isValid(b)) {
        errno = EINVAL;
        delete_Date(dateToIncrement);
        return 0;
    }
    //if dates are already equal just return 0
    if(Date_compare(a,b) == 0) {
        delete_Date(dateToIncrement);
        return counter;
        //if a is after b, increment forwards and count difference
    } else if (Date_compare(a,b) == 1) {
        while(Date_compare(a,b) != 0) {
            Date_increment(b);
            counter++;
        }
        delete_Date(dateToIncrement);
        return counter;
        //if a is before b, increment backwards and count difference
    } else {
        while(Date_compare(a,b)!= 0) {
            Date_decrement(b);
            counter--;
        }
        delete_Date(dateToIncrement);
        return counter;
    }
}

