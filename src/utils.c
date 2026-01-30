#include "utils.h"
#include "context.h"
#include "render.h"

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

bool is_mouse_hovering(UIElements *el, float mx, float my){
    if(!el->is_visible)
        return false;
    
    if(mx >= el->x && mx <= el->x + el->width 
    && my >= el->y && my <= el->y + el->height)
            return true;

    return false;
}

void ui_update_hover_flag(UIContext* ui, float mouse_x, float mouse_y){
    for(int i = 0; i < NMB_ELEMENTS; i++){
        UIElements* el = &ui->elements[i];

        if(el->type == TYPE_TEXT) continue;

        if(!el->is_visible){
            el->is_hovering = false;
            continue;
        }

        if(is_mouse_hovering(el, mouse_x, mouse_y))
            el->is_hovering = true;
        else
            el->is_hovering = false;
    }
    // da pra adicionar a mudança do ponteiro do mouse quando há hover aqui
}

void create_text(UIContext* ui, ALLEGRO_FONT* font, int id, float x_pct, float y_pct, const char* text){
    strcpy(ui->elements[id].data.text.content, text);

    ui->elements[id].type = TYPE_TEXT;

    ui->elements[id].x = LOGICAL_WIDTH * x_pct;
    ui->elements[id].y = LOGICAL_HEIGHT * y_pct;

    ui->elements[id].data.text.UIfont = font;
    ui->elements[id].color = ui->palette.black;

    ui->elements[id].is_visible = true;
}

void create_icon_button(UIContext* ui, RenderContext* render, float s_pct, int id, float x_pct, float y_pct, ButtonAction onClick){
    ui->elements[id].type = TYPE_BUTTON;
    ui->elements[id].data.button.button_type = BUTTON_ICON;

    ui->elements[id].x = LOGICAL_WIDTH * x_pct;
    ui->elements[id].y = LOGICAL_HEIGHT * y_pct;
    ui->elements[id].data.button.x_render = render->screen_w * x_pct;
    ui->elements[id].data.button.y_render = render->screen_h * y_pct;

    ui->elements[id].width = s_pct * render->screen_h / 2;
    ui->elements[id].height = s_pct * render->screen_w / 2;

    ui->elements[id].data.button.onClick = onClick;

    ui->elements[id].color = ui->palette.black;

    ui->elements[id].is_visible = true;
}

void create_text_button(UIContext* ui, RenderContext* render, int id, float x_pct, float y_pct, const char* text, ButtonAction onClick){
    strcpy(ui->elements[id].data.button.label, text);
    
    ui->elements[id].type = TYPE_BUTTON;
    ui->elements[id].data.button.button_type = BUTTON_TEXT;

    ui->elements[id].x = LOGICAL_WIDTH * x_pct;
    ui->elements[id].y = LOGICAL_HEIGHT * y_pct;
    ui->elements[id].data.button.x_render = render->screen_w * x_pct;
    ui->elements[id].data.button.y_render = render->screen_h * y_pct;

    ui->elements[id].data.button.UIfont = ui->fonts->starmap_normal;
    ui->elements[id].data.button.UIfont_s = ui->fonts->starmap_normal_s;

    ui->elements[id].color = ui->palette.black;

    ui->elements[id].data.button.onClick = onClick;

    ui->elements[id].width = al_get_text_width(ui->fonts->starmap_normal, ui->elements->data.button.label);
    ui->elements[id].height = al_get_font_line_height(ui->fonts->starmap_normal);

    ui->elements[id].is_visible = true;
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

void update_ui_visibility(UIContext* ui, int current_state){
    for(int i = 0; i < NMB_ELEMENTS; i++){
        if(ui->elements[i].visible_mask & current_state)
            ui->elements[i].is_visible = true;
        else
            ui->elements[i].is_visible = false;
    }
}