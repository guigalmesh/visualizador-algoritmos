#ifndef ALGOS_H
#define ALGOS_H
#include "list.h"

Node* retrieve_node(List* list, int index);
void bubble_one_step(List* list);
void bubble_sort(ProgramContext* program);

#endif