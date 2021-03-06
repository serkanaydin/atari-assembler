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
        fflush(fp);
    }
    fclose(fp);
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
    for(int k=0;k<110;k++){
        printf("label %s, address:%d\n",LABEL[k].name,LABEL[k].location);
    }
    for(int k=0;k<54;k++){
        printf("operator %s, value:%x\n",OPNTAB[k].name,OPNTAB[k].value);
    }
}