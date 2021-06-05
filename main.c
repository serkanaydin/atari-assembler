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
    initializeTables();                                  //reads tables statement name table, operator token table, syntax table and
                                                        //creates program[] array what is syntax table
    while(1) {                                          //program editor loop: takes input from and tokenizes
        char strEnd[2]={'\r','\0'};
        OPNTAB_STRING[6].val.str=strEnd;                //added because program doesnt read \r as char from opntab-string-values.txt
        gets(inbuff);                                   //gets input from user
        inbuff[strlen(inbuff)]='\r';
        cix = 0;                                        //initializes input buffer index as 0
        cox = 0;                                        //initializes output buffer index as 0
        direct_statement = 0;                           //initializes direct statement flag as 0(direct statements execute program)
        skblank();                                      //skips blanks
        getlnum();                                      //gets line number from input and locates to outbuff's first 2 byte
        setcode(NULL);                               //leaves 1 byte space for line length after syntax operation editor will replace as line number
        if (binint < 0)                                 //binint was set in getlnum function. binint is default 8000 if user enter line number its set in getlnum
            direct_statement = 1;
        skblank();
        stmstart=cix;                                   //statement start index
        if (inbuff[cix] == '\n') {                      //if program editor is at end of the line and direct statement(user enters blank line)
            if (direct_statement == 1)                  //program editor goes to request new line
                continue;

        }
        stmlbd=cox;                                     //stmlbd keeps the index which will be determined as statement length
        setcode(NULL);                               //reserves 1 byte space for statement length
        skblank();
        search(sntab,0);                        //searches the next token in statement table. if finds keeps the statement's index as stenum
        cix=bufferIndex;                                //equalizes input buffer index to old buffer index + token size
        setcode(&stenum);                               //5. index of outbuff is become statement number
        skblank();
        if(synent()){                                   //calls the synaxer..
            fprintf(stderr,"error\n");           //if an error occures synent returns 1
        }
            outbuff[2]=cox;                             //sets line length
            outbuff[stmlbd]=cox;                        //sets statement length

        printf("SETCODE-> COX:%d OUTBUFF: ",cox);       //debug output
        for(int i=0;i<256;i++){
            if(i<cox)
                printf(ANSI_COLOR_GREEN "%x|" ANSI_COLOR_RESET,outbuff[i]);
            else
            printf("%x|",outbuff[i]);
            if(i%64==0)
               printf("\n");
        }
        printf("\n");
        printf("ready\n");                      //writes to user ready to get a new line
    }
}