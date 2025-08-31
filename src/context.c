#include "context.h"
#include "logic.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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
}

void create_program_context(ProgramContext* program){
    al_set_new_display_flags(ALLEGRO_NOFRAME | ALLEGRO_WINDOWED);
    ALLEGRO_MONITOR_INFO monitor_info;
    al_get_monitor_info(0, &monitor_info);
    int screen_w = monitor_info.x2 - monitor_info.x1;
    int screen_h = monitor_info.y2 - monitor_info.y1;
    ALLEGRO_DISPLAY *display = al_create_display(screen_w, screen_h);
    must_init(display, "display");
    program->display = display;

    ALLEGRO_BITMAP *render_target = al_create_bitmap(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    must_init(render_target, "render target");
    program->render_target = render_target;

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "event queue");
    program->queue = queue;
    
    ALLEGRO_TIMER *logic_timer = al_create_timer(1 / 60.0);
    program->logic_timer = logic_timer;

    program->program_running = true;

    program->programState = MENU;

    ColorPalette palette;
    create_color_palette(&palette);
    program->palette = palette;

    FontSet* fonts = malloc(sizeof(FontSet));
    must_init(fonts, "malloc fonts");
    create_fonts(fonts);
    program->fonts = fonts;
}

void destroy_program_context(ProgramContext* program){
    al_destroy_bitmap(program->render_target);
    al_destroy_event_queue(program->queue);
    al_destroy_display(program->display);
    al_destroy_timer(program->logic_timer);
}
