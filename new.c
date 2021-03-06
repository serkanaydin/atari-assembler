#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct label{
    char* name;
    short location;
};
struct table{
    char* name;
    int value;
};

struct label LABEL[120];
struct table OPNTAB[54];
short program[20000];
/*void initializeSntab(){
    sntab[0].name="rem";
    sntab[0].address=labelSearch("srem");
    sntab[1].name="data";
    sntab[1].address=labelSearch("sdata");
    sntab[2].name="input";
    sntab[2].address=labelSearch("sinput");
    sntab[3].name="color";
    sntab[3].address=labelSearch("scolor");
    sntab[4].name="list ";
    sntab[4].address=labelSearch("slist");
    sntab[5].name="enter";
    sntab[5].address=labelSearch("senter");
    sntab[6].name="let";
    sntab[6].address=labelSearch("slet");
    sntab[7].name="if";
    sntab[7].address=labelSearch("sif");
    sntab[8].name="for";
    sntab[8].address=labelSearch("sfor");
    sntab[9].name="next";
    sntab[9].address=labelSearch("snext");
    sntab[10].name="goto";
    sntab[10].address=labelSearch("sgoto");
    sntab[11].name="go to";
    sntab[11].address=labelSearch("sgoto");
    sntab[12].name="gosub";
    sntab[12].address=labelSearch("sgosub");
    sntab[13].name="trap";
    sntab[13].address=labelSearch("strap");
    //  sntab[14].name="bye";                                                            //DOESNT EXIST
    //  sntab[14].address=labelSearch("sbye");
    sntab[15].name="cont";
    sntab[15].address=labelSearch("scont");
    sntab[16].name="call";
    sntab[16].address=labelSearch("scall");
    sntab[17].name="close";
    sntab[17].address=labelSearch("sclose");
    sntab[18].name="clr";
    sntab[18].address=labelSearch("sclr");
    sntab[19].name="deg";
    sntab[19].address=labelSearch("sdeg");
    sntab[20].name="dim";
    sntab[20].address=labelSearch("sdim");
    sntab[21].name="end";
    sntab[21].address=labelSearch("send");
    sntab[22].name="new";
    sntab[22].address=labelSearch("snew");
    sntab[23].name="open";
    sntab[23].address=labelSearch("sopen");
    sntab[24].name="load";
    sntab[24].address=labelSearch("sload");
    sntab[25].name="save";
    sntab[25].address=labelSearch("ssave");
    sntab[26].name="status";
    sntab[26].address=labelSearch("sstatus");
    sntab[27].name="note";
    sntab[27].address=labelSearch("snote");
    sntab[28].name="point";
    sntab[28].address=labelSearch("spoint");
    sntab[29].name="xio";
    sntab[29].address=labelSearch("sxio");
    sntab[30].name="on";
    sntab[30].address=labelSearch("son");
    sntab[31].name="poke";
    sntab[31].address=labelSearch("spoke");
    sntab[32].name="print";
    sntab[32].address=labelSearch("sprint");
    sntab[33].name="rad";
    sntab[33].address=labelSearch("srad");
    sntab[34].name="read";
    sntab[34].address=labelSearch("sread");
    sntab[35].name="restore";
    sntab[35].address=labelSearch("srest");
    sntab[36].name="return";
    sntab[36].address=labelSearch("sret");
    sntab[37].name="run";
    sntab[37].address=labelSearch("srun");
    sntab[38].name="stop";
    sntab[38].address=labelSearch("sstop");
    sntab[39].name="pop";
    sntab[39].address=labelSearch("spop");
    sntab[40].name="?";
    sntab[40].address=labelSearch("sprint");
    sntab[41].name="get";
    sntab[41].address=labelSearch("sget");
    sntab[42].name="put";
    sntab[42].address=labelSearch("sput");
    sntab[43].name="graphics";
    sntab[43].address=labelSearch("sgr");
    sntab[44].name="plot";
    sntab[44].address=labelSearch("splot");
    sntab[45].name="position";
    sntab[45].address=labelSearch("spos");
    sntab[46].name="dos";
    sntab[46].address=labelSearch("sdos");
    sntab[47].name="drawto";
    sntab[47].address=labelSearch("sdrawto");                            //*SDRAWTO
    sntab[48].name="setcolor";
    sntab[48].address=labelSearch("ssetcolor");
    sntab[49].name="locate";
    sntab[49].address=labelSearch("slocate");                            //*slocate
    sntab[50].name="sound";
    sntab[50].address=labelSearch("ssound");
    sntab[51].name="lprint";
    sntab[51].address=labelSearch("slprint");
    sntab[52].name="csave";
    sntab[52].address=labelSearch("scsave");
    sntab[53].name="cload";
    sntab[53].address=labelSearch("scload");
    sntab[54].name="sound";
    sntab[54].address=labelSearch("ssound");
    //??? SILET

}*/

int opnTabSearch(char* str){
    int index=0;
    for(int i=0;i<53;i++){
        if(strcmp(OPNTAB[i].name,str)==0){
            return i;
        }
    }
    return -1;
}

int labelSearch(char* str){
    int index=0;
    for(int i=0;i<114;i++){
        if(strcmp(LABEL[i].name,str)==0){
            return i;}
    }
    return -1;
}

int main(void){
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



    for(int k=0;k<110;k++){
        printf("label %s, address:%d\n",LABEL[k].name,LABEL[k].location);
    }
    for(int k=0;k<54;k++){
        printf("operator %s, value:%x\n",OPNTAB[k].name,OPNTAB[k].value);
    }
    for(int k=0; k<20000;k++){
        printf("program %d value:%x\n",k,program[k]);
    }
    //initializeSntab();
}