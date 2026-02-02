#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "list.h"

#define LOGICAL_WIDTH 1280
#define LOGICAL_HEIGHT 720
#define NMB_ELEMENTS 7

//Estados do programa
enum ProgramState{
    MENU_STATE = 1 << 0,
    BUBBLE_STATE = 1 << 1,
    INSERTION_STATE = 1 << 2
};

typedef enum{
    SORTSTATE_IDLE,
    SORTSTATE_BUBBLE,
    SORTSTATE_INSERTION
} SortState;

enum UI_Elements{
    VISUALIZER,
    BUBBLE_SORT,
    INSERTION_SORT,
    BACK_TO_MENU,
    CLOSE_PROGRAM,
    INSERTION_START,
    BUBBLE_START
};

typedef enum{ BUTTON_ICON, BUTTON_TEXT } ButtonType;

typedef enum{
    TYPE_BUTTON,
    TYPE_TEXT,
    TYPE_SLIDER
}ElementType;

typedef enum {
    ICON_NONE,
    ICON_PLAY,
    ICON_CLOSE,
    ICON_ARROW_LEFT
} IconType;

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

typedef struct RenderContext {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *render_target;
    int screen_w, screen_h;
} RenderContext;

typedef struct EventContext {
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *logic_timer;
    float mouse_x, mouse_y;
} EventContext;

typedef struct StateContext StateContext;
typedef struct UIContext UIContext;
typedef struct SortContext SortContext;
struct UIElements;

//Function pointer para a ação dos botões
typedef void (*ButtonAction)(StateContext*, UIContext*, SortContext*);
typedef void (*DrawElement)(struct UIElements* btn);


typedef struct UIElements{
    float x, y;
    bool is_visible;
    bool is_hovering;
    int visible_mask;
    float width, height;
    ALLEGRO_COLOR color;
    ElementType type;

    union{
        struct{
            ButtonType button_type;
            ButtonAction onClick;
            int icon_size;
            int icon_id;
            float x_render, y_render;
            char label[32];
            ALLEGRO_FONT *UIfont;
            ALLEGRO_FONT *UIfont_s;
        } button;

        struct{
            ALLEGRO_FONT *UIfont;
            char content[100];
        } text;

        struct{
            DrawElement draw;
            int min_value, max_value;
            int* linked_value;
            bool is_dragging;
        } slider;
    } data;

}UIElements;

typedef struct UIContext {
    UIElements elements[NMB_ELEMENTS];
    ColorPalette palette;
    FontSet *fonts;
} UIContext;

typedef struct StateContext {
    int programState;
    bool redraw;
    bool program_running;
} StateContext;

typedef struct SortContext {
    DynamicArr *arr;
    SortState sort_state;
    int array_size;
    int state;
    int j;
    int i;
    bool is_holding_key;
    int key_value;
    ALLEGRO_COLOR key_color;
} SortContext;

//Struct que contém as informações do programa, é passado em toda função
typedef struct ProgramContext{
    RenderContext render;
    EventContext event;
    UIContext ui;
    StateContext state;
    SortContext sort;
}ProgramContext;

//Carrega os elementos da UI
void create_user_interface(UIContext* ui, RenderContext* render);
//Carrega as cores
void create_color_palette(ColorPalette* palette);
//Carrega as fontes
void create_fonts(FontSet* fonts);
//Chama várias funções de criação
void create_program_context(ProgramContext* program);
//Libera várias coisas chamadas
void destroy_program_context(ProgramContext* program);

#endif 