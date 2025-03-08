#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datelib.h"

/******************************************************************************
Main Function
******************************************************************************/
int main(int argc, char* argv[]) {
    Date* date6 = new_Date(2000,3,1);
    char* printStr = Date_toString(date6);
    printf("%s", printStr);
    int incriment = Date_increment(date6);
    char* printStr2 = Date_toString(date6);
    printf("%s", printStr2);
    delete_Date(date6);
    free(printStr);
    free(printStr2);

    Date* date7 = new_Date(2000,2,29);
    char* printStr3 = Date_toString(date7);
    printf("%s", printStr3);
    int incriment2 = Date_increment(date7);
    char* printStr4 = Date_toString(date7);
    printf("%s", printStr4);
    delete_Date(date7);
    free(printStr3);
    free(printStr4);

    Date* date8 = new_Date(2000,12,31);
    char* printStr5 = Date_toString(date8);
    printf("%s", printStr5);
    int incriment3 = Date_increment(date8);
    char* printStr6 = Date_toString(date8);
    printf("%s", printStr6);
    delete_Date(date8);
    free(printStr5);
    free(printStr6);

    printf("----------------\n");

    Date* ddate6 = new_Date(2000,3,1);
    char* pprintStr = Date_toString(ddate6);
    printf("%s", pprintStr);
    int decriment = Date_decrement(ddate6);
    char* pprintStr2 = Date_toString(ddate6);
    printf("%s", pprintStr2);
    delete_Date(ddate6);
    free(pprintStr);
    free(pprintStr2);

    Date* ddate7 = new_Date(2000,2,29);
    char* pprintStr3 = Date_toString(ddate7);
    printf("%s", pprintStr3);
    int decriment2 = Date_decrement(ddate7);
    char* pprintStr4 = Date_toString(ddate7);
    printf("%s", pprintStr4);
    delete_Date(ddate7);
    free(pprintStr3);
    free(pprintStr4);

    Date* ddate8 = new_Date(2000,1,1);
    char* pprintStr5 = Date_toString(ddate8);
    printf("%s", pprintStr5);
    int decriment3 = Date_decrement(ddate8);
    char* pprintStr6 = Date_toString(ddate8);
    printf("%s", pprintStr6);
    delete_Date(ddate8);
    free(pprintStr5);
    free(pprintStr6);

    printf("----------------\n");

    Date* b = new_Date(2000,1,1);
    Date* a = new_Date(2000,1,31);
    int delta = Date_delta(a,b);
    printf("%d\n", delta);
    delete_Date(a);
    delete_Date(b);

    Date* d = new_Date(2000,2,10);
    Date* c = new_Date(2000,1,1);
    int delta2 = Date_delta(c,d);
    printf("%d\n", delta2);
    delete_Date(d);
    delete_Date(c);

    Date* f = new_Date(2001,1,1);
    Date* e = new_Date(2002,1,1);
    int delta3 = Date_delta(e,f);
    printf("%d\n", delta3);
    delete_Date(e);
    delete_Date(f);
    return EXIT_SUCCESS;
}