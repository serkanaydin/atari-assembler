#ifndef ATARI_ASSEMBLER_DEFINITIONS_H
#define ATARI_ASSEMBLER_DEFINITIONS_H
struct label{
    char* name;
    short location;
};
struct table{
    char* name;
    int value;
};
struct table sntab[200];
struct label LABEL[120];
struct table OPNTAB[54];

short program[20000];

char inbuff[255], outbuff[255];
int cix, cox,binint=0;
int stenum;
int stmlbd;
int direct_statement;
int stack[200];
#endif //ATARI_ASSEMBLER_DEFINITIONS_H
