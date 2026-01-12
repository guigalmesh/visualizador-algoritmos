#include "context.h"
#include "utils.h"
#include "render.h"
#include <allegro5/allegro.h>
#include <stdio.h>

void button_bubble_sort(ProgramContext* program){
    program->programState = BUBBLE_STATE;
    program->number_list = lst_generate(10, 1, 100);
}

void button_back_to_menu(ProgramContext* program){
    program->programState = MENU_STATE;
}

void button_insertion_sort(ProgramContext* program){
    program->programState = INSERTION_STATE;
    program->number_list = lst_generate(30, 1, 10);
}

void program_loop(ProgramContext* program){
    ALLEGRO_EVENT event;

    al_start_timer(program->logic_timer);
    register_event_sources(program);

    while(program->program_running){
        al_wait_for_event(program->queue, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                program->redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                program->mouse_x = event.mouse.x;
                program->mouse_y = event.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                for(int i = 0; i < 4; i++){
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