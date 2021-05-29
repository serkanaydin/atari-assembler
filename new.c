#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "definitions.h"
#include "syntaxer.h"
char* labelName;
char* getLabel(long location){
    int i;
     for(i=0;i<120;i++){
        if(LABEL[i].location==location)
            break;
    }
    return LABEL[i].name;

}

        int synent() {
    cpc = spc = LABEL[sntab[stenum].val.num].location;
    labelName = getLabel(cpc);
    stklvl = 0;
    six = cix;
    sox = cox;
            stack[1]=cix;
            stack[2]=cox;
            stack[3]=cpc;   //record the present address.
            stklvl+=4;

            while (1) {
        code = nxsc();
        if (code == 0x0000) {
            code = nxsc();
            stack[stklvl + 1] = cix;
            stack[stklvl + 2] = cox;
            stack[stklvl + 3] = cpc;
            cpc = code;
            labelName = getLabel(code);
            fprintf(stderr,"LABEL=%s\n",getLabel(code));
            stklvl += 4;
            fprintf(stderr,"Stklvl: %d cpc:%d six:%d sox:%d spc:%d\n",stklvl,cpc,stack[stklvl-3],stack[stklvl-2],stack[stklvl-1]);
        }
        else if (code == 0x0001) {
            if(echng())
                if(fail()){
                    return 1;
                }
        }
        else if (code == 0x0004) {
            if(tncon())
                if(fail()){
                    return 1;
                }
        }
        else if (code == 0x0005) {
            if(tnvar())
                if(fail()){
                    return 1;
                }
        }
        else if (code == 0x0006) {
            if(tscon())
                if(fail()){
                    return 1;
                }
        }
        else if (code == 0x0007) {
            if(tsvar())
                if(fail()){
                    return 1;
                }
        }
        else if (code == 0x000a) {
            if (eif())
                if(fail()){
                    return 1;
                }
        }
        else if (code==0x0008) {
            if (edata())
                if(fail()){
                    return 1;
                }
        }
        else if (code==0x0009) {
            if (erem())
                if(fail()){
                    return 1;
                }
        }
        else if (code ==2 || code ==3 ) {//or veya return
            fprintf(stderr,"SYNENT: CODE:%d Stklvl: %d cpc:%d six:%d sox:%d spc:%d\n",code,stklvl,cpc,stack[stklvl-3],stack[stklvl-2],stack[stklvl-1]);
            if (stklvl == 0)
                return 0;                             //main exit of syntaxer ??  nasıl dönmeli?
            cpc = stack[stklvl - 1];
            stklvl -= 4;
            if (stklvl < 0)
                fail();
        }
        else if ((code>=16)&&(code<=127)) {
            if (srcont())
                if(fail()){
                    return 1;
                }
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