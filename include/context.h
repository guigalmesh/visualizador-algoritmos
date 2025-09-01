#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#define LOGICAL_WIDTH 1280
#define LOGICAL_HEIGHT 720
#define MAX_ELEMENTS 32

//Cores carregadas com al_map_rgb()
typedef struct ColorPalette{
    ALLEGRO_COLOR black;
    ALLEGRO_COLOR white;
    ALLEGRO_COLOR green;
}ColorPalette;

//Fontes ttf utilizadas
typedef struct FontSet{
    ALLEGRO_FONT *debug_font;
    ALLEGRO_FONT *starmap_large;
    ALLEGRO_FONT *starmap_normal;
    ALLEGRO_FONT *starmap_normal_s;
}FontSet;

//Botões e elementos em da UI
typedef struct UIElements{
    char text[100];
    float x, y;
    float width, height;
}UIElements;

enum UI_Names{
    VISUALIZER,
    BUBBLE_SORT,
    SELECTION_SORT
};

//Estados do programa
enum ProgramState{
    MENU,
    BUBBLE,
    INSERTION
};

//Struct que contém as informações do programa, é passado em toda função
typedef struct ProgramContext{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *render_target;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *logic_timer;
    int programState;
    bool redraw;
    bool program_running;
    UIElements elements[MAX_ELEMENTS];
    ColorPalette palette;
    FontSet *fonts;
    float mouse_x, mouse_y;
}ProgramContext;

//Carrega os elementos da UI
void create_user_interface(ProgramContext* program);
//Carrega as cores
void create_color_palette(ColorPalette* palette);
//Carrega as fontes
void create_fonts(FontSet* fonts);
//Chama várias funções de criação
void create_program_context(ProgramContext* program);
//Libera várias coisas chamadas
void destroy_program_context(ProgramContext* program);

#endif 