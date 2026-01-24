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

    int screen_w = al_get_display_width(render->display);
    int screen_h = al_get_display_height(render->display);

    float scale_x = (float)screen_w / LOGICAL_WIDTH;
    float scale_y = (float)screen_h / LOGICAL_HEIGHT;
    float scale = fmin(scale_x, scale_y);

    float scaled_w = LOGICAL_WIDTH * scale;
    float scaled_h = LOGICAL_HEIGHT * scale;
    float offset_x = (screen_w - scaled_w) / 2;
    float offset_y = (screen_h - scaled_h) / 2;

    al_clear_to_color(ui->palette.black);
    al_draw_scaled_bitmap(render->render_target, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, 
        offset_x, offset_y, scaled_w, scaled_h, 0);
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

void draw_text(UIText* texts, int id){
    al_draw_text(texts[id].UIfont, texts[id].color, 
        texts[id].x, texts[id].y, 
        ALLEGRO_ALIGN_CENTER, texts[id].text);
}

void draw_button(EventContext* event, UIButtons* buttons, int id){
    ALLEGRO_FONT* font = is_mouse_hovering_button(event, buttons, id) ?
    buttons[id].UIfont_s : buttons[id].UIfont;
    al_draw_text(font, buttons[id].color, 
        buttons[id].x, buttons[id].y, 
        ALLEGRO_ALIGN_CENTER, buttons[id].text);
}

void draw_menu(UIContext* ui, EventContext* event){
    //Titulo "VISUALIZER"
    draw_text(ui->texts, VISUALIZER);
    //Botão "BUBBLE SORT"
    draw_button(event, ui->buttons, BUBBLE_SORT);
    //Botão "INSERTION SORT"
    draw_button(event, ui->buttons, INSERTION_SORT);
    //Botão "CLOSE PROGRAM"
    draw_button(event, ui->buttons, CLOSE_PROGRAM);
}

void draw_bubble(UIContext* ui, EventContext* event, SortContext* sort){
    //Botão "BACK"
    draw_button(event, ui->buttons, BACK_TO_MENU);

    draw_button(event, ui->buttons, BUBBLE_START);

    draw_itens(sort->arr);
}

void draw_insertion(UIContext* ui, EventContext* event, SortContext* sort){
    //Botão "BACK"
    draw_button(event, ui->buttons, BACK_TO_MENU);

    draw_button(event, ui->buttons, INSERTION_START);

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
    al_flip_display();
}