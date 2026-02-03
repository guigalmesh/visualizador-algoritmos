#include "render.h"
#include "context.h"
#include "logic.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

void draw_scaled_render_target(RenderContext* render, UIContext* ui){
    al_set_target_backbuffer(render->display);

    al_clear_to_color(ui->palette.black);
    al_draw_scaled_bitmap(render->render_target, 
        0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, 
        render->offset_x, render->offset_y, 
        LOGICAL_WIDTH * render->scale, 
        LOGICAL_HEIGHT * render->scale, 
        0
    );
}

void draw_itens(DynamicArr* arr){
    for(int i = 0; i < arr->size; i++){
        float height = ((float)arr->item_arr[i].value / arr->max_number) * ITEM_CANVAS_HEIGHT;
        float width = ((float)ITEM_CANVAS_WIDTH / arr->size);
        float x1 = (LOGICAL_WIDTH * 0.15f) + (width * i + 1);
        float y1 = LOGICAL_HEIGHT * 0.70f;
        float x2 = x1 + width;
        float y2 = y1 - height;
        al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 0), 3);
        al_draw_filled_rectangle(x1, y1, x2, y2, arr->item_arr[i].color);
    }
}

void draw_text(UIElements* el){
    al_draw_text(el->data.text.UIfont, el->color, 
        el->x, el->y, 
        ALLEGRO_ALIGN_CENTER, el->data.text.content);
}

void draw_icon_button(UIElements* el){
    float x = el->x;
    float y = el->y;
    float w = el->width;
    float h = el->height;

    ALLEGRO_COLOR color = el->is_hovering ? al_map_rgb(0, 255, 0) : al_map_rgb(0, 0, 0);

    float pad = w * 0.15;
    float thick = w * 0.05;

    switch(el->data.button.icon_id){
        case ICON_PLAY:
            al_draw_filled_triangle(x + pad, y + pad, x + pad, 
                y + h - pad, x + w - pad, 
                y + h / 2, color);
            break;
        case ICON_CLOSE:
            al_draw_line(x + pad, y + pad, 
                x + w - pad,  y + h - pad, 
                color, thick);

            al_draw_line(x + pad, y + h - pad, 
                x + w - pad, y + pad, 
                color, thick);
            break;
        case ICON_ARROW_LEFT:
            float center_y = y + h / 2.0f;
    
            float head_start_x = x + pad;
            float head_end_x   = x + (w * 0.4f);
    
            float head_half_h  = (h * 0.25f);
    
            al_draw_filled_triangle(head_start_x, center_y, 
                head_end_x, center_y - head_half_h, 
                head_end_x, center_y + head_half_h, 
                color);
    
            float tail_end_x = x + w - pad;
    
            al_draw_line(head_end_x - 1, center_y, 
                tail_end_x, center_y, 
                color, thick);
            break;
    }
}

void draw_text_button(UIElements* el){
    ALLEGRO_FONT* font = el->is_hovering ? el->data.button.UIfont_s : el->data.button.UIfont;

    float center_x = el->x + (el->width / 2.0f);
    float center_y = el->y + (el->height / 2.0f);
    
    float font_h = al_get_font_line_height(el->data.button.UIfont);
    float text_y = center_y - (font_h / 2.0f);

    al_draw_text(font, el->color, center_x, text_y, ALLEGRO_ALIGN_CENTER, el->data.button.label);
}

void draw_button(UIElements* el){
    switch(el->data.button.button_type){
        case BUTTON_ICON:
            draw_icon_button(el);
            break;
        case BUTTON_TEXT:
            draw_text_button(el);
            break;
    }
}

void draw_ui_elements(UIContext* ui){
    for(int i = 0; i < NMB_ELEMENTS; i++){
        UIElements* el = &ui->elements[i];

        draw_debug_hitbox(el);
        
        if(!el->is_visible) continue;

        switch(ui->elements[i].type){
            case TYPE_TEXT:
                draw_text(el);
                break;
            case TYPE_BUTTON:
                draw_button(el);
                break;
            case TYPE_SLIDER:
                break;
        }
    }
}

void draw_menu(UIContext* ui, EventContext* event){
    draw_ui_elements(ui);
}

void draw_bubble(UIContext* ui, EventContext* event, SortContext* sort){
    draw_ui_elements(ui);

    draw_itens(sort->arr);
}

void draw_insertion(UIContext* ui, EventContext* event, SortContext* sort){
    draw_ui_elements(ui);

    draw_itens(sort->arr);
}

void program_render(ProgramContext* program){
    al_set_target_bitmap(program->render.render_target);
    al_clear_to_color(program->ui.palette.white);
    switch(program->state.programState){
        case MENU_STATE:
            draw_menu(&program->ui, &program->event);
            break;
        case BUBBLE_STATE:
            draw_bubble(&program->ui, &program->event, &program->sort);
            break;
        case INSERTION_STATE:
            draw_insertion(&program->ui, &program->event, &program->sort);
            break;
    }
    al_set_target_backbuffer(program->render.display);
    draw_scaled_render_target(&program->render, &program->ui);
    // Dentro de program_render, ANTES de al_flip_display():

    // 1. Pega a posição crua do mouse
    ALLEGRO_MOUSE_STATE ms;
    al_get_mouse_state(&ms);

    // 2. Converte para lógico usando SUA função atual
    float log_x, log_y;
    get_mouse_logical_pos(&program->render, ms.x, ms.y, &log_x, &log_y);

    // 3. Desenha a cruz no buffer da tela (acima de tudo)
    // Convertemos DE VOLTA para tela para desenhar no lugar exato
    float screen_x = (log_x * program->render.scale) + program->render.offset_x;
    float screen_y = (log_y * program->render.scale) + program->render.offset_y;

    al_draw_line(screen_x - 10, screen_y, screen_x + 10, screen_y, al_map_rgb(0, 255, 255), 2);
    al_draw_line(screen_x, screen_y - 10, screen_x, screen_y + 10, al_map_rgb(0, 255, 255), 2);
    al_flip_display();
}