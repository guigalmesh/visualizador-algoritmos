#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "context.h"
#include "list.h"

Node* create_node(int value, List* list){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->box = (Box*)malloc(sizeof(Box));
    new_node->box->value = value;
    new_node->prox = NULL;

    // protótipo das propriedades de box

    float height = ((float)value / list->max_number) * 300;
    float width = 900.0 / list->list_size;
    float x1 = (LOGICAL_WIDTH * 0.15f) + (width * list->list_size_counter);
    float y1 = LOGICAL_HEIGHT * 0.70f;
    float x2 = x1 + width;
    float y2 = y1 - height;

    new_node->box->height = height;
    new_node->box->width = width;

    new_node->box->x1 = x1;
    new_node->box->y1 = y1;

    new_node->box->x2 = x2;
    new_node->box->y2 = y2;

    return new_node;
}

List* lst_create(){
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->list_size = 0;
    list->list_size_counter = 0;
    return list;
}

List* lst_append(List* list, int value){
    Node* new_node = create_node(value, list);
    list->list_size_counter++;
    if(list->head == NULL){
        list->head = new_node;
        return list;
    }
    Node* p = list->head;
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = new_node;
    return list;
}

List* lst_generate(int list_size, int min, int max){
    srand(time(NULL));
    List* list = lst_create();
    list->list_size = list_size;
    list->max_number = max;
    for(int i = 0; i < list_size; i++){
        int value = (rand() % max) + min;
        list = lst_append(list, value);
    }
    return list;
}

void lst_print(List* list){
    Node* node = list->head;
    for(int i = 0; i < list->list_size; i++){
        printf("%d ", node->box->value);
        node = node->prox;
    }
    printf("\n");
}