#include <ctype.h>
int nxsc() {
    return program[++cpc];    //cpc points to the syntax_table[]
}
int srcont(){
    skblank();
    char temp=cix;
    if(temp != svontx){
        svontx= temp;
        if(search(OPNTAB_STRING,0)){                     //STENUMU AYARLIYOR
            svontc =0;
            return 1;
        }
        svontl = bufferIndex;
        temp = OPNTAB[stenum].val.num;                   //
        svontc = temp;
    }
    temp = program[cpc];
    if(svontc == temp){
        setcode(temp);
        cix = svontl;
        return 1;
    }
    else if(temp >= 0x44) {
        setcode(svontc);
        cix = svontl;
        return 1; }
    else{
        svontc='\0';
        return 0;
    }
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
    outbuff[cox-1] = (char)(program[cpc++]&0x00ff); //outbuff is a char arr but program short arr
    return(1);
}

void fail(){

}

int tncon(){

}

int tscon(){

}
int tvar(int tvtype){
    skblank();
    tvscix=cix;
    if(isalpha(inbuff[cix])) {
        srcont();
        if (svontc == 0 || (svontc == 1) && (inbuff[svontl] >= 0x30)) {  //not reserved word, or it is
            do                                                  //a non-reserved word whose prefix
                cix++;                                //is a reserved word..
            while (!isalpha(inbuff[cix]) | !isdigit(inbuff[cix]));
        }
        if (tvtype == 0x80 ) {
            if (inbuff[cix] == '$')
                cix++;                          //skip over $
            else
                return 1;
        }
        else if ( tvtype == 0x0 ) {
            if (inbuff[cix] == '(') {
                cix++;      //skip over (
                tvtype += 0x40;
            } else
                return 1;
        }
        char temp=cix;
        cix=tvscix;    //search expects the string to be searched pointed by cix.
        tvscix=temp;  //variable string'in sonunu tvscix'e attık.. search
        int result=search(VNTP_HEAD,0);
        while(!result){
            if(bufferIndex==tvscix){
                break;
            }
            else{
                result=search(VNTP_HEAD,1);
            }
        }
        if (result == 1){
            cix=tvscix-cix-1;
            addToTABLE(VNTP_HEAD,VNTP_TAIL);
            char tempVname[200];
            memcpy(tempVname,(inbuff+cix-1),cix);
            VNTP_TAIL->name=tempVname;
            addToTABLE(STMTAB_HEAD,STMTAB_TAIL);
            svvvte++;
            char* stmtabTemp= (char*)(calloc(8,1));
            STMTAB_TAIL->entry=stmtabTemp;

            if(tvtype==0x40)
                --tvscix;
            cix=tvscix;
            if (stenum>0x7f)
                return 1;
            setcode(&stenum);
        }
    }
    else{
        return 1;                           //error
    }



    return 1;
}

int tnvar(){
    return tvar(0x00);
}

int tsvar(){
    return tvar(0x80);
}

