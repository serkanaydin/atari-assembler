#include "definitions.h"
#include "table.h"

int labelSearch(char* str){
    int index=0;
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
        temp= getStr(stenum,VNTP_HEAD);
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
            case 1: if(*(lbuff + bufferIndex) == '.'){
                    situation=5;
                    break;
                }
            case 2:

                temp=getFromTable(table);
                size=strlen(temp);
                if(*(lbuff + bufferIndex) == temp[tableIndex]){
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
    for(int i=0;i<54;i++){
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



void initializeSntab(){
    sntab[0].name="rem";
    sntab[0].val.num=labelSearch("srem");
    sntab[1].name="data";
    sntab[1].val.num=labelSearch("sdata");
    sntab[2].name="input";
    sntab[2].val.num=labelSearch("sinput");
    sntab[3].name="color";
    sntab[3].val.num=labelSearch("scolor");
    sntab[4].name="list ";
    sntab[4].val.num=labelSearch("slist");
    sntab[5].name="enter";
    sntab[5].val.num=labelSearch("senter");
    sntab[6].name="let";
    sntab[6].val.num=labelSearch("slet");
    sntab[7].name="if";
    sntab[7].val.num=labelSearch("sif");
    sntab[8].name="for";
    sntab[8].val.num=labelSearch("sfor");
    sntab[9].name="next";
    sntab[9].val.num=labelSearch("snext");
    sntab[10].name="goto";
    sntab[10].val.num=labelSearch("sgoto");
    sntab[11].name="go to";
    sntab[11].val.num=labelSearch("sgoto");
    sntab[12].name="gosub";
    sntab[12].val.num=labelSearch("sgosub");
    sntab[13].name="trap";
    sntab[13].val.num=labelSearch("strap");
      sntab[14].name="bye";                                                            //DOESNT EXIST
      sntab[14].val.num=labelSearch("strap");      //hata verdiği için herhangi bir değer verdim
    sntab[15].name="cont";
    sntab[15].val.num=labelSearch("scont");
    sntab[16].name="com";
    sntab[16].val.num=labelSearch("scom");
    sntab[17].name="close";
    sntab[17].val.num=labelSearch("sclose");
    sntab[18].name="clr";
    sntab[18].val.num=labelSearch("sclr");
    sntab[19].name="deg";
    sntab[19].val.num=labelSearch("sdeg");
    sntab[20].name="dim";
    sntab[20].val.num=labelSearch("sdim");
    sntab[21].name="end";
    sntab[21].val.num=labelSearch("send");
    sntab[22].name="new";
    sntab[22].val.num=labelSearch("snew");
    sntab[23].name="open";
    sntab[23].val.num=labelSearch("sopen");
    sntab[24].name="load";
    sntab[24].val.num=labelSearch("sload");
    sntab[25].name="save";
    sntab[25].val.num=labelSearch("ssave");
    sntab[26].name="status";
    sntab[26].val.num=labelSearch("sstatus");
    sntab[27].name="note";
    sntab[27].val.num=labelSearch("snote");
    sntab[28].name="point";
    sntab[28].val.num=labelSearch("spoint");
    sntab[29].name="xio";
    sntab[29].val.num=labelSearch("sxio");
    sntab[30].name="on";
    sntab[30].val.num=labelSearch("son");
    sntab[31].name="poke";
    sntab[31].val.num=labelSearch("spoke");
    sntab[32].name="print";
    sntab[32].val.num=labelSearch("sprint");
    sntab[33].name="rad";
    sntab[33].val.num=labelSearch("srad");
    sntab[34].name="read";
    sntab[34].val.num=labelSearch("sread");
    sntab[35].name="restore";
    sntab[35].val.num=labelSearch("srest");
    sntab[36].name="return";
    sntab[36].val.num=labelSearch("sret");
    sntab[37].name="run";
    sntab[37].val.num=labelSearch("srun");
    sntab[38].name="stop";
    sntab[38].val.num=labelSearch("sstop");
    sntab[39].name="pop";
    sntab[39].val.num=labelSearch("spop");
    sntab[40].name="?";
    sntab[40].val.num=labelSearch("sprint");
    sntab[41].name="get";
    sntab[41].val.num=labelSearch("sget");
    sntab[42].name="put";
    sntab[42].val.num=labelSearch("sput");
    sntab[43].name="graphics";
    sntab[43].val.num=labelSearch("sgr");
    sntab[44].name="plot";
    sntab[44].val.num=labelSearch("splot");
    sntab[45].name="position";
    sntab[45].val.num=labelSearch("spos");
    sntab[46].name="dos";
    sntab[46].val.num=labelSearch("sdos");
    sntab[47].name="drawto";
    sntab[47].val.num=labelSearch("sdrawto");                            //*SDRAWTO
    sntab[48].name="setcolor";
    sntab[48].val.num=labelSearch("ssetcolor");
    sntab[49].name="locate";
    sntab[49].val.num=labelSearch("slocate");                            //*slocate
    sntab[50].name="sound";
    sntab[50].val.num=labelSearch("ssound");
    sntab[51].name="lprint";
    sntab[51].val.num=labelSearch("slprint");
    sntab[52].name="csave";
    sntab[52].val.num=labelSearch("scsave");
    sntab[53].name="cload";
    sntab[53].val.num=labelSearch("scload");
    sntab[54].name="sound";                                                 //???
    sntab[54].val.num=labelSearch("ssound");
    //??? SILET
}

void initializeTables(){
    FILE *fp;
    char line[100];
    char *token = NULL;
    fp = fopen("input3.txt","r");
    int i=0;
    int PC=0;
    FILE *fp2 ;


    fp2=fopen("opntab.txt","r");
    if(fp2!=NULL) {
        while (fgets(line, sizeof line, fp2) != NULL) {
            token = strtok(line, "\n\t\r ");
            while (token) {
                char *temp = (char*)(malloc(sizeof(token)));
                strcpy(temp,token); // temp = CDQ
                OPNTAB[i].name=temp;
                token = strtok(NULL, "\n\t\r ");
                OPNTAB[i].val.num=strtol(token, NULL, 16);

                token = strtok(NULL, "\n\t\r ");
                i++;
            }
        }
    }
    fclose(fp2);

    fp2=fopen("opntab2.txt","r");
    i=0;
    if(fp2!=NULL) {
        while (fgets(line, sizeof line, fp2) != NULL) {
            token = strtok(line, "\n\t\r ");
            while (token) {
                char *temp = (char*)(malloc(sizeof(token)));
                strcpy(temp,token);
                OPNTAB_STRING[i].name=temp;
                token = strtok(NULL, "\n\t\r ");
                temp =(char*)(malloc(8));
                strcpy(temp,token);
                OPNTAB_STRING[i].val.str=temp;
                token = strtok(NULL, "\n\t\r ");
                i++;
            }
        }
    }
    fclose(fp2);

    i=0;
    int k=0;
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
                LABEL[i].location=PC-1; // location = labels location
                i++; // label doesn't increment PC
            }
            token = strtok(NULL, ",\n\t\r ");
        }
        rewind(fp);
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
        printf("label %s, value:%d\n",LABEL[k].name,LABEL[k].location);
    }
    for(int k=0;k<54;k++){
        printf("operator %s, value:%x\n",OPNTAB[k].name,OPNTAB[k].value);
    }*/
    /*for(int k=0; k<1000;k++){
        printf("program %d value:%x\n",k,program[k]);
    }*/
    initializeSntab();
}

char getll() {
    return (*(stmcur+2));
}
