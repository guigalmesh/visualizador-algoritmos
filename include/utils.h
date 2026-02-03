#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <context.h>


void must_init(bool test, const char* description);
void register_event_sources(EventContext* event, RenderContext* render);
void init_sequence(ProgramContext* program);
void update_render_geometry(RenderContext* render);
void get_mouse_logical_pos(RenderContext* render, int raw_mx, int raw_my, float* out_x, float* out_y);
bool is_mouse_hovering(UIElements* el, RenderContext *ren, float mx, float my);
void ui_update_hover_flag(UIContext* ui, RenderContext* render, float raw_mx, float raw_my);
void create_text(UIContext* ui, ALLEGRO_FONT *font, int id, float x_pct, float y_pct, const char *text);
void create_icon_button(UIContext* ui, RenderContext* render, float s_pct, int id, float x_pct, float y_pct, IconType iid, ButtonAction onClick);
void create_text_button(UIContext* ui, RenderContext* render, int id, float x_pct, float y_pct, const char *name, ButtonAction onClick);
void swap(ItemArr *item_a, ItemArr *item_b);
void update_ui_visibility(UIContext* ui, int current_state);
void draw_debug_hitbox(UIElements* el);

#endif