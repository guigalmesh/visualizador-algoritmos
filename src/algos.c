#include "list.h"
#include "context.h"
#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

void bubble_sort_step(ProgramContext* program){
    DynamicArr* arr = program->arr;

    if(program->iterator_i >= arr->size - 1){
        program->sort_state = SORTSTATE_IDLE;
        return;
    }

    int j = program->iterator_j;

    if(arr->item_arr[j].value > arr->item_arr[j+ 1].value){
        int temp = arr->item_arr[j].value;
        arr->item_arr[j].value = arr->item_arr[j + 1].value;
        arr->item_arr[j + 1].value = temp;

        ALLEGRO_COLOR temp_color = arr->item_arr[j].color;
        arr->item_arr[j].color = arr->item_arr[j + 1].color;
        arr->item_arr[j + 1].color = temp_color;
    }

    program->iterator_j++;

    if(program->iterator_j >= arr->size - 1 - program->iterator_i){
        program->iterator_j = 0;
        program->iterator_i++;
    }
}

void insertion_sort_step(ProgramContext* program){
    DynamicArr* arr = program->arr;

    if(program->iterator_i >= arr->size){
        program->sort_state = SORTSTATE_IDLE;
        return;
    }

    if(!program->is_holding_key){
        program->key_value = arr->item_arr[program->iterator_i].value;
        program->key_color = arr->item_arr[program->iterator_i].color;

        program->iterator_j = program->iterator_i - 1;
        program->is_holding_key = true;
        return;
    }

    if(program->iterator_j >= 0 && arr->item_arr[program->iterator_j].value > program->key_value){
        arr->item_arr[program->iterator_j + 1] = arr->item_arr[program->iterator_j];

        program->iterator_j--;
        return;
    }

    arr->item_arr[program->iterator_j + 1].value = program->key_value;
    arr->item_arr[program->iterator_j + 1].color = program->key_color;

    program->iterator_i++;
    program->is_holding_key = false;
}