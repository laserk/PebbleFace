#include <pebble.h>

static Window *_sWindow;
TextLayer *_textLayer;
static void main_window_load(Window *window){}
static void main_window_unload(Window *window){}  

static void init(){
  _sWindow = window_create();
  window_set_window_handlers(_sWindow , (WindowHandlers){
   .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(_sWindow, true);
  _textLayer=text_layer_create(GRect(5, 10, 134, 144));
  text_layer_set_text(_textLayer,"I Love Sophia CHEN ! and I also Love RuoChen KANG!");
  text_layer_set_text_color(_textLayer, GColorBlue);
  text_layer_set_background_color(_textLayer,GColorRajah);
  layer_add_child(window_get_root_layer(_sWindow),text_layer_get_layer(_textLayer));
}

static void deinit(){
  window_destroy(_sWindow);
  text_layer_destroy(_textLayer);
}

int main (){
  init ();
  
  app_event_loop();
  
  deinit();
  
  return 0;
}