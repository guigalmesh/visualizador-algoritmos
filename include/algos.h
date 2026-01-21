#ifndef ALGOS_H
#define ALGOS_H
#include "list.h"
#include "context.h"

// yields points para algoritmos iterativos
enum{ 
    PHASE_INIT_OUTER, 
    PHASE_COMPARE_LOOP, 
    PHASE_SWAP, 
    PHASE_FINISHED 
};

void bubble_sort_step(SortContext* sort);
void insertion_sort_step(SortContext* sort);

#endif