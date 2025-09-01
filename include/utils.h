#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <context.h>

void must_init(bool test, const char* description);
void register_event_sources(ProgramContext* program);
void init_sequence(ProgramContext* program);
bool mouse_isHovering(ProgramContext* program, float x1, float y1, float x2, float y2);

#endif