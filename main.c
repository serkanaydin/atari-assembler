#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basicFunctions.h"
#include "definitions.h"
#include "syntaxer.h"
#include "constantFunctions.h"
#include "variableFunctions.h"
#include "initializer.h"

int main(void){
    initializeTables();
    while(1) {
        char strEnd[2]={'\r','\0'};
        OPNTAB_STRING[6].val.str=strEnd;
        gets(inbuff);
        inbuff[strlen(inbuff)]='\r';
        cix = 0;
        cox = 0;
        direct_statement = 0;
        skblank();
        getlnum();
        setcode(NULL);
        if (binint < 0)
            direct_statement = 1;
        skblank();
        stmstart=cix;
        if (inbuff[cix] == '\n') {
            if (direct_statement == 1)
                continue;

        }
        stmlbd=cox;
        setcode(NULL);
        skblank();
        search(sntab,0);
        cix=bufferIndex;
        setcode(&stenum);
        skblank();
        if(synent()){
            fprintf(stderr,"error\n");
        }
        outbuff[stmstart] = cox;
//        while (inbuff[cix-1]!='\n')
//            outbuff[2]=cox;
        //linelength=getll();
        fprintf(stderr,"ready\n");
    }
}