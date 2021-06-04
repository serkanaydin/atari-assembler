#include "definitions.h"
#include "table.h"
#include <stdio.h>
int labelSearch(char* str){
    for(int i=0;i<114;i++){
        if(strcmp(LABEL[i].name,str)==0){
            return i;}
    }
    return -1;
}

char* getFromTable(void* table){
    char* temp=NULL;
    if(table == sntab){
        temp = ((struct table*)(table))[stenum].name;
    }
    else if(table == OPNTAB_STRING) { temp = ((struct table *) (table))[stenum].val.str; }
    else if(table == VNTP_HEAD){
        temp= getStr(stenum,&VNTP_HEAD);
    }
    return temp;
}

int search(void* table ,int SRCNXT) {  //srcadr is the address of the table, srcskip is the skip factor..
    int size;
    int error;
    int situation=0;
    char* temp;
    if(!SRCNXT)
        stenum=-1;
    while(1){
        switch (situation) {
            case 0: stenum++;
                bufferIndex=cix;
                tableIndex=0;
                if(getFromTable(table) == NULL)
                    return 1;
                error =0;
            case 1: if(inbuff[bufferIndex] == '.'){
                    situation=5;
                    break;
                }
            case 2:

                temp=getFromTable(table);
                size=strlen(temp);
                if(inbuff[bufferIndex] == temp[tableIndex]){
                    situation=3;
                    break;
                }
                error=1;
            case 3: bufferIndex++;
                tableIndex++;
                if(tableIndex < size){
                    situation=1;
                    break;
                }
                if(error==0) {
                    return 0;
                }
                situation=0;
        }
    }
}
int opnTabSearch(char* str){
    for(int i=0;i<55;i++){
        if(strcmp(OPNTAB[i].name, str) == 0){
            return i;
        }
    }
    return -1;
}
void setcode(char* a) {
    if(a==NULL)
        outbuff[cox++]= '\0';
    else { outbuff[cox++] = *a; }
    fprintf(stderr,"SETCODE-> COX:%d OUTBUFF: ",cox);
    for(int i=0;i<=cox;i++){
        fprintf(stderr,"%x|",outbuff[i]);
    }
    fprintf(stderr,"\n");
    if (cox==0) { printf("line is too long"); }
}

short getlnum() {
    short lNum=0;
    while(inbuff[cix]<=57 && inbuff[cix]>=48){
        lNum*=10;
        lNum+=(short)(inbuff[cix++]-'0');
    }
    binint=lNum;
    char low = (char)(lNum&0xff00);
    char high = (char)(lNum&0x00ff);
    setcode(&low);
    setcode(&high);
    return lNum;
}

void skblank(){
    while (inbuff[cix]==' ')
        cix++;
}



