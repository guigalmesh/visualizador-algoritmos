#include "context.h"
#include "utils.h"
#include "render.h"
#include "algos.h"
#include "list.h"
#include <allegro5/allegro.h>
#include <stdio.h>

void button_bubble_sort(StateContext* state, UIContext* ui, SortContext* sort){
    state->programState = BUBBLE_STATE;
    ui->elements[INSERTION_SORT].is_visible = false;
    ui->elements[BUBBLE_SORT].is_visible = false;
    ui->elements[BACK_TO_MENU].is_visible = true;
    ui->elements[CLOSE_PROGRAM].is_visible = false;
    ui->elements[INSERTION_START].is_visible = false;
    ui->elements[BUBBLE_START].is_visible = true;
    sort->arr = generate_arr(100, 1, 100);
}

void button_back_to_menu(StateContext* state, UIContext* ui, SortContext* sort){
    state->programState = MENU_STATE;
    ui->elements[INSERTION_SORT].is_visible = true;
    ui->elements[BUBBLE_SORT].is_visible = true;
    ui->elements[BACK_TO_MENU].is_visible = false;
    ui->elements[CLOSE_PROGRAM].is_visible = true;
    ui->elements[INSERTION_START].is_visible = false;
    ui->elements[BUBBLE_START].is_visible = false;
    sort->i = 0;
    sort->j = 0;
    sort->is_holding_key = false;
    sort->key_value = false;
    sort->sort_state = SORTSTATE_IDLE;
}

void button_insertion_sort(StateContext* state, UIContext* ui, SortContext* sort){
    state->programState = INSERTION_STATE;
    ui->elements[INSERTION_SORT].is_visible = false;
    ui->elements[BUBBLE_SORT].is_visible = false;
    ui->elements[BACK_TO_MENU].is_visible = true;
    ui->elements[CLOSE_PROGRAM].is_visible = false;
    ui->elements[INSERTION_START].is_visible = true;
    ui->elements[BUBBLE_START].is_visible = false;
    sort->arr = generate_arr(100, 1, 100);
}

void button_close_program(StateContext* state, UIContext* ui, SortContext* sort){
    state->program_running = false;
}

void button_start_insertion(StateContext* state, UIContext* ui, SortContext* sort){
    sort->i = 1;
    sort->j = 0;
    sort->is_holding_key = false;
    sort->sort_state = SORTSTATE_INSERTION;
}

void button_start_bubble(StateContext* state, UIContext* ui, SortContext* sort){
    sort->i = 0;
    sort->j = 0;

    sort->sort_state = SORTSTATE_BUBBLE;
}

void program_loop(ProgramContext* program){
    ALLEGRO_EVENT event;

    al_start_timer(program->event.logic_timer);
    register_event_sources(&program->event, &program->render);

    while(program->state.program_running){
        al_wait_for_event(program->event.queue, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:

                if(program->sort.sort_state == SORTSTATE_BUBBLE){
                    for(int i = 0; i < 10; i++)
                        bubble_sort_step(&program->sort);
                }

                if(program->sort.sort_state == SORTSTATE_INSERTION){
                    for(int i = 0; i < 10; i++)
                        insertion_sort_step(&program->sort);
                }
                program->state.redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                program->event.mouse_x = event.mouse.x;
                program->event.mouse_y = event.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                for(int i = 0; i < MAX_ELEMENTS; i++){
                    if(is_mouse_hovering_button(&program->event, program->ui.elements, i)){
                        if(program->ui.elements[i].onClick != NULL){
                            program->ui.elements[i].onClick(&program->state, &program->ui, &program->sort);
                            break;
                        }
                    }
                }
                break;
        }
        if(program->state.redraw && al_is_event_queue_empty(program->event.queue)){
            program_render(program);
            program->state.redraw = false;
        }
    }
}