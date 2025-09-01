#include "render.h"
#include "context.h"
#include "logic.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

void draw_scaled_render_target(ProgramContext* program){
    al_set_target_backbuffer(program->display);

    int screen_w = al_get_display_width(program->display);
    int screen_h = al_get_display_height(program->display);

    float scale_x = (float)screen_w / LOGICAL_WIDTH;
    float scale_y = (float)screen_h / LOGICAL_HEIGHT;
    float scale = fmin(scale_x, scale_y);

    float scaled_w = LOGICAL_WIDTH * scale;
    float scaled_h = LOGICAL_HEIGHT * scale;
    float offset_x = (screen_w - scaled_w) / 2;
    float offset_y = (screen_h - scaled_h) / 2;

    al_clear_to_color(program->palette.black);
    al_draw_scaled_bitmap(program->render_target, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, 
        offset_x, offset_y, scaled_w, scaled_h, 0);
}

void draw_button(ProgramContext* program, UIElements* elements, int element){
    ALLEGRO_FONT* font = mouse_isHovering_button(program, elements, element) ?
    elements[element].UIfont_s : elements[element].UIfont;
    al_draw_text(font, elements[element].color, 
        elements[element].x, elements[element].y, 
        ALLEGRO_ALIGN_CENTER, elements[element].text);
}

void draw_menu(ProgramContext* program){
    ALLEGRO_FONT* starmap_large = program->fonts->starmap_large;
    ALLEGRO_FONT* starmap_normal = program->fonts->starmap_normal;
    ALLEGRO_COLOR black = program->palette.black;
    UIElements* elements = program->elements;
    //Titulo "VISUALIZER"
    UIElements* title = &program->elements[VISUALIZER];
    al_draw_text(starmap_large, 
        black, 
        title->x, title->y, 
        ALLEGRO_ALIGN_CENTER, 
        title->text);
    //Botão "BUBBLE SORT"
    draw_button(program, elements, BUBBLE_SORT);
    //Botão "INSERTION SORT"
    draw_button(program, elements, INSERTION_SORT);
}

void draw_bubble(ProgramContext* program){

}

void draw_insertion(ProgramContext* program){

}

void program_render(ProgramContext* program){
    al_set_target_bitmap(program->render_target);
    al_clear_to_color(program->palette.white);
    switch(program->programState){
        case MENU_STATE:
            draw_menu(program);
            al_draw_textf(program->fonts->debug_font, 
                program->palette.black, 75, 75, ALLEGRO_ALIGN_CENTER, "x = %.2f y = %.2f", 
                program->mouse_x, program->mouse_y);
            break;
        case BUBBLE_STATE:
            draw_bubble(program);
            break;
        case INSERTION_STATE:
            draw_insertion(program);
            break;
    }
    al_set_target_backbuffer(program->display);
    draw_scaled_render_target(program);
    al_flip_display();
}