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
    if(el->type == TYPE_TEXT) return false;

    if(!el->is_visible){
        return false;
    }

    if(el->type == TYPE_BUTTON){
        float ex = el->x;
        float ey = el->y;

        float x1 = ex - (float)el->width / 2.0f;
        float y1 = ey - (float)el->height / 2.0f;
        float x2 = ex + (float)el->width / 2.0f;
        float y2 = ey + (float)el->height / 2.0f;

        if(mx >= x1 && my >= y1 && mx <= x2 && my <= y2)
            return true;
    }
    
    return false;       
}

void ui_update_hover_flag(UIContext* ui, RenderContext* render, float raw_mx, float raw_my){
    //Convertendo a escala do mouse
    float scale_x = (float)render->screen_w / LOGICAL_WIDTH;
    float scale_y = (float)render->screen_h / LOGICAL_HEIGHT;

    float logical_mx = raw_mx / scale_x;
    float logical_my = raw_my / scale_y;

    for(int i = 0; i < NMB_ELEMENTS; i++){
        UIElements* el = &ui->elements[i];
        //printf("element %d is visible? %d\n", i, el->is_visible);
        if(el->type == TYPE_TEXT) continue;

        if(!el->is_visible){
            el->is_hovering = false;
            continue;
        }

        if(is_mouse_hovering(el, logical_mx, logical_my))
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

    el->data.button.x_render = render->screen_w * x_pct;
    el->data.button.y_render = render->screen_h * y_pct;

    el->width = s_pct;
    el->height = s_pct;

    float center_x = LOGICAL_WIDTH * x_pct;
    float center_y = LOGICAL_HEIGHT * y_pct;

    el->x = center_x - (el->width / 2.0f);
    el->y = center_y - (el->height / 2.0f);

    el->data.button.onClick = onClick;

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

    el->data.button.x_render = render->screen_w * x_pct;
    el->data.button.y_render = render->screen_h * y_pct;

    el->data.button.UIfont = ui->fonts->starmap_normal;
    el->data.button.UIfont_s = ui->fonts->starmap_normal_s;

    el->color = ui->palette.black;

    el->data.button.onClick = onClick;


    el->is_visible = true;
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

void draw_debug_hitbox(UIElements* el) {
    if (!el->is_visible) return;
    
    // Desenha a caixa exata que o is_mouse_hovering está usando
    al_draw_rectangle(
        el->x, 
        el->y, 
        el->x + el->width, 
        el->y + el->height, 
        al_map_rgb(255, 0, 0), // Vermelho
        1.0 // Espessura fina
    );
    
    // Desenha um ponto no X,Y para você saber onde é a âncora
    al_draw_filled_circle(el->x, el->y, 2, al_map_rgb(0, 255, 0));
}