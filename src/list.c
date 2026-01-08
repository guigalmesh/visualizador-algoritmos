#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List* lst_create(){
    return NULL;
}

List* lst_insert_end(List* list, int number){
    Node* new_node = (List*)malloc(sizeof(List));
    Node* p = list->head;
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = new_node;
    return list;
}

