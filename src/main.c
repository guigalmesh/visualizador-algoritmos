#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>

#define LOGICAL_WIDTH 800
#define LOGICAL_HEIGHT 600

typedef struct ProgramContext{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *render_target;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *logic_timer;
    bool redraw;
    bool program_running;
}ProgramContext;

void must_init(bool test, const char* description){
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

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

void draw_scaled_render_target(ProgramContext* program){
    al_set_target_backbuffer(program->display);

    int screen_w = al_get_display_width(program->display);
    int screen_h = al_get_display_height(program->display);

    float scale_x = (float)screen_w / LOGICAL_WIDTH;
    float scale_y = (float)screen_h / LOGICAL_HEIGHT;
    float scale = fmin(scale_x, scale_y);

    float scaled_w = LOGICAL_WIDTH * scale;
    float scaled_h = LOGICAL_HEIGHT * scale;
    float offset_x = (screen_w - scaled_w) / 2;
    float offset_y = (screen_h - scaled_h) / 2;

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(program->render_target, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, 
        offset_x, offset_y, scaled_w, scaled_h, 0);
}

void program_render(ProgramContext* program){
    al_set_target_bitmap(program->render_target);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_set_target_backbuffer(program->display);
    draw_scaled_render_target(program);
    al_flip_display();
}

void register_event_sources(ProgramContext* program){
    al_register_event_source(program->queue, al_get_timer_event_source(program->logic_timer));
    al_register_event_source(program->queue, al_get_display_event_source(program->display));
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
        }
        if(program->redraw && al_is_event_queue_empty(program->queue)){
            program_render(program);
            program->redraw = false;
        }
    }
}

void init_sequence(ProgramContext* program){
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_font_addon(), "font");
    create_program_context(program);
}

void destroy_program_context(ProgramContext* program){
    al_destroy_bitmap(program->render_target);
    al_destroy_event_queue(program->queue);
    al_destroy_display(program->display);
    al_destroy_timer(program->logic_timer);
}

int main(){
    ProgramContext program;
    init_sequence(&program);

    program_loop(&program);

    destroy_program_context(&program);
    return 0;
}
