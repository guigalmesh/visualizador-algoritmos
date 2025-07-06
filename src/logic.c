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
        }
        if(program->redraw && al_is_event_queue_empty(program->queue)){
            program_render(program);
            program->redraw = false;
        }
    }
}