#include "definitions.h"

int nxsc() {
    return program[cpc++];    //cpc points to the syntax_table[]
}

int labelSearch(char* str){
    int index=0;
    for(int i=0;i<114;i++){
        if(strcmp(LABEL[i].name,str)==0){
            return i;}
    }
    return -1;
}




void getToken(){
    int i=cix;
    for(;i<200;i++){
        if(inbuff[i]==' ' || inbuff[i]=='\0')
            break;
    }
    memcpy(subStr,(inbuff+cix),i-cix);
    cix=i;
}

int search(struct table table[]) {  //srcadr is the address of the table, srcskip is the skip factor..
    int i=cix;
    for(;i<200;i++){
        if(lbuff[i]==' ' || lbuff[i]=='\0')
            break;
    }
    int size =i-cix;
    int error;
    int situation=0;
    stenum=-1;
    while(1){
        switch (situation) {
            case 0: stenum++;
                bufferIndex=cix;
                tableIndex=0;
                if(table[stenum].string == NULL)
                    return 1;
                error =0;
            case 1: if(*(lbuff + bufferIndex) == '.'){
                    situation=5;
                    break;
                }
            case 2: if(*(lbuff + bufferIndex) == (table[stenum].string)[tableIndex]){
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
                if(error==0)
                    return 0;
                situation=0;
        }
    }
}

int sntabSearch(){
    getToken();
    for(int i=0;i<114;i++){
        if(strcmp(sntab[i].string, subStr) == 0){
            return i;}
    }
    return -1;
}

int opnTabSearch(char* str){
    for(int i=0;i<54;i++){
        if(strcmp(OPNTAB[i].string, str) == 0){
            return i;
        }
    }
    return -1;
}

void setcode(char *a) {
    if(a==NULL)
        outbuff[cox++]= '\0';
    else
    outbuff[cox++]=*a;
    if (cox==0)
        printf("line is too long");
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
    int i;

    while (inbuff[cix]==' ')
        cix++;
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
    skblank();
    tvscix=cix;
    return 0;
}

int tscon(){
    skblank;
    if (inbuff[cix] != '"') //is the character read a double quote
        return(1); //fail, carry=1

    char ch0 =0x0f;
    setcode(&ch0);  //set sconcode
    tscox=cox;
    setcode(NULL); //open a space in outbuff for string length..
    char ch;
    do {
        cix++;
        ch = inbuff[cix];
        setcode(&ch);
    }while (!((ch=='\n')||(ch == '"')));
        if (ch == '"')
            cix++;  //increment over double quote,
    outbuff[tscox]=cox-tscox; //set string length
    return(0); //success, carry=0
}

int tnvar(){
    return 0;
}

int tsvar(){
    return 0;
}

void initializeSntab(){
    sntab[0].string="rem";
    sntab[0].val.num=labelSearch("srem");
    sntab[1].string="data";
    sntab[1].val.num=labelSearch("sdata");
    sntab[2].string="input";
    sntab[2].val.num=labelSearch("sinput");
    sntab[3].string="color";
    sntab[3].val.num=labelSearch("scolor");
    sntab[4].string="list ";
    sntab[4].val.num=labelSearch("slist");
    sntab[5].string="enter";
    sntab[5].val.num=labelSearch("senter");
    sntab[6].string="let";
    sntab[6].val.num=labelSearch("slet");
    sntab[7].string="if";
    sntab[7].val.num=labelSearch("sif");
    sntab[8].string="for";
    sntab[8].val.num=labelSearch("sfor");
    sntab[9].string="next";
    sntab[9].val.num=labelSearch("snext");
    sntab[10].string="goto";
    sntab[10].val.num=labelSearch("sgoto");
    sntab[11].string="go to";
    sntab[11].val.num=labelSearch("sgoto");
    sntab[12].string="gosub";
    sntab[12].val.num=labelSearch("sgosub");
    sntab[13].string="trap";
    sntab[13].val.num=labelSearch("strap");
      sntab[14].string="bye";                                                            //DOESNT EXIST
      sntab[14].val.num=labelSearch("strap");      //hata verdiği için herhangi bir değer verdim
    sntab[15].string="cont";
    sntab[15].val.num=labelSearch("scont");
    sntab[16].string="com";
    sntab[16].val.num=labelSearch("scom");
    sntab[17].string="close";
    sntab[17].val.num=labelSearch("sclose");
    sntab[18].string="clr";
    sntab[18].val.num=labelSearch("sclr");
    sntab[19].string="deg";
    sntab[19].val.num=labelSearch("sdeg");
    sntab[20].string="dim";
    sntab[20].val.num=labelSearch("sdim");
    sntab[21].string="end";
    sntab[21].val.num=labelSearch("send");
    sntab[22].string="new";
    sntab[22].val.num=labelSearch("snew");
    sntab[23].string="open";
    sntab[23].val.num=labelSearch("sopen");
    sntab[24].string="load";
    sntab[24].val.num=labelSearch("sload");
    sntab[25].string="save";
    sntab[25].val.num=labelSearch("ssave");
    sntab[26].string="status";
    sntab[26].val.num=labelSearch("sstatus");
    sntab[27].string="note";
    sntab[27].val.num=labelSearch("snote");
    sntab[28].string="point";
    sntab[28].val.num=labelSearch("spoint");
    sntab[29].string="xio";
    sntab[29].val.num=labelSearch("sxio");
    sntab[30].string="on";
    sntab[30].val.num=labelSearch("son");
    sntab[31].string="poke";
    sntab[31].val.num=labelSearch("spoke");
    sntab[32].string="print";
    sntab[32].val.num=labelSearch("sprint");
    sntab[33].string="rad";
    sntab[33].val.num=labelSearch("srad");
    sntab[34].string="read";
    sntab[34].val.num=labelSearch("sread");
    sntab[35].string="restore";
    sntab[35].val.num=labelSearch("srest");
    sntab[36].string="return";
    sntab[36].val.num=labelSearch("sret");
    sntab[37].string="run";
    sntab[37].val.num=labelSearch("srun");
    sntab[38].string="stop";
    sntab[38].val.num=labelSearch("sstop");
    sntab[39].string="pop";
    sntab[39].val.num=labelSearch("spop");
    sntab[40].string="?";
    sntab[40].val.num=labelSearch("sprint");
    sntab[41].string="get";
    sntab[41].val.num=labelSearch("sget");
    sntab[42].string="put";
    sntab[42].val.num=labelSearch("sput");
    sntab[43].string="graphics";
    sntab[43].val.num=labelSearch("sgr");
    sntab[44].string="plot";
    sntab[44].val.num=labelSearch("splot");
    sntab[45].string="position";
    sntab[45].val.num=labelSearch("spos");
    sntab[46].string="dos";
    sntab[46].val.num=labelSearch("sdos");
    sntab[47].string="drawto";
    sntab[47].val.num=labelSearch("sdrawto");                            //*SDRAWTO
    sntab[48].string="setcolor";
    sntab[48].val.num=labelSearch("ssetcolor");
    sntab[49].string="locate";
    sntab[49].val.num=labelSearch("slocate");                            //*slocate
    sntab[50].string="sound";
    sntab[50].val.num=labelSearch("ssound");
    sntab[51].string="lprint";
    sntab[51].val.num=labelSearch("slprint");
    sntab[52].string="csave";
    sntab[52].val.num=labelSearch("scsave");
    sntab[53].string="cload";
    sntab[53].val.num=labelSearch("scload");
    sntab[54].string="sound";                                                 //???
    sntab[54].val.num=labelSearch("ssound");
    //??? SILET
}

void initializeTables(){
    FILE *fp;
    char line[100];
    char *token = NULL;
    fp = fopen("input3.txt","r");
    short lNum=0;
    int i=0;
    int labelCatch=0;
    int PC=0;

    FILE *fp2 ;
    fp2=fopen("opntab.txt","r");
    i=0;
    if(fp2!=NULL) {
        while (fgets(line, sizeof line, fp2) != NULL) {

            /*  CDQ   0x10
                CSOE   0x11 */

            token = strtok(line, "\n\t\r "); // token = CDQ
            while (token) {
                char *temp = (char*)(malloc(sizeof(token)));
                strcpy(temp,token); // temp = CDQ
                OPNTAB[i].string=temp;
                token = strtok(NULL, "\n\t\r "); // token = 0x10
                if(strlen(token)==1)
                    OPNTAB[i].val.num=(long)strtol(token, NULL, 16); // value = 0x10 return 16

                token = strtok(NULL, "\n\t\r "); // token = CSOE
                i++;
            }
        }
    }
    fclose(fp2);

    fp2=fopen("opntab2.txt","r");
    i=0;
    if(fp2!=NULL) {
        while (fgets(line, sizeof line, fp2) != NULL) {

            /*  CDQ   0x10
                CSOE   0x11 */

            token = strtok(line, "\n\t\r "); // token = CDQ
            while (token) {
                char *temp = (char*)(malloc(sizeof(token)));
                strcpy(temp,token); // temp = CDQ
                OPNTAB_STRING[i].string=temp;
                token = strtok(NULL, "\n\t\r "); // token = 0x10
                temp =(char*)(malloc(8));
                strcpy(temp,token);
                OPNTAB_STRING[i].val.str=temp; // value = 0x10 return 16
                printf("%s\t%d\n",temp,i);
                token = strtok(NULL, "\n\t\r "); // token = CSOE
                i++;
            }
        }
    }
    fclose(fp2);

    i=0;
    int k=0;
    /* 
    exp 
        CLPRN
        call exp
        CRPRN
        call nop 
    */
    if (fp != NULL){
        while(fgets(line,sizeof line,fp)!= NULL) {
            if(line[0]=='\t'){      // (exp) label so do nothing
                token = strtok(line, "\n\r\t ");
                if(strcmp(token,"call")==0) {
                    PC += 2; }
                else{
                    PC+=1;
                }
            }
            else{           // only takes labels
                token = strtok(line, "\n\r\t "); // token = label
                char* temp = (char *)(malloc(sizeof(token)));
                strcpy(temp,token);
                LABEL[i].name=temp; // label i = temp
                LABEL[i].location=PC; // location = labels location
                i++; // label doesn't increment PC
            }
            token = strtok(NULL, ",\n\t\r ");
        }

        rewind(fp); // put fp to the start of file

        /* 
        exp 
            CLPRN
            call exp
            CRPRN
            call nop 
        */

        while(fgets(line,sizeof line,fp)!= NULL) {
            if(line[0]=='\t'){ // if label, skip line
                token = strtok(line, "\n\r\t "); // token = CLRPN
                if(strcmp(token,"call")==0) {
                    token = strtok(NULL, "\n\r\t ");
                    int index= labelSearch(token);
                    program[k]=0;
                    program[k+1]=LABEL[index].location;
                    k+=2;
                }
                else if(strcmp(token,"ret")==0) {
                    program[k]=0x0003;
                    k++;
                }
                else if(strcmp(token,"or")==0) {
                    program[k]=0x0002;
                    k++;
                }
                else  if(token[0]=='C') { // if token starts with C
                    int index =opnTabSearch(token);
                    program[k]=OPNTAB[index].val.num;
                    k++;
                }
                else if(strcmp(token,"chng")==0){
                    program[k]=0x0001;
                    k++;
                }
                else if(strcmp(token,"tncon")==0){
                    program[k]=0x0004;
                    k++;
                }
                else if(strcmp(token,"tnvar")==0){
                    program[k]=0x0005;
                    k++;
                }
                else if(strcmp(token,"tscon")==0){
                    program[k]=0x0006;
                    k++;
                }
                else if(strcmp(token,"tsvar")==0){
                    program[k]=0x0007;
                    k++;
                }
                else if(strcmp(token,"edata")==0){
                    program[k]=0x0008;
                    k++;
                }
                else if(strcmp(token,"erem")==0){
                    program[k]=0x0009;
                    k++;
                }
                else if(strcmp(token,"eif")==0){
                    program[k]=0x000a;
                    k++;
                }
            }
        }
    }
    /*for(int k=0;k<110;k++){
        printf("label %s, value:%d\n",LABEL[k].string,LABEL[k].location);
    }
    for(int k=0;k<54;k++){
        printf("operator %s, value:%x\n",OPNTAB[k].string,OPNTAB[k].value);
    }
    for(int k=0; k<1000;k++){
        printf("program %d value:%x\n",k,program[k]);
    }*/
    initializeSntab();
}

int srcont(){
    skblank();
    char temp=cix;
    if(temp != svontx){
        svontx= temp;
        if(search(OPNTAB)){                     //STENUMU AYARLIYOR
            svontc =0;
            return 1;
        }
        svontl = bufferIndex;
        temp = stenum + 0x10;                   //
        svontc = temp;
    }
    if(svontc == temp){
        setcode(temp);
        cix = svontl;
        return 0;
    }
    else if(temp != 0x44)
        return 1;
    else{
        temp = svontc;
        setcode(temp);
        cix = svontl;
        return 0;
    }
}