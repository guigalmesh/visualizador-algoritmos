#include "list.h"
#include "context.h"
#include "render.h"
#include <stdio.h>
#include <stdlib.h>

Node* retrieve_node(List* list, int index){
    if(index == 0)
        return list->head;
    Node* node = list->head;
    for(int i = 0; i < index; i++){
        node = node->prox;
    }
    return node;
}

void bubble_one_step(Node* node, Node* node_next){
    if(node->box->value > node_next->box->value){
        int temp = node->box->value;
        node->box->value = node_next->box->value;
        node_next->box->value = temp;

        float temp_y2;
        temp_y2 = node->box->y2;
        node->box->y2 = node_next->box->y2;
        node_next->box->y2 = temp_y2;
    }
}

void bubble_sort(ProgramContext* program){
    int list_size = program->number_list->list_size;
    Node *node, *node_next;
    for(int i = 0; i < list_size; i++){
        for(int j = 0; j < list_size - i - 1; j++){
            program_render(program);
            node = retrieve_node(program->number_list, j);
            node_next = retrieve_node(program->number_list, j + 1);
            bubble_one_step(node, node_next);
        }
    }
}
