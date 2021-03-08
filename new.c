#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "definitions.h"
int main(void){
    initializeTables();
    while(1) {
        gets(inbuff);
        cix = 0;
        cox = 0;
        direct_statement = 0;
        skblank();
        getlnum();   //sets binint
        setcode(NULL);
        if (binint < 0)
            direct_statement = 1;
        skblank();
        if (inbuff[cix] == '\n') {           //boş satır.
            if (direct_statement == 1) //if no line number
                continue;

        }
        stmlbd=cox;
        setcode(NULL);
        skblank();
        stenum= sntabSearch();
        setcode(NULL);
        skblank();
    }
}