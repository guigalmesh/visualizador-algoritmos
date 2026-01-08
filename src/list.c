#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

List* lst_create(){
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
}

List* lst_append(List* list, int value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->box = (Box*)malloc(sizeof(Box));
    new_node->box->value = value;
    new_node->prox = NULL;

    if(list->head == NULL){
        list->head = new_node;
        return list;
    }
    Node* p = list->head;
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = new_node;
    list->size++;
    return list;
}

List* lst_generate(int size, int min, int max){
    srand(time(NULL));
    List* list = lst_create();
    for(int i = 0; i < size; i++){
        int value = (rand() % max) + min;
        list = lst_append(list, value);
    }
    return list;
}

void lst_print(List* list){
    Node* node = list->head;
    for(int i = 0; i < list->size; i++){
        printf("%d ", node->box->value);
        node = node->prox;
    }
    printf("\n");
}