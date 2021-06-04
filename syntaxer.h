#include <ctype.h>

int nxsc() {
    return program[++cpc];
}


int erem(){
    return 0;
}

int edata(){
    return 0;
}

int eif(){
    return 0;
}

int echng(){
    outbuff[cox-1] = (char)(program[++cpc]&0x00ff);
    return(0);
}

int fail(){
    while(1){
        code=nxsc();
        while (code<2 || code >3 ){
            if (code == 0 ){
                cpc++;
            }
            code=nxsc();
            fprintf(stderr,"--Fail-- code=%d\n",code);
        }
        if(code==3){
            fprintf(stderr,"--Fail-- code=3 stklvl=%d\n",stklvl);

            if(stklvl==4){
                return 1;
            }
            cpc=stack[stklvl-1];
            stklvl-=4;
            fprintf(stderr,"--Fail-- cpc=%d stklvl=%d\n",cpc,stklvl);
        }
        else{
            if(cix>maxcix){
                maxcix = cix;
            }
            cix = stack[stklvl-3];
            cox = stack[stklvl-2];
            return 0;
        }

    }
}

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
    cpc =  LABEL[sntab[stenum].val.num].location;
    labelName = getLabel(cpc);
    stklvl = 0;

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
        else if (code ==2 || code ==3 ) { //or veya return
            fprintf(stderr,"SYNENT: CODE:%d Stklvl: %d cpc:%d six:%d sox:%d spc:%d\n",code,stklvl,cpc,stack[stklvl-3],stack[stklvl-2],stack[stklvl-1]);
            if (stklvl == 4)
                return 0;
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

