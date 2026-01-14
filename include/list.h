#ifndef INPUT_H
#define INPUT_H
#include <allegro5/allegro.h>

typedef struct ItemArr{
    int value;
    ALLEGRO_COLOR color;
}ItemArr;

typedef struct DynamicArr{
    ItemArr* item_arr;
    int size;
    int capacity;
    int max_number;
}DynamicArr;

DynamicArr* create_arr(int initial_capacity);
void destroy_arr(DynamicArr* array);
void append_arr(DynamicArr* array, int value);
DynamicArr* generate_arr(int n_items, int min, int max);
void print_arr(DynamicArr* arr);

#endif