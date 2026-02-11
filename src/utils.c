#include "utils.h"
#include "context.h"
#include "render.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

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
    must_init(al_init_image_addon(), "images");
    create_program_context(program);
}

void update_render_geometry(RenderContext* render){
    render->screen_w = al_get_display_width(render->display);
    render->screen_h = al_get_display_height(render->display);

    float scale_x = (float)render->screen_w / LOGICAL_WIDTH;
    float scale_y = (float)render->screen_h / LOGICAL_HEIGHT;

    render->scale = scale_x < scale_y ? scale_x : scale_y;

    float scaled_w = LOGICAL_WIDTH * render->scale;
    float scaled_h = LOGICAL_HEIGHT * render->scale;

    render->offset_x = (render->screen_w - scaled_w) / 2.0f;
    render->offset_y = (render->screen_h - scaled_h) / 2.0f;
}

void get_mouse_logical_pos(RenderContext* render, int raw_mx, int raw_my, float* out_x, float* out_y){
    *out_x = (raw_mx - render->offset_x) / render->scale;
    *out_y = (raw_my - render->offset_y) / render->scale;
}

bool is_mouse_hovering(UIElements *el, RenderContext *ren, float mx, float my){
    if(el->type == TYPE_TEXT) return false;

    if(!el->is_visible){
        return false;
    }

    bool inside_x = (mx >= el->x) && (mx <= el->x + el->width);
    bool inside_y = (my >= el->y) && (my <= el->y + el->height);
    
    return inside_x && inside_y;
}

void ui_update_hover_flag(UIContext* ui, RenderContext* render, float raw_mx, float raw_my){
    float logical_mx, logical_my;
    get_mouse_logical_pos(render, raw_mx, raw_my, &logical_mx, &logical_my);

    for(int i = 0; i < NMB_ELEMENTS; i++){
        UIElements* el = &ui->elements[i];
        if(el->type == TYPE_TEXT) continue;

        if(!el->is_visible){
            el->is_hovering = false;
            continue;
        }

        if(is_mouse_hovering(el, render, logical_mx, logical_my))
            el->is_hovering = true;
        else
            el->is_hovering = false;
    }
    // da pra adicionar a mudança do ponteiro do mouse quando há hover aqui
}

void create_text(UIContext* ui, ALLEGRO_FONT* font, int id, float x_pct, float y_pct, const char* text){
    UIElements* el = &ui->elements[id];
    
    strcpy(el->data.text.content, text);

    el->type = TYPE_TEXT;

    el->visible_mask = 0;

    el->x = LOGICAL_WIDTH * x_pct;
    el->y = LOGICAL_HEIGHT * y_pct;

    el->data.text.UIfont = font;
    el->color = ui->palette.black;

    el->is_visible = true;
}

void create_icon_button(UIContext* ui, RenderContext* render, float s_pct, int id, float x_pct, float y_pct, IconType iid, ButtonAction onClick){
    UIElements* el = &ui->elements[id];
    
    el->type = TYPE_BUTTON;
    el->data.button.button_type = BUTTON_ICON;
    el->data.button.icon_id = iid;
    el->visible_mask = 0;

    el->width = s_pct;
    el->height = s_pct;

    float center_x = LOGICAL_WIDTH * x_pct;
    float center_y = LOGICAL_HEIGHT * y_pct;

    el->x = center_x - (el->width / 2.0f);
    el->y = center_y - (el->height / 2.0f);

    el->onClick = onClick;

    el->color = ui->palette.black;

    el->is_visible = true;
}

void create_text_button(UIContext* ui, RenderContext* render, int id, float x_pct, float y_pct, const char* text, ButtonAction onClick){
    UIElements* el = &ui->elements[id];
    
    strcpy(el->data.button.label, text);
    
    el->type = TYPE_BUTTON;
    el->data.button.button_type = BUTTON_TEXT;

    el->visible_mask = 0;

    float desired_center_x = LOGICAL_WIDTH * x_pct;
    float desired_center_y = LOGICAL_HEIGHT * y_pct;

    el->width = al_get_text_width(ui->fonts->starmap_normal, el->data.button.label);
    el->height = al_get_font_line_height(ui->fonts->starmap_normal);

    el->x = desired_center_x - (el->width / 2.0f);
    el->y = desired_center_y - (el->height / 2.0f);

    el->data.button.UIfont = ui->fonts->starmap_normal;
    el->data.button.UIfont_s = ui->fonts->starmap_normal_s;

    el->color = ui->palette.black;

    el->onClick = onClick;


    el->is_visible = true;
}

void create_slider(UIContext* ui, SortContext* sort, RenderContext* render, int id, float x_pct, float y_pct, ButtonAction onClick){
    UIElements* el = &ui->elements[id];

    el->type = TYPE_SLIDER;

    el->visible_mask = 0;

    el->data.slider.min_value = MIN_COLUMNS;
    el->data.slider.max_value = MAX_COLUMNS;

    el->width = 12;
    el->height = 12;

    el->data.slider.is_dragging = false;
    el->data.slider.line_size = 100;

    float center_x = LOGICAL_WIDTH * x_pct;
    float center_y = LOGICAL_HEIGHT * y_pct;

    el->x = center_x - (el->width / 2.0f);
    el->y = center_y - (el->height / 2.0f);

    el->data.slider.line_px1 = el->x - (el->data.slider.line_size / 2);
    el->data.slider.line_px2 = el->x + (el->data.slider.line_size / 2);
    el->data.slider.line_y = el->y + (el->width / 2);

    el->onClick = onClick;

    el->data.slider.linked_value = &sort->array_size;
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
        if(ui->elements[i].visible_mask & current_state){
            ui->elements[i].is_visible = true;
        }
        else{
            ui->elements[i].is_visible = false;
        }
    }
}