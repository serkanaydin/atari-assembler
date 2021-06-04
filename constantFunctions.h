int srcont(){
    skblank();
    char temp=cix;
    if(temp != svontx){
        svontx= temp;
        if(search(OPNTAB_STRING,0)){
            svontc ='\0';
            return 1;
        }
        svontl = bufferIndex;
        temp = OPNTAB[stenum].val.str;
        svontc = temp;
    }
    temp = program[cpc];
    printf("--SRCONT-- cix=%d temp=%d svontc=%d\n",cix,temp,svontc);
    if(svontc == temp){
        printf("SRCONT - SETCODE-- cix=%d SVONTC=%d temp=%d\n",cix,svontc,temp);
        setcode(&temp);
        cix = svontl;
        return 0;
    }
    else if((temp == 0x44)&&( 0x44 <= svontc)) {
        setcode(&svontc);
        cix = svontl;
        return 0; }
    else{
        return 1;
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

    printf(stderr,"TNCON - SETCODE cix=%d cox=%d i=%d\n",cix,cox,i);
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
        printf("TSCON - SETCODE \n");
        setcode(&ch);
    }while (!((ch=='\n')||(ch == '"')));
    if (ch == '"')
        cix++;  //increment over double quote,
    outbuff[tscox]=cox-tscox;
    return 0;
}