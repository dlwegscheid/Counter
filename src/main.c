#include <pebble.h>
#include "main_menu.h"
    
static void init() {
  show_main_menu();
}

static void deinit() {
  hide_main_menu();
}
    
int main(void) {
  init();
  app_event_loop();
  deinit();
}