#ifndef RENDER_H
#define RENDER_H

#include "list.h"
#include "context.h"

#define ITEM_CANVAS_HEIGHT 300
#define ITEM_CANVAS_WIDTH 900

void draw_scaled_render_target(ProgramContext* program);
void draw_itens(DynamicArr* arr);
void draw_button(ProgramContext* program, UIElements* elements, int element);
void draw_menu(ProgramContext* program);
void draw_bubble(ProgramContext* program);
void draw_insertion(ProgramContext* program);
void program_render(ProgramContext* program);

#endif