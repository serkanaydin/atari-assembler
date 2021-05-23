#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "definitions.h"
#include "syntaxer.h"



        int synent() {
    cpc = spc = LABEL[sntab[stenum].val.num].location;
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
            stack[stklvl + 3] = cpc+1;
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
        else if (code ==2 || code ==3 ) {            //or veya return
            if (stklvl == 0)
                return 1;                             //main exit of syntaxer ??  nasıl dönmeli?
            cpc = stack[stklvl + 3];
            stklvl -= 4;
            if (stklvl < 0)
                fail();
        }
        else if ((code>=16)&&(code<=127)) {
            if (!srcont())
                fail();
        }
        else
            printf("unrecognized code in syntax table\n");
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
        stmstart=cix;
        if (inbuff[cix] == '\n') {           //boş satır.
            if (direct_statement == 1) //if no line number
                continue;

        }
        stmlbd=cox;
        setcode(NULL);
        skblank();
        lbuff = inbuff;
        search(sntab,0);
        cix=bufferIndex;
        setcode(NULL);
        skblank();
        if(!synent()){
            printf("error");
        }
        outbuff[stmstart] = cox;
        while (inbuff[cix-1]!='\n')
            outbuff[2]=cox;
        linelength=getll();
    }
}