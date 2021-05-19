#include <ctype.h>
int nxsc() {
    return program[++cpc];    //cpc points to the syntax_table[]
}
int srcont(){
    skblank();
    char temp=cix;
    if(temp != svontx){
        svontx= temp;
        if(search(OPNTAB_STRING)){                     //STENUMU AYARLIYOR
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
        search(head);
    }
    else{
        return 1;                           //error
    }



    return 1;
}

int tnvar(){
    return 0;
}

int tsvar(){
    return 0;
}

