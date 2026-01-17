#ifndef LOGIC_H
#define LOGIC_H

#include "context.h"

void button_bubble_sort(StateContext* state, UIContext* ui, SortContext* sort);
void button_back_to_menu(StateContext* state, UIContext* ui, SortContext* sort);
void button_insertion_sort(StateContext* state, UIContext* ui, SortContext* sort);
void button_close_program(StateContext* state, UIContext* ui, SortContext* sort);
void button_start_insertion(StateContext* state, UIContext* ui, SortContext* sort);
void button_start_bubble(StateContext* state, UIContext* ui, SortContext* sort);
void program_loop(ProgramContext* program);

#endif