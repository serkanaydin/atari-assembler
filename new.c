#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "definitions.h"




        int synent() {
    cpc = spc = sntab[stenum].value;
    stklvl = 0;
    six = cix;
    sox = cox;
    while (1) {
        short code = nxsc();
        if (code == 0x0000) {
            code = nxsc();
            stklvl += 4;
            stack[stklvl + 1] = cix;
            stack[stklvl + 2] = cox;
            stack[stklvl + 3] = cpc;
            cpc = code;
        }
        else if (code == 0x0003) { //return
            if (stklvl == 0)
                return 1;
            cpc = stack[stklvl + 3];
            stklvl -= 4;
            if (stklvl < 0)
                fail();
        }
        else if (code == 0x0001) {
            if(echng())
                fail();
        }
        else if (code == 0x0004) {
            if(tncon())
                fail();
        }
        else if (code == 0x0006) {
            if(tscon())
                fail();
        }
        else if (code == 0x0006) {
            if(tnvar())
                fail();
        }
        else if (code == 0x0006) {
            if(tsvar())
                fail();
        }
        else if (code == 0x000a) {
            if (eif())
                fail();
        }
        else if (code==0x0008) {
            if (edata())
                fail();
        }
        else if (code==0x0009) {
            if (erem())
                fail();
        }
    }
}
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
        lbuff = inbuff;
        search(sntab);
        printf("%d",stenum);
        setcode(NULL);
        skblank();
    }
}