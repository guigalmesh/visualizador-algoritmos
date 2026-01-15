#include "context.h"
#include "utils.h"
#include "render.h"
#include "algos.h"
#include "list.h"
#include <allegro5/allegro.h>
#include <stdio.h>

void button_bubble_sort(ProgramContext* program){
    program->programState = BUBBLE_STATE;
    program->elements[INSERTION_SORT].is_visible = false;
    program->elements[BUBBLE_SORT].is_visible = false;
    program->elements[BACK_TO_MENU].is_visible = true;
    program->elements[CLOSE_PROGRAM].is_visible = false;
    program->arr = generate_arr(1000, 1, 10000);
}

void button_back_to_menu(ProgramContext* program){
    program->programState = MENU_STATE;
    program->elements[INSERTION_SORT].is_visible = true;
    program->elements[BUBBLE_SORT].is_visible = true;
    program->elements[BACK_TO_MENU].is_visible = false;
    program->elements[CLOSE_PROGRAM].is_visible = true;
}

void button_insertion_sort(ProgramContext* program){
    program->programState = INSERTION_STATE;
    program->elements[INSERTION_SORT].is_visible = false;
    program->elements[BUBBLE_SORT].is_visible = false;
    program->elements[BACK_TO_MENU].is_visible = true;
    program->elements[CLOSE_PROGRAM].is_visible = false;
    program->arr = generate_arr(100, 1, 100);
}

void button_close_program(ProgramContext* program){
    program->program_running = false;
}

void button_test_algo(ProgramContext* program){
    program->iterator_i = 0;
    program->iterator_j = 0;

    program->sort_state = STATE_BUBBLE;
}

void program_loop(ProgramContext* program){
    ALLEGRO_EVENT event;

    al_start_timer(program->logic_timer);
    register_event_sources(program);

    while(program->program_running){
        al_wait_for_event(program->queue, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:

                if(program->sort_state == STATE_BUBBLE){
                    for(int i = 0; i < 100; i++)
                        bubble_sort_step(program);
                }

                program->redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                program->mouse_x = event.mouse.x;
                program->mouse_y = event.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                for(int i = 0; i < 6; i++){
                    if(is_mouse_hovering_button(program, program->elements, i)){
                        if(program->elements[i].onClick != NULL){
                            program->elements[i].onClick(program);
                            break;
                        }
                    }
                }
                break;
        }
        if(program->redraw && al_is_event_queue_empty(program->queue)){
            program_render(program);
            program->redraw = false;
        }
    }
}