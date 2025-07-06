#include "context.h"
#include "utils.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

void create_program_context(ProgramContext* program){
    al_set_new_display_flags(ALLEGRO_NOFRAME | ALLEGRO_WINDOWED);
    ALLEGRO_MONITOR_INFO monitor_info;
    al_get_monitor_info(0, &monitor_info);
    int screen_w = monitor_info.x2 - monitor_info.x1;
    int screen_h = monitor_info.y2 - monitor_info.y1;
    ALLEGRO_DISPLAY *display = al_create_display(screen_w, screen_h);
    must_init(display, "display");
    program->display = display;

    ALLEGRO_BITMAP *render_target = al_create_bitmap(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    must_init(render_target, "render target");
    program->render_target = render_target;

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "event queue");
    program->queue = queue;
    
    ALLEGRO_TIMER *logic_timer = al_create_timer(1 / 60.0);
    program->logic_timer = logic_timer;

    program->program_running = true;
}

void destroy_program_context(ProgramContext* program){
    al_destroy_bitmap(program->render_target);
    al_destroy_event_queue(program->queue);
    al_destroy_display(program->display);
    al_destroy_timer(program->logic_timer);
}
