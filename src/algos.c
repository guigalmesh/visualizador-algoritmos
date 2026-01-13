#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void bubble_one_step(List* list){
    Node* node = list->head;
    Node* node_next = node->prox;
    if(node->box->value > node_next->box->value){
        int temp = node->box->value;
        node->box->value = node_next->box->value;
        node_next->box->value = temp;

        float temp_y2;
        temp_y2 = node->box->y2;
        node->box->y2 = node_next->box->y2;
        node_next->box->y2 = temp_y2;
    }
    lst_print(list);
}