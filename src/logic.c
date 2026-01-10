#include "context.h"
#include "utils.h"
#include "render.h"
#include <allegro5/allegro.h>

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
            // isso aqui é horrivel, melhorar depois pra uma solução mais robusta
                if(program->programState == MENU_STATE){
                    if(is_mouse_hovering_button(program, program->elements, BUBBLE_SORT)){
                        program->programState = BUBBLE_STATE;
                        List* list = lst_generate(30, 1, 10);
                        program->number_list = list;
                        lst_print(list);
                    }
                    if(is_mouse_hovering_button(program, program->elements, INSERTION_SORT))
                        program->programState = INSERTION_STATE;
                }
                if(program->programState == BUBBLE_STATE){
                    if(is_mouse_hovering_button(program, program->elements, BACK_TO_MENU))
                        program->programState = MENU_STATE;
                }
                if(program->programState == INSERTION_STATE){
                    if(is_mouse_hovering_button(program, program->elements, BACK_TO_MENU))
                        program->programState = MENU_STATE;
                }
                break;
        }
        if(program->redraw && al_is_event_queue_empty(program->queue)){
            program_render(program);
            program->redraw = false;
        }
    }
}