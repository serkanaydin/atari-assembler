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
            svontc ='\0';
            return 1;
        }
        svontl = bufferIndex;
        temp = OPNTAB[stenum].val.str;                   //
        svontc = temp;
    }
    temp = program[cpc];
    fprintf(stderr,"--SRCONT-- cix=%d temp=%d svontc=%d\n",cix,temp,svontc);
    if(svontc == temp){
        fprintf(stderr,"SRCONT - SETCODE-- cix=%d SVONTC=%d temp=%d\n",cix,svontc,temp);
        setcode(&temp);
        cix = svontl;
        return 0;
    }
    else if((temp == 0x44)&&( 0x44 <= svontc)) {
        setcode(&svontc);
        cix = svontl;
        return 0; }
    else{
        //svontc='\0';              //comment out
        return 1;
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
    outbuff[cox-1] = (char)(program[++cpc]&0x00ff); //outbuff is a char arr but program short arr
    return(0);
}

int fail(){
    while(1){                                           //??
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

            if(stklvl==0){
                return 1;
            }
            cpc=stack[stklvl-1];                        //??
            stklvl-=4;
            fail();
            fprintf(stderr,"--Fail-- cpc=%d stklvl=%d\n",cpc,stklvl);
        }
        else{
            if(cix>maxcix){
                maxcix = cix;
            }
            cix = stack[stklvl-3];                  //??
            cox = stack[stklvl-2];                  //??
        }
        return 0;
    }
}

int tncon(){

    skblank();
    tvscix=cix;
    int test=0;
    int i=0;
    while(inbuff[cix+i]<='9' && inbuff[cix+i]>='0'){
        i++;
        test=1;
    }
    if(test==0) {
    return 1; }

    fprintf(stderr,"TNCON - SETCODE cix=%d cox=%d i=%d\n",cix,cox,i);
    char token=0x0e;
    setcode(&token);
    int outbuffIndex=0;
    while(outbuffIndex<i){
        outbuff[cox+outbuffIndex]=inbuff[cix+outbuffIndex];
        outbuffIndex++;
    }
    cix=cix+i;
    cox=cox+outbuffIndex;
    return 0;
}

int tscon(){
    skblank();
    if(inbuff[cix]!='"')
        return 1;
    char token=0x0f;
    setcode(&token);
    tscox=cox;
    setcode(NULL);
    char ch;
    do{
        cix++;
        ch = inbuff[cix];
        fprintf(stderr,"TSCON - SETCODE \n");
        setcode(&ch);
    }while (!((ch=='\n')||(ch == '"')));
    outbuff[tscox]=cox-tscox;
    return 0;
}
int tvar(int tvtype){
    skblank();
    tvscix=cix;
    if(isalpha(inbuff[cix])) {
        srcont();                               //which table?
       if (svontc == 0 || (svontc == 1) && (inbuff[svontl] >= 0x30)) {  //not reserved word, or it is
           do                                                  //a non-reserved word whose prefix
               cix++;                                //is a reserved word..
           while (isalpha(inbuff[cix]) || isdigit(inbuff[cix]));
       }
      if (tvtype == 0x80 ) {
           if (inbuff[cix] == '$')
               cix++;                          //skip over $
           else
               return 1;
       }
       else if ( tvtype == 0x00 ) {
           if (inbuff[cix] == '(') {
               cix++;      //skip over (
               tvtype += 0x40;
       }
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
           addToTABLE(&VNTP_HEAD,&VNTP_TAIL);
           char tempVname[200];
           memcpy(tempVname,(inbuff+cix-1),cix);
           VNTP_TAIL->name=tempVname;
           addToTABLE(&STMTAB_HEAD,&STMTAB_TAIL);
           svvvte++;
           char* stmtabTemp= (char*)(calloc(8,1));
           STMTAB_TAIL->entry=stmtabTemp;

           if(tvtype==0x40)
               --tvscix;
           cix=tvscix;
           if (stenum>0x7f)
               return 1;
           fprintf(stderr,"TVAR- SETCODE \n");
           setcode(&stenum);
       }
    }
   else{
        return 1;                         //error
                                    //comment silinecek
    }



    /* return 1;*/
    return 0;
}

int tnvar(){
    return tvar(0x00);
}

int tsvar(){
    return tvar(0x80);
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
            if (stklvl == 4)       //??
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

