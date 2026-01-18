#include "list.h"
#include "context.h"
#include "render.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

void bubble_sort_step(SortContext* sort){
    DynamicArr* arr = sort->arr;

    if(sort->iterator_i >= arr->size - 1){
        sort->sort_state = SORTSTATE_IDLE;
        return;
    }

    int j = sort->iterator_j;

    if(arr->item_arr[j].value > arr->item_arr[j+ 1].value){
        swap(&arr->item_arr[j], &arr->item_arr[j + 1]);
    }

    sort->iterator_j++;

    if(sort->iterator_j >= arr->size - 1 - sort->iterator_i){
        sort->iterator_j = 0;
        sort->iterator_i++;
    }
}

void insertion_sort_step(SortContext* sort){
    DynamicArr* arr = sort->arr;

    if(sort->iterator_i >= arr->size){
        sort->sort_state = SORTSTATE_IDLE;
        return;
    }

    if(!sort->is_holding_key){
        sort->key_value = arr->item_arr[sort->iterator_i].value;
        sort->key_color = arr->item_arr[sort->iterator_i].color;

        sort->iterator_j = sort->iterator_i - 1;
        sort->is_holding_key = true;
        return;
    }

    if(sort->iterator_j >= 0 && arr->item_arr[sort->iterator_j].value > sort->key_value){
        arr->item_arr[sort->iterator_j + 1] = arr->item_arr[sort->iterator_j];

        sort->iterator_j--;
        return;
    }

    arr->item_arr[sort->iterator_j + 1].value = sort->key_value;
    arr->item_arr[sort->iterator_j + 1].color = sort->key_color;

    sort->iterator_i++;
    sort->is_holding_key = false;
}