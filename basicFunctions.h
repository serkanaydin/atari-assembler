#include "definitions.h"
#include "table.h"
#include <stdio.h>

void printINBUFF(char* str){
    printf("%-25sCIX = %-2d INBUFF :  ",str,cix);
    for(int i=0;i<50;i++){
        if(i<cix)
            printf(ANSI_COLOR_GREEN "%x|" ANSI_COLOR_RESET,inbuff[i]);
        else
            printf("%x|",inbuff[i]);
    }
    printf("\n");
}
void printOUTBUFF(char* str){
    printf("%-25sCOX = %-2d OUTBUFF : ",str,cox);
    for(int i=0;i<50;i++){
        if(i<cox)
            printf(ANSI_COLOR_GREEN "%x|" ANSI_COLOR_RESET,outbuff[i]);
        else
            printf("%x|",outbuff[i]);
    }
    printf("\n");
}

void printStack(){
    printf(ANSI_COLOR_RED"STACK :\n"ANSI_COLOR_RESET,stklvl);
    for(int i=stklvl ;i>0;i-=4 ){
        printf("Stack level: %d  SPC: %d SOX: %d SIX: %d\n--------------------------\n",i,stack[i-1],stack[i-2],stack[i-3]);
    }
    printf("\n");
}


int labelSearch(char* str){                                         //finds index of str parameter in LABEL array
    for(int i=0;i<114;i++){                                         //which keeps locations and names of labels
        if(strcmp(LABEL[i].name,str)==0){
            return i;}
    }
    return -1;
}
                                                                    //gets different tokens depending on table name
char* getFromTable(void* table){
    char* temp=NULL;
    if(table == sntab){                                             //if table is statement name table
        temp = ((struct table*)(table))[stenum].name;
    }
    else if(table == OPNTAB_STRING) {                               //if opntab string table
        temp = ((struct table *) (table))[stenum].val.str;
   }
    else if(table == VNTP_HEAD){                                    //if variable name table
        temp= getStr(stenum,&VNTP_HEAD);
    }
    return temp;
}

int search(void* table ,int SRCNXT) {                               //It is a deus ex machina searches tokens in different tables
    int size;                                                       //it is size of searching token
    int error;
    int situation=0;
    char* temp;                                                     //it will be the token which will be searched
    if(!SRCNXT)                                                     //if srcnxt==1 it will not initialize stenum as -1 so the search function will continue to search from last index instead of stenum=0
        stenum=-1;
    while(1){
        switch (situation) {                                        //gets new token from table
            case 0: stenum++;
                bufferIndex=cix;
                tableIndex=0;
                if(getFromTable(table) == NULL)
                    return 1;
                error =0;                                           //error is 0 if all the char comparisons are true
            case 1: if(inbuff[bufferIndex] == '.'){                 //wild card check
                    situation=5;
                    break;
                }
            case 2:

                temp=getFromTable(table);                           //it gets token from table and comparises buffer char and token char
                size=strlen(temp);
                if(inbuff[bufferIndex] == temp[tableIndex]){        //if characters are matched
                    situation=3;                                    //goes to check next characters
                    break;
                }
                error=1;                                            //if characters arent matched makes error flag as 1
            case 3: bufferIndex++;                                  //increments indexes to check next chars
                tableIndex++;
                if(tableIndex < size){
                    situation=2;                                    //if size > table index search function goes to get new token from table
                    break;
                }                                                   //if table index >= size of buffer token it is time to make decision whether buffer token and table token are matched
                if(error==0) {                                      //if error flag was not set program returns 0; 0 return means the token was found
                    return 0;
                }
                situation=0;                                        //else goes to get and check new token from table
        }
    }
}
int opnTabSearch(char* str){                                        //searches str token in operator name table and returns index of the token if the token was found
    for(int i=0;i<55;i++){
        if(strcmp(OPNTAB[i].name, str) == 0){
            return i;
        }
    }
    return -1;
}
void setcode(char* a) {                                             //setcode function puts 1 byte to outbuff
    if(a==NULL)
        outbuff[cox++]= '\0';
    else { outbuff[cox++] = *a; }

    printOUTBUFF("SETCODE: ");
    if (cox==0) { printf("line is too long"); }
}

short getlnum() {                                                   //calculates line number and puts to outbuff
    short lNum=0;
    while(inbuff[cix]<=57 && inbuff[cix]>=48){
        lNum*=10;
        lNum+=(short)(inbuff[cix++]-'0');
    }
    printINBUFF("GETLNUM: ");
    binint=lNum;
    char low = (char)(lNum&0xff00);
    char high = (char)(lNum&0x00ff);
    setcode(&low);
    setcode(&high);
    return lNum;
}

void skblank(){                                                     //skips all blanks in inbuff until a non blank character appear
    while (inbuff[cix]==' ')
        cix++;
    printINBUFF("SKBLANK: ");
}



