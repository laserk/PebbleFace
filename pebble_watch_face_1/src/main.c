#include <pebble.h>

// main watch face window
static Window *_sWindow;
// main Text UI for the watch
static TextLayer *_sTextLayer;
//customize Font
static GFont _sTimeFont;
static BitmapLayer *_sBitmapLayer;
static GBitmap *_sBitmap;

static void main_window_load(Window *window){
  // Load font res
  _sTimeFont = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DOS_VGA_42));

  //Load bitmap res
  _sBitmap=gbitmap_create_with_resource(RESOURCE_ID_BackGroundImage);

  Layer *window_layer= window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
    
  //Create bitmap layer and set before the text
  _sBitmapLayer = bitmap_layer_create(bounds) ;
  bitmap_layer_set_bitmap(_sBitmapLayer, _sBitmap)  ;
  
  layer_add_child(window_get_root_layer(_sWindow),bitmap_layer_get_layer(_sBitmapLayer));
  
  //Create text layer after bitmap layer
   _sTextLayer=text_layer_create(
     GRect(0, PBL_IF_BW_ELSE(58,52), bounds.size.w, 50));
  
  text_layer_set_background_color(_sTextLayer,GColorClear);
  text_layer_set_text_color(_sTextLayer, GColorChromeYellow);
  
  text_layer_set_font(_sTextLayer, fonts_get_system_font(FONT_KEY_GOTHIC_09));
  text_layer_set_text_alignment(_sTextLayer, GTextAlignmentCenter);
  text_layer_set_font(_sTextLayer, _sTimeFont);

  layer_add_child(window_get_root_layer(_sWindow),text_layer_get_layer(_sTextLayer));
 
  
}
static void main_window_unload(Window *window){
    gbitmap_destroy(_sBitmap);
    bitmap_layer_destroy(_sBitmapLayer);
    fonts_unload_custom_font(_sTimeFont);
    text_layer_destroy(_sTextLayer);
}  

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(_sTextLayer, s_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time();
}


static void init(){
  _sWindow = window_create();
  window_set_window_handlers(_sWindow , (WindowHandlers){
   .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_background_color(_sWindow, GColorBlack);
  window_stack_push(_sWindow, true);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
 

}

static void deinit(){
  window_destroy(_sWindow);

}

int main (){
  init ();
  
  app_event_loop();
  
  deinit();
  
  return 0;
}