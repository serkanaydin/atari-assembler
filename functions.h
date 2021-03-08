#include "definitions.h"

#ifndef ATARI_ASSEMBLER_FUNCTIONS_H
#define ATARI_ASSEMBLER_FUNCTIONS_H

int labelSearch(char* str){
    int index=0;
    for(int i=0;i<114;i++){
        if(strcmp(LABEL[i].name,str)==0){
            return i;}
    }
    return -1;
}


int sntabSearch(){
    int i=cix;
    for(;i<200;i++){
        if(inbuff[i]==' ' || inbuff[i]=='\0')
            break;
    }
    char subStr[i-cix];
    memcpy(subStr,(inbuff+cix),i-cix);
    for(int i=0;i<114;i++){
        if(strcmp(sntab[i].name,subStr)==0){
            return i;}
    }
    return -1;
}

int opnTabSearch(char* str){
    for(int i=0;i<53;i++){
        if(strcmp(OPNTAB[i].name,str)==0){
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

void initializeSntab(){
    sntab[0].name="rem";
    sntab[0].value=labelSearch("srem");
    sntab[1].name="data";
    sntab[1].value=labelSearch("sdata");
    sntab[2].name="input";
    sntab[2].value=labelSearch("sinput");
    sntab[3].name="color";
    sntab[3].value=labelSearch("scolor");
    sntab[4].name="list ";
    sntab[4].value=labelSearch("slist");
    sntab[5].name="enter";
    sntab[5].value=labelSearch("senter");
    sntab[6].name="let";
    sntab[6].value=labelSearch("slet");
    sntab[7].name="if";
    sntab[7].value=labelSearch("sif");
    sntab[8].name="for";
    sntab[8].value=labelSearch("sfor");
    sntab[9].name="next";
    sntab[9].value=labelSearch("snext");
    sntab[10].name="goto";
    sntab[10].value=labelSearch("sgoto");
    sntab[11].name="go to";
    sntab[11].value=labelSearch("sgoto");
    sntab[12].name="gosub";
    sntab[12].value=labelSearch("sgosub");
    sntab[13].name="trap";
    sntab[13].value=labelSearch("strap");
      sntab[14].name="bye";                                                            //DOESNT EXIST
      sntab[14].value=labelSearch("strap");      //hata verdiği için herhangi bir değer verdim
    sntab[15].name="cont";
    sntab[15].value=labelSearch("scont");
    sntab[16].name="com";
    sntab[16].value=labelSearch("scom");
    sntab[17].name="close";
    sntab[17].value=labelSearch("sclose");
    sntab[18].name="clr";
    sntab[18].value=labelSearch("sclr");
    sntab[19].name="deg";
    sntab[19].value=labelSearch("sdeg");
    sntab[20].name="dim";
    sntab[20].value=labelSearch("sdim");
    sntab[21].name="end";
    sntab[21].value=labelSearch("send");
    sntab[22].name="new";
    sntab[22].value=labelSearch("snew");
    sntab[23].name="open";
    sntab[23].value=labelSearch("sopen");
    sntab[24].name="load";
    sntab[24].value=labelSearch("sload");
    sntab[25].name="save";
    sntab[25].value=labelSearch("ssave");
    sntab[26].name="status";
    sntab[26].value=labelSearch("sstatus");
    sntab[27].name="note";
    sntab[27].value=labelSearch("snote");
    sntab[28].name="point";
    sntab[28].value=labelSearch("spoint");
    sntab[29].name="xio";
    sntab[29].value=labelSearch("sxio");
    sntab[30].name="on";
    sntab[30].value=labelSearch("son");
    sntab[31].name="poke";
    sntab[31].value=labelSearch("spoke");
    sntab[32].name="print";
    sntab[32].value=labelSearch("sprint");
    sntab[33].name="rad";
    sntab[33].value=labelSearch("srad");
    sntab[34].name="read";
    sntab[34].value=labelSearch("sread");
    sntab[35].name="restore";
    sntab[35].value=labelSearch("srest");
    sntab[36].name="return";
    sntab[36].value=labelSearch("sret");
    sntab[37].name="run";
    sntab[37].value=labelSearch("srun");
    sntab[38].name="stop";
    sntab[38].value=labelSearch("sstop");
    sntab[39].name="pop";
    sntab[39].value=labelSearch("spop");
    sntab[40].name="?";
    sntab[40].value=labelSearch("sprint");
    sntab[41].name="get";
    sntab[41].value=labelSearch("sget");
    sntab[42].name="put";
    sntab[42].value=labelSearch("sput");
    sntab[43].name="graphics";
    sntab[43].value=labelSearch("sgr");
    sntab[44].name="plot";
    sntab[44].value=labelSearch("splot");
    sntab[45].name="position";
    sntab[45].value=labelSearch("spos");
    sntab[46].name="dos";
    sntab[46].value=labelSearch("sdos");
    sntab[47].name="drawto";
    sntab[47].value=labelSearch("sdrawto");                            //*SDRAWTO
    sntab[48].name="setcolor";
    sntab[48].value=labelSearch("ssetcolor");
    sntab[49].name="locate";
    sntab[49].value=labelSearch("slocate");                            //*slocate
    sntab[50].name="sound";
    sntab[50].value=labelSearch("ssound");
    sntab[51].name="lprint";
    sntab[51].value=labelSearch("slprint");
    sntab[52].name="csave";
    sntab[52].value=labelSearch("scsave");
    sntab[53].name="cload";
    sntab[53].value=labelSearch("scload");
    sntab[54].name="sound";
    sntab[54].value=labelSearch("ssound");
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
            token = strtok(line, "\n\t\r ");
            while (token) {
                char* temp = (char*)(malloc(sizeof(token)));
                strcpy(temp,token);
                OPNTAB[i].name=temp;
                token = strtok(NULL, "\n\t\r ");
                OPNTAB[i].value=(int)strtol(token, NULL, 16);
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
            if(line[0]=='\t'){
                token = strtok(line, "\n\r\t ");
                if(strcmp(token,"call")==0) {
                    PC += 2; }
                else{
                    PC+=1;
                }
            }
            else{           //LABEL
                token = strtok(line, "\n\r\t ");
                char* temp = (char *)(malloc(sizeof(token)));
                strcpy(temp,token);
                LABEL[i].name=temp;
                LABEL[i].location=PC;
                i++;
            }
            token = strtok(NULL, ",\n\t\r ");
        }
        rewind(fp);
        while(fgets(line,sizeof line,fp)!= NULL) {
            if(line[0]=='\t'){
                token = strtok(line, "\n\r\t ");
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
                else  if(token[0]=='C') {
                    int index =opnTabSearch(token);
                    program[k]=OPNTAB[index].value;
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
    }
    for(int k=0; k<1000;k++){
        printf("program %d value:%x\n",k,program[k]);
    }*/
    initializeSntab();
}
#endif //ATARI_ASSEMBLER_FUNCTIONS_H
