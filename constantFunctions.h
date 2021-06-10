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
    printf(ANSI_COLOR_GRAY"--SRCONT-- cix=%d temp=%d svontc=%d\n"ANSI_COLOR_RESET, cix, temp, svontc);
    if(svontc == temp){
        printf(ANSI_COLOR_BRIGHT_GREEN"SRCONT - SETCODE-- cix=%d SVONTC=%d temp=%d\n"ANSI_COLOR_RESET, cix, svontc, temp);
        setcode(&temp);
        cix = svontl;
        printINBUFF("SRCONT : ");
        return 0;
    }
    else if((temp == 0x44)&&( 0x44 <= svontc)) {
        printf("SRCONT - SETCODE- CNFNP- cix=%d SVONTC=%d temp=%d\n",cix,svontc,temp);
        setcode(&svontc);
        cix = svontl;
        printINBUFF("SRCONT - CNFNP : ");
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

    printf(stderr,ANSI_COLOR_CYAN"TNCON - SETCODE cix=%d cox=%d i=%d\n"ANSI_COLOR_RESET,cix,cox,i);
    char token=0x0e;
    setcode(&token);
    int outbuffIndex=0;
    int inbuffIndex=0;
    while(outbuffIndex<6){
	if(outbuffIndex <6-i)
	outbuff[cox+outbuffIndex++]='\0';
	else
        outbuff[cox+outbuffIndex++]=inbuff[cix+inbuffIndex++];

    }
    cix=cix+i;
    printINBUFF("TNCON: ");
    cox=cox+6;
    printOUTBUFF("TNCON: ");
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
    printOUTBUFF("2 SETCODES UPPER -> SCON TOKEN & TOKEN SIZE");
    char ch;
	cix++;
    while (!(((ch=inbuff[cix])=='\n')||((ch=inbuff[cix])== '"'))){
        printf(ANSI_COLOR_MAGENTA"TSCON - SETCODE \n"ANSI_COLOR_RESET);
        setcode(&ch);
	cix++;
    }
    if (ch == '"') {
        cix++;
        printINBUFF("TSCON: ");}
    outbuff[tscox]=cox-tscox-1;                       //??
    printINBUFF("TSCON: ");
    return 0;
}
