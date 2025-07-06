#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>
#include <allegro5/allegro.h>

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

void create_program_context(ProgramContext* program);
void destroy_program_context(ProgramContext* program);

#endif 