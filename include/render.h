#ifndef RENDER_H
#define RENDER_H

#include "context.h"

void draw_scaled_render_target(ProgramContext* program);
void draw_text_selection(ProgramContext* program, UIElements* element);
void draw_menu(ProgramContext* program);
void draw_bubble(ProgramContext* program);
void draw_insertion(ProgramContext* program);
void program_render(ProgramContext* program);

#endif