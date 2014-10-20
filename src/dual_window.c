#include "dual_window.h"
#include <pebble.h>

static unsigned s_count_1 = 0;
static unsigned s_count_2 = 0;
static char s_count_str_1[3] = "0\0\0";
static char s_count_str_2[3] = "0\0\0";
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_42_bold;
static GBitmap *s_res_action_plus_white;
static GBitmap *s_res_action_refresh_white;
static TextLayer *s_textlayer_1;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *s_textlayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, 0);
  
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_res_action_plus_white = gbitmap_create_with_resource(RESOURCE_ID_ACTION_PLUS_WHITE);
  s_res_action_refresh_white = gbitmap_create_with_resource(RESOURCE_ID_ACTION_REFRESH_WHITE);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(32, 0, 80, 51));
  text_layer_set_background_color(s_textlayer_1, GColorBlack);
  text_layer_set_text_color(s_textlayer_1, GColorWhite);
  text_layer_set_text(s_textlayer_1, "0");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_action_plus_white);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_action_refresh_white);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_action_plus_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(32, 98, 80, 51));
  text_layer_set_background_color(s_textlayer_2, GColorBlack);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "0");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_2, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(s_textlayer_2);
  gbitmap_destroy(s_res_action_plus_white);
  gbitmap_destroy(s_res_action_refresh_white);
}
// END AUTO-GENERATED UI CODE

static void count_1_reset() {
  s_count_1 = 0;
  strcpy(s_count_str_1, "0\0\0");
  text_layer_set_text(s_textlayer_1, s_count_str_1);
}

static void count_2_reset() {
  s_count_2 = 0;
  strcpy(s_count_str_2, "0\0\0");
  text_layer_set_text(s_textlayer_2, s_count_str_2);
}

static void up_single_click_handler(ClickRecognizerRef rec, void *context) {
  if(s_count_1 < 99) {
    s_count_1++;
    snprintf(s_count_str_1, 3, "%d", s_count_1);
    
    text_layer_set_text(s_textlayer_1, s_count_str_1);
  }
}

static void select_single_click_handler(ClickRecognizerRef rec, void *context) {
  count_1_reset();
  count_2_reset();
}

static void down_single_click_handler(ClickRecognizerRef rec, void *context) {
  if(s_count_2 < 99) {
    s_count_2++;
    snprintf(s_count_str_2, 3, "%d", s_count_2);
    
    text_layer_set_text(s_textlayer_2, s_count_str_2);
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
}

static void handle_window_unload(Window *window) {
  destroy_ui();
}

void show_dual_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_set_click_config_provider(s_window, (ClickConfigProvider) click_config_provider);
  window_stack_push(s_window, true);
}

void hide_dual_window(void) {
  window_stack_remove(s_window, true);
}
