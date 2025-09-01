#include "utils.h"
#include "context.h"

#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void must_init(bool test, const char* description){
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void register_event_sources(ProgramContext* program){
    al_register_event_source(program->queue, al_get_timer_event_source(program->logic_timer));
    al_register_event_source(program->queue, al_get_display_event_source(program->display));
    al_register_event_source(program->queue, al_get_mouse_event_source());
}

void init_sequence(ProgramContext* program){
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_font_addon(), "font");
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_install_mouse(), "mouse");
    create_program_context(program);
}

bool mouse_isHovering_button(ProgramContext* program, UIElements* elements, int element){
    if(program->mouse_x >= elements[element].x1 && program->mouse_y >= elements[element].y1 
    && program->mouse_x <= elements[element].x2 && program->mouse_y <= elements[element].y2)
        return true;
    return false;
}

void get_button_hitbox(UIElements* elements, int button){
    int width = al_get_text_width(
        elements[button].UIfont, 
        elements[button].text);
    int height = al_get_font_line_height(elements[button].UIfont);
    elements[button].x1 = elements[button].x - (float)width / 2;
    elements[button].y1 = elements[button].y - (float)height / 2;
    elements[button].x2 = elements[button].x + (float)width / 2;
    elements[button].y2 = elements[button].y + (float)height / 2;
    printf("x = %.2f y = %.2f\n", elements[button].x, elements[button].y);
    printf("x1 = %.2f, y1 = %.2f, x2 = %.2f, y2 = %.2f\n", elements[button].x1, elements[button].y1, elements[button].x2, elements[button].y2);
}

