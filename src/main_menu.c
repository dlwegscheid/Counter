#include "main_menu.h"
#include "dual_window.h"
#include "solo_window.h"

#include <pebble.h>

#define NUM_MENU_ITEMS 4
#define NUM_MENU_SECTIONS 1
  
static Window *s_window;
static SimpleMenuLayer *s_simplemenulayer;
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem menu_items[NUM_MENU_ITEMS];

static void dual_up_select_handler (int index, void *ctx) {
  show_dual_window();
}

static void solo_up_select_handler (int index, void *ctx) {
  show_solo_window();
}

static void dual_down_select_handler (int index, void *ctx) {
  menu_items[index].subtitle = "Coming soon!";

  layer_mark_dirty(simple_menu_layer_get_layer(s_simplemenulayer));
}

static void solo_down_select_handler (int index, void *ctx) {
  menu_items[index].subtitle = "Coming soon!";

  layer_mark_dirty(simple_menu_layer_get_layer(s_simplemenulayer));
}

static void handle_window_load(Window *window) {
  int num_items = 0;
  
  menu_items[num_items++] = (SimpleMenuItem){
    .title = "Dual Up",
    .callback = dual_up_select_handler,
  };
  menu_items[num_items++] = (SimpleMenuItem){
    .title = "Single Up",
    .callback = solo_up_select_handler,
  };
  menu_items[num_items++] = (SimpleMenuItem){
    .title = "Dual Down",
    .callback = dual_down_select_handler,
  };
  menu_items[num_items++] = (SimpleMenuItem){
    .title = "Single Down",
    .callback = solo_down_select_handler,
  };
  
  menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_MENU_ITEMS,
    .items = menu_items,
  };
  
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_frame(window_layer);

  s_simplemenulayer = simple_menu_layer_create(bounds, s_window, menu_sections, NUM_MENU_SECTIONS, NULL);
  layer_add_child(window_layer, simple_menu_layer_get_layer(s_simplemenulayer));
}

static void handle_window_unload(Window* window) {
  simple_menu_layer_destroy(s_simplemenulayer);
  window_destroy(s_window);
}

void show_main_menu(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_menu(void) {
  window_stack_remove(s_window, true);
}