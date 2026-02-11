#ifndef RENDER_H
#define RENDER_H

#include "list.h"
#include "context.h"

#define ITEM_CANVAS_HEIGHT 300
#define ITEM_CANVAS_WIDTH 900

void draw_scaled_render_target(RenderContext* render, UIContext* ui);
void draw_debug_hitbox(UIElements* el);
void draw_itens(DynamicArr* arr);
void draw_text(UIElements* el);
void draw_icon_button(UIElements* el);
void draw_slider(UIElements* el);
void draw_text_button(UIElements* el);
void draw_button(UIElements* el);
void draw_ui_elements(UIContext* ui);
void draw_menu(UIContext* ui, EventContext* event);
void draw_bubble(UIContext* ui, EventContext* event, SortContext* sort);
void draw_insertion(UIContext* ui, EventContext* event, SortContext* sort);
void program_render(ProgramContext* program);

#endif