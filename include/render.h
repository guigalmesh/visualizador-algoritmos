#ifndef RENDER_H
#define RENDER_H

#include "list.h"
#include "context.h"

#define ITEM_CANVAS_HEIGHT 300
#define ITEM_CANVAS_WIDTH 900

void draw_scaled_render_target(RenderContext* render, UIContext* ui);
void draw_itens(DynamicArr* arr);
void draw_text(UIText* texts, int id);
void draw_button(EventContext* event, UIButtons* buttons, int element);
void draw_menu(UIContext* ui, EventContext* event);
void draw_bubble(UIContext* ui, EventContext* event, SortContext* sort);
void draw_insertion(UIContext* ui, EventContext* event, SortContext* sort);
void program_render(ProgramContext* program);

#endif