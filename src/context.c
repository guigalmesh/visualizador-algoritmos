#include "context.h"
#include "logic.h"
#include "utils.h"
#include "algos.h"
#include "render.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void create_user_interface(UIContext* ui, RenderContext* render){

    create_text(ui, ui->fonts->starmap_large, VISUALIZER, 0.50, 0.25, "VISUALIZER");
    ui->elements[VISUALIZER].visible_mask = MENU_STATE;

    create_text_button(ui, render, BUBBLE_SORT, 0.50, 0.35, "BUBBLE SORT", button_bubble_sort);
    ui->elements[BUBBLE_SORT].visible_mask = MENU_STATE;

    create_text_button(ui, render, INSERTION_SORT, 0.50, 0.45, "INSERTION SORT", button_insertion_sort);
    ui->elements[INSERTION_SORT].visible_mask = MENU_STATE;

    create_icon_button(ui, render, 0.1, BACK_TO_MENU, 0.05, 0.10, button_back_to_menu);
    ui->elements[BACK_TO_MENU].visible_mask = BUBBLE_STATE | INSERTION_STATE;

    create_icon_button(ui, render, 0.1, CLOSE_PROGRAM, 0.90, 0.10, button_close_program);
    ui->elements[CLOSE_PROGRAM].visible_mask = MENU_STATE;

    create_icon_button(ui, render, 0.1, INSERTION_START, 0.90, 0.10, button_start_insertion);
    ui->elements[INSERTION_START].visible_mask = INSERTION_STATE;

    create_icon_button(ui, render, 0.1, BUBBLE_START, 0.90, 0.10, button_start_bubble);
    ui->elements[BUBBLE_START].visible_mask = BUBBLE_STATE;

    update_ui_visibility(ui, MENU_STATE);
}

void create_color_palette(ColorPalette* palette){
    palette->black = al_map_rgb(0, 0, 0);
    palette->white = al_map_rgb(255, 255, 255);
    palette->green = al_map_rgb(0, 255, 0);
}

void create_fonts(FontSet* fonts){
    fonts->debug_font = al_create_builtin_font();
    must_init(fonts->debug_font, "debug_font");
    fonts->starmap_large = al_load_ttf_font("assets/starmap.TTF", 48, 0);
    must_init(fonts->starmap_large, "starmap_large");
    fonts->starmap_normal = al_load_ttf_font("assets/starmap.TTF", 24, 0);
    must_init(fonts->starmap_normal, "starmap_normal");
    fonts->starmap_normal_s = al_load_ttf_font("assets/starmap.TTF", 28, 0);
    must_init(fonts->starmap_normal_s, "starmap_normal_s");
}

void create_program_context(ProgramContext* program){
    al_set_new_display_flags(ALLEGRO_NOFRAME | ALLEGRO_WINDOWED);
    ALLEGRO_MONITOR_INFO monitor_info;
    al_get_monitor_info(0, &monitor_info);
    int screen_w = monitor_info.x2 - monitor_info.x1;
    int screen_h = monitor_info.y2 - monitor_info.y1;
    program->render.screen_w = screen_w;
    program->render.screen_h = screen_h;
    ALLEGRO_DISPLAY *display = al_create_display(screen_w, screen_h);
    must_init(display, "display");
    program->render.display = display;

    ALLEGRO_BITMAP *render_target = al_create_bitmap(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    must_init(render_target, "render target");
    program->render.render_target = render_target;

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "event queue");
    program->event.queue = queue;
    
    ALLEGRO_TIMER *logic_timer = al_create_timer(1 / 60.0);
    program->event.logic_timer = logic_timer;

    program->state.program_running = true;

    program->state.programState = MENU_STATE;

    program->sort.sort_state = SORTSTATE_IDLE;

    program->sort.state = PHASE_INIT_OUTER;

    ColorPalette palette;
    create_color_palette(&palette);
    program->ui.palette = palette;

    FontSet* fonts = malloc(sizeof(FontSet));
    must_init(fonts, "malloc fonts");
    create_fonts(fonts);
    program->ui.fonts = fonts;

    create_user_interface(&program->ui, &program->render);
}

void destroy_program_context(ProgramContext* program){
    al_destroy_bitmap(program->render.render_target);
    al_destroy_event_queue(program->event.queue);
    al_destroy_display(program->render.display);
    al_destroy_timer(program->event.logic_timer);
    al_destroy_font(program->ui.fonts->debug_font);
    al_destroy_font(program->ui.fonts->starmap_normal);
    al_destroy_font(program->ui.fonts->starmap_normal_s);
    al_destroy_font(program->ui.fonts->starmap_large);
    free(program->ui.fonts);
}
