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

bool is_mouse_hovering_button(ProgramContext* program, UIElements* elements, int element){
    if(elements[element].is_visible == false)
        return false;
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
    elements[button].x1 = elements[button].x_render - (float)width;
    elements[button].y1 = elements[button].y_render - (float)height;
    elements[button].x2 = elements[button].x_render + (float)width;
    elements[button].y2 = elements[button].y_render + (float)height;
}

void create_button(ProgramContext* program, int id, float x_pct, float y_pct, const char *text, ButtonAction onClick){
    strcpy(program->elements[id].text, text);

    program->elements[id].x = LOGICAL_WIDTH * x_pct;
    program->elements[id].y = LOGICAL_HEIGHT * y_pct;
    program->elements[id].x_render = program->screen_w * x_pct;
    program->elements[id].y_render = program->screen_h * y_pct;

    program->elements[id].UIfont = program->fonts->starmap_normal;
    program->elements[id].UIfont_s = program->fonts->starmap_normal_s;
    program->elements[id].color = program->palette.black;

    program->elements[id].onClick = onClick;
    get_button_hitbox(program->elements, id);
}  

