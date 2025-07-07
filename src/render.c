#include "render.h"
#include "context.h"
#include "logic.h"
#include <math.h>
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

void draw_menu(ProgramContext* program){
    al_draw_text(program->fonts->starmap_large, program->palette.black, 300, 300, ALLEGRO_ALIGN_CENTER, "VISUALIZER");
}

void program_render(ProgramContext* program){
    al_set_target_bitmap(program->render_target);
    switch(program->state){
        case menu:
            draw_menu(program);
            break;
    }
    al_clear_to_color(program->palette.white);
    al_set_target_backbuffer(program->display);
    draw_scaled_render_target(program);
    al_flip_display();
}