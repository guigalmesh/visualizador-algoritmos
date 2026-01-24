#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <context.h>


void must_init(bool test, const char* description);
void register_event_sources(EventContext* event, RenderContext* render);
void init_sequence(ProgramContext* program);
bool is_mouse_hovering_button(EventContext* event, UIButtons* buttons, int id);
void get_button_hitbox(UIButtons* buttons, int id);
void create_text(UIContext* ui, ALLEGRO_FONT *font, int id, float x_pct, float y_pct, const char *text);
void create_button(UIContext* ui, RenderContext* render, int id, float x_pct, float y_pct, const char *name, ButtonAction onClick);
void swap(ItemArr *item_a, ItemArr *item_b);
void update_ui_visibility(UIContext* ui, int current_state);

#endif