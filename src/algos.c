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
            ctx->sort_state = SORTSTATE_IDLE;
            break;
    }
}

void insertion_sort_step(SortContext* ctx){
    DynamicArr* arr = ctx->arr;

    switch(ctx->state){
        case PHASE_INIT_OUTER:
            if(ctx->i >= arr->size){
                ctx->state = PHASE_FINISHED;
                return;
            }
            ctx->key_value = arr->item_arr[ctx->i].value;
            ctx->j = ctx->i - 1;
            ctx->state = PHASE_COMPARE_LOOP;
        case PHASE_COMPARE_LOOP:
            if(ctx->j < 0 || arr->item_arr[ctx->j].value < ctx->key_value){
                ctx->state = PHASE_SWAP;
                return;
            }
            swap(&arr->item_arr[ctx->j + 1], &arr->item_arr[ctx->j]);
            ctx->j--;
            return;
        case PHASE_SWAP:
            arr->item_arr[ctx->j + 1].value = ctx->key_value;
            ctx->i++;
            ctx->state = PHASE_INIT_OUTER;
            return;
        case PHASE_FINISHED:
            ctx->sort_state = SORTSTATE_IDLE;
            break;
    }
}