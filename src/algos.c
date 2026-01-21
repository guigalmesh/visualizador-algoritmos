#include "list.h"
#include "context.h"
#include "render.h"
#include "utils.h"
#include "algos.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

void bubble_sort_step(SortContext* ctx){
    DynamicArr* arr = ctx->arr;

    switch(ctx->state){
        case PHASE_INIT_OUTER:
            if(ctx->i >= arr->size - 1){
                ctx->state = PHASE_FINISHED;
                return;
            }
            ctx->j = 0;
            ctx->state = PHASE_COMPARE_LOOP;
        case PHASE_COMPARE_LOOP:
            if(ctx->j >= arr->size - ctx->i - 1){
                ctx->i++;
                ctx->state = PHASE_INIT_OUTER;
                return;
            }
            if(arr->item_arr[ctx->j].value > arr->item_arr[ctx->j + 1].value){
                ctx->state = PHASE_SWAP;
                return;
            }
            ctx->j++;
            break;
        case PHASE_SWAP:
            swap(&arr->item_arr[ctx->j], &arr->item_arr[ctx->j + 1]);
            ctx->j++;
            ctx->state = PHASE_COMPARE_LOOP;
            return;
        case PHASE_FINISHED:
            break;
    }
}

void insertion_sort_step(SortContext* sort){
    DynamicArr* arr = sort->arr;

    if(sort->i >= arr->size){
        sort->sort_state = SORTSTATE_IDLE;
        return;
    }

    if(!sort->is_holding_key){
        sort->key_value = arr->item_arr[sort->i].value;
        sort->key_color = arr->item_arr[sort->i].color;

        sort->j = sort->i - 1;
        sort->is_holding_key = true;
        return;
    }

    if(sort->j >= 0 && arr->item_arr[sort->j].value > sort->key_value){
        arr->item_arr[sort->j + 1] = arr->item_arr[sort->j];

        sort->j--;
        return;
    }

    arr->item_arr[sort->j + 1].value = sort->key_value;
    arr->item_arr[sort->j + 1].color = sort->key_color;

    sort->i++;
    sort->is_holding_key = false;
}