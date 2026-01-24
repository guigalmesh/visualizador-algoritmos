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

bool is_mouse_hovering_button(EventContext* event, UIButtons* buttons, int id){
    if(buttons[id].is_visible == false)
        return false;
    if(event->mouse_x >= buttons[id].x1 && event->mouse_y >= buttons[id].y1 
    && event->mouse_x <= buttons[id].x2 && event->mouse_y <= buttons[id].y2)
        return true;
    return false;
}

void get_button_hitbox(UIButtons* buttons, int id){
    int width = al_get_text_width(
        buttons[id].UIfont, 
        buttons[id].text);
    int height = al_get_font_line_height(buttons[id].UIfont);
    buttons[id].x1 = buttons[id].x_render - (float)width;
    buttons[id].y1 = buttons[id].y_render - (float)height;
    buttons[id].x2 = buttons[id].x_render + (float)width;
    buttons[id].y2 = buttons[id].y_render + (float)height;
}

void create_text(UIContext* ui, ALLEGRO_FONT *font, int id, float x_pct, float y_pct, const char *text){
    strcpy(ui->texts[id].text, text);

    ui->texts[id].x = LOGICAL_WIDTH * x_pct;
    ui->texts[id].y = LOGICAL_HEIGHT * y_pct;

    ui->texts->UIfont = font;
    ui->texts->color = ui->palette.black;
}

void create_button(UIContext* ui, RenderContext* render, int id, float x_pct, float y_pct, const char *text, ButtonAction onClick){
    strcpy(ui->buttons[id].text, text);

    ui->buttons[id].x = LOGICAL_WIDTH * x_pct;
    ui->buttons[id].y = LOGICAL_HEIGHT * y_pct;
    ui->buttons[id].x_render = render->screen_w * x_pct;
    ui->buttons[id].y_render = render->screen_h * y_pct;

    ui->buttons[id].UIfont = ui->fonts->starmap_normal;
    ui->buttons[id].UIfont_s = ui->fonts->starmap_normal_s;
    ui->buttons[id].color = ui->palette.black;

    ui->buttons[id].onClick = onClick;
    get_button_hitbox(ui->buttons, id);
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
    for(int i = 0; i < NMB_BUTTONS; i++){
        if(ui->buttons[i].visible_mask & current_state){
            ui->buttons[i].is_visible = true;
        }
        else{
            ui->buttons[i].is_visible = false;
        }
    }

    for(int i = 0; i < NMB_TEXTS; i++){
        if(ui->texts[i].visible_mask & current_state){
            ui->texts[i].is_visible = true;
        }
        else{
            ui->texts[i].is_visible = false;
        }
    }
}