#ifndef ATARI_ASSEMBLER_DEFINITIONS_H
#define ATARI_ASSEMBLER_DEFINITIONS_H
struct label{
    char* name;
    short location;
};
union value{
    long num;
    char* str;
};
struct table{
    char* name;
    union value val;
};
struct linkedTable{
    char* name;
    char* entry;
    struct linkedTable* next;
};
typedef struct linkedTable* LinkedTable_PTR;
typedef struct linkedTable LinkedTAB;

LinkedTable_PTR  VNTP_HEAD=NULL;
LinkedTable_PTR VNTP_TAIL=NULL;
LinkedTable_PTR  STMTAB_HEAD=NULL;
LinkedTable_PTR STMTAB_TAIL=NULL;

struct table OPNTAB_STRING[71];
struct table sntab[200];
struct label LABEL[120];
struct table OPNTAB[55];
char STATEMENT_TABLE[1000];

short program[20000];
char* lbuff;
char inbuff[255], outbuff[255];
int cix, cox,binint=0;
int stenum;
int stmlbd;
int direct_statement;
int stack[200];
int cpc, spc, six, sox, stklvl;
int tvscix,tscox;

char svontx,svontc,svvte,svontl,svvvte=0;

char stmstart;

short linelength;
char* stmcur;

char subStr[255];
int bufferIndex;
int tableIndex;
#endif //ATARI_ASSEMBLER_DEFINITIONS_H
