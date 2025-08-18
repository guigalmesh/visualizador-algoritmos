#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#define LOGICAL_WIDTH 1280
#define LOGICAL_HEIGHT 720

typedef struct ColorPalette{
    ALLEGRO_COLOR black;
    ALLEGRO_COLOR white;
    ALLEGRO_COLOR green;
}ColorPalette;

typedef struct FontSet{
    ALLEGRO_FONT *debug_font;
    ALLEGRO_FONT *starmap_large;
    ALLEGRO_FONT *starmap_normal;
}FontSet;

enum ProgramState{
    MENU
};

typedef struct ProgramContext{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *render_target;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *logic_timer;
    int programState;
    bool redraw;
    bool program_running;
    ColorPalette palette;
    FontSet *fonts;
}ProgramContext;

void create_color_palette(ColorPalette* palette);
void create_fonts(FontSet* fonts);
void create_program_context(ProgramContext* program);
void destroy_program_context(ProgramContext* program);

#endif 