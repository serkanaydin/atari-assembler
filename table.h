#include "definitions.h"
void initializeVTABLE(char* name,char entry[]){
    head = (VTABLE_PTR)(malloc(sizeof (VTABLE)));
    char* nameTmp=(char*)(malloc(strlen(name)));
    strcpy(nameTmp,name);
    head->name=nameTmp;
    char* entryTmp = (char*)(malloc(8));
    strcpy(entryTmp,entry);
    head->entry=entryTmp;
    tail=head;
    tail->next=NULL;
}
void addToVTABLE(char* name,char entry[]){
    VTABLE_PTR temp = (VTABLE_PTR)(malloc(sizeof (VTABLE)));
    char* nameTmp=(char*)(malloc(strlen(name)));
    strcpy(nameTmp,name);
    temp->name=nameTmp;
    char* entryTmp = (char*)(malloc(8));
    strcpy(entryTmp,entry);
    temp->entry=nameTmp;
    tail->next=temp;
    tail=temp;
    tail->next=NULL;
}
char* getStr(int index){
    VTABLE_PTR current=head;
    for(int i=0;i<index;i++){
        current=current->next;
        if(current==NULL)
            return NULL;
    }
    return current->name;

}