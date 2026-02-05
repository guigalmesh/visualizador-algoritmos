#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "context.h"
#include "list.h"
#include "utils.h"

DynamicArr* create_arr(int initial_capacity){
    DynamicArr *arr = (DynamicArr*)malloc(sizeof(DynamicArr));
    if(arr == NULL){
        printf("failed to initialize DynamicArr arr\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
    arr->item_arr = (ItemArr*)malloc(initial_capacity * sizeof(ItemArr));
    if(arr->item_arr == NULL){
        printf("failed to initialize item_array\n");
        exit(1);
    }

    return arr;
}

void destroy_arr(DynamicArr* arr){
    if(arr){
        free(arr->item_arr);
        free(arr);
    }
}

void append_arr(DynamicArr* arr, int value){
    if(arr->size >= arr->capacity){
        arr->capacity *= 2;
        arr->item_arr = realloc(arr->item_arr, sizeof(ItemArr) * arr->capacity);
        if(arr->item_arr == NULL){
            printf("failed to resize item_arr\n");
            exit(1);
        }
    }

    arr->item_arr[arr->size].value = value;
    arr->item_arr[arr->size].color = al_map_rgb(0, 255, 0);
    arr->size++;
}

DynamicArr* generate_arr(int array_size, int min, int max){
    srand(time(NULL));
    DynamicArr* arr = create_arr(array_size);
    arr->max_number = max;
    for(int i = 0; i < array_size; i++){
        int value = (rand() % max) + min;
        append_arr(arr, value);
    }

    return arr;
}

void print_arr(DynamicArr* arr){
    printf("array: ");
    for(int i = 0; i < arr->size; i++){
        int k = arr->item_arr[i].value;
        printf("%d ", k);
    }
    printf("\n");
}