#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <context.h>


void must_init(bool test, const char* description);
void register_event_sources(EventContext* event, RenderContext* render);
void init_sequence(ProgramContext* program);
bool is_mouse_hovering_button(EventContext* event, UIElements* elements, int element);
void get_button_hitbox(UIElements* elements, int element);
void create_button(UIContext* ui, RenderContext* render, int id, float x_pct, float y_pct, const char *name, ButtonAction onClick);

#endif