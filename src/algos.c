#include "list.h"
#include "context.h"
#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

void bubble_sort_step(ProgramContext* program){
    DynamicArr* arr = program->arr;

    if(program->iterator_i >= arr->size - 1){ // condição de parada loop 1
        program->sort_state = STATE_IDLE;
        return;
    }

    int j = program->iterator_j;

    if(arr->item_arr[j].value > arr->item_arr[j+ 1].value){ // comparação
        int temp = arr->item_arr[j].value;
        arr->item_arr[j].value = arr->item_arr[j + 1].value;
        arr->item_arr[j + 1].value = temp;

        ALLEGRO_COLOR temp_color = arr->item_arr[j].color;
        arr->item_arr[j].color = arr->item_arr[j + 1].color;
        arr->item_arr[j + 1].color = temp_color;
    }

    program->iterator_j++; // incremento j

    if(program->iterator_j >= arr->size - 1 - program->iterator_i){ // condição de parada loop 2
        program->iterator_j = 0;
        program->iterator_i++;
    }
}

void insertion_sort_step(ProgramContext* program){
    DynamicArr* arr = program->arr;


    if(program->iterator_i > arr->size - 1){ // condição de parada loop for
        program->sort_state = STATE_IDLE;
        return;
    }

    if(program->iterator_i == 0 || 
    !(program->iterator_j >= 0 && arr->item_arr[program->iterator_j].value > program->key)){
        program->key = arr->item_arr[program->iterator_i].value;
        program->iterator_j = program->iterator_i - 1;
    }

    if(program->iterator_j >= 0 && arr->item_arr[program->iterator_j].value > program->key){
        arr->item_arr[program->iterator_j + 1] = arr->item_arr[program->iterator_j];
        program->iterator_j--;
    }

    if(!(program->iterator_j >= 0 && arr->item_arr[program->iterator_j].value > program->key)){
        arr->item_arr[program->iterator_j + 1].value = program->key;
        program->iterator_i++;
    }
}

/*
- se i for maior que size, para
- program->key = arr[i]
- j = i - 1



*/