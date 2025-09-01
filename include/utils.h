#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <context.h>

void must_init(bool test, const char* description);
void register_event_sources(ProgramContext* program);
void init_sequence(ProgramContext* program);
bool mouse_isHovering_button(ProgramContext* program, UIElements* elements, int element);
void get_button_hitbox(UIElements* elements, int element);

#endif