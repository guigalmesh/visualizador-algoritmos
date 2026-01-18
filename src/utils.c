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

void register_event_sources(EventContext* event, RenderContext* render){
    al_register_event_source(event->queue, al_get_timer_event_source(event->logic_timer));
    al_register_event_source(event->queue, al_get_display_event_source(render->display));
    al_register_event_source(event->queue, al_get_mouse_event_source());
}

void init_sequence(ProgramContext* program){
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_font_addon(), "font");
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_install_mouse(), "mouse");
    create_program_context(program);
}

bool is_mouse_hovering_button(EventContext* event, UIElements* elements, int element){
    if(elements[element].is_visible == false)
        return false;
    if(event->mouse_x >= elements[element].x1 && event->mouse_y >= elements[element].y1 
    && event->mouse_x <= elements[element].x2 && event->mouse_y <= elements[element].y2)
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

void create_button(UIContext* ui, RenderContext* render, int id, float x_pct, float y_pct, const char *text, ButtonAction onClick){
    strcpy(ui->elements[id].text, text);

    ui->elements[id].x = LOGICAL_WIDTH * x_pct;
    ui->elements[id].y = LOGICAL_HEIGHT * y_pct;
    ui->elements[id].x_render = render->screen_w * x_pct;
    ui->elements[id].y_render = render->screen_h * y_pct;

    ui->elements[id].UIfont = ui->fonts->starmap_normal;
    ui->elements[id].UIfont_s = ui->fonts->starmap_normal_s;
    ui->elements[id].color = ui->palette.black;

    ui->elements[id].onClick = onClick;
    get_button_hitbox(ui->elements, id);
}

void swap(ItemArr *item_a, ItemArr *item_b){
    int temp;
    temp = item_a->value;
    item_a->value = item_b->value;
    item_b->value = temp;

    ALLEGRO_COLOR color;
    color = item_a->color;
    item_a->color = item_b->color;
    item_b->color = color;
}

