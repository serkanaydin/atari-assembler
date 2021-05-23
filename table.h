#include "definitions.h"
void initializeTABLE(LinkedTable_PTR head,LinkedTable_PTR tail){
    head = (LinkedTable_PTR)(malloc(sizeof (LinkedTAB)));
    head->name=NULL;
    head->entry=NULL;
    tail=head;
    tail->next=NULL;
}
void addToTABLE(LinkedTable_PTR head,LinkedTable_PTR tail){
    if(head==NULL)
        initializeTABLE(head,tail);
    else {
        LinkedTable_PTR temp = (LinkedTable_PTR) (malloc(sizeof(LinkedTAB)));
        temp->name = NULL;
        temp->entry = NULL;
        tail->next = temp;
        tail = temp;
        tail->next = NULL;
    }
}
char* getStr(int index,LinkedTable_PTR head){
    LinkedTable_PTR current=head;
    for(int i=0;i<index;i++){
        current=current->next;
        if(current==NULL)
            return NULL;
    }
    return current->name;

}