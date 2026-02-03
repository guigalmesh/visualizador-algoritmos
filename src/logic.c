#include "context.h"
#include "utils.h"
#include "render.h"
#include "algos.h"
#include "list.h"
#include <allegro5/allegro.h>
#include <stdio.h>

void button_bubble_sort(StateContext* state, UIContext* ui, SortContext* sort){
    state->programState = BUBBLE_STATE;

    update_ui_visibility(ui, state->programState);
    
    sort->arr = generate_arr(100, 1, 100);
}

void button_back_to_menu(StateContext* state, UIContext* ui, SortContext* sort){
    state->programState = MENU_STATE;

    update_ui_visibility(ui, state->programState);
   
    sort->i = 0;
    sort->j = 0;
    sort->is_holding_key = false;
    sort->sort_state = SORTSTATE_IDLE;
    destroy_arr(sort->arr);
}

void button_insertion_sort(StateContext* state, UIContext* ui, SortContext* sort){
    state->programState = INSERTION_STATE;

    update_ui_visibility(ui, state->programState);
    
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
    sort->state = PHASE_INIT_OUTER;
}

void button_start_bubble(StateContext* state, UIContext* ui, SortContext* sort){
    sort->i = 0;
    sort->j = 0;

    sort->sort_state = SORTSTATE_BUBBLE;
    sort->state = PHASE_INIT_OUTER;
}

void handle_clicks(UIContext* ui, StateContext* stctx, SortContext* soctx){
    for(int i = 0; i < NMB_ELEMENTS; i++){
        UIElements* el = &ui->elements[i];

        if(el->type == TYPE_TEXT) continue;

        if(el->is_hovering){
            el->data.button.onClick(stctx, ui, soctx);
            return;
        } 
    }
}

void handle_resize(RenderContext* render){
    al_acknowledge_resize(render->display);
    update_render_geometry(render);
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
                    for(int i = 0; i < 100; i++)
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

                ui_update_hover_flag(&program->ui, &program->render, event.mouse.x, event.mouse.y);
                
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                handle_clicks(&program->ui, &program->state, &program->sort);
                break;
        }
        if(program->state.redraw && al_is_event_queue_empty(program->event.queue)){
            program_render(program);
            program->state.redraw = false;
        }
    }
}