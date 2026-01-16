#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "list.h"

#define LOGICAL_WIDTH 1280
#define LOGICAL_HEIGHT 720
#define MAX_ELEMENTS 6

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

typedef struct ProgramContext ProgramContext;

//Function pointer para a ação dos botões
typedef void (*ButtonAction)(ProgramContext*);

//Botões e elementos em da UI
typedef struct UIElements{
    ALLEGRO_FONT *UIfont;
    ALLEGRO_FONT *UIfont_s;
    ALLEGRO_COLOR color;
    char text[100];
    float x, y, x_render, y_render;
    float width, height;
    float x1, y1, x2, y2;
    bool is_visible;
    ButtonAction onClick;
}UIElements;

enum UI_Names{
    VISUALIZER,
    BUBBLE_SORT,
    INSERTION_SORT,
    BACK_TO_MENU,
    CLOSE_PROGRAM,
    TEST_ALGO
};

//Estados do programa
enum ProgramState{
    MENU_STATE,
    BUBBLE_STATE,
    INSERTION_STATE
};

typedef enum{
    STATE_IDLE,
    STATE_BUBBLE,
    STATE_INSERTION
} SortState;

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
    int screen_w, screen_h;
    DynamicArr *arr;
    SortState sort_state;
    int iterator_j;
    int iterator_i;
    int key;
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