#include <pebble.h>
  
  
  
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_day_layer;
static TextLayer *s_date_layer;


static TextLayer *s_leftbar_layer;
static TextLayer *s_rightbar_layer;
static TextLayer *s_left_layer;
static TextLayer *s_right_layer;

static void update_time(BatteryChargeState chargeState) {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";
  static char day[] = "Wednesday";
  static char date[] = "00 MTH";
  static char secs[] = "00";

  static char percent_show[] = "00 %";
  uint8_t percent = chargeState.charge_percent;
  snprintf(percent_show, 5, "%i%%", percent);
  //snprintf(percent_show, sizeof(battery_text), "%d%% charged", chargeState.charge_percent);

  //APP_LOG(APP_LOG_LEVEL_DEBUG, "percent: %s", percent_show);
//  text_layer_set_text(s_left_layer, percent_show);

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    //Use 2h hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
    //strftime(buffer, sizeof("44:44"), "00:00", tick_time);
  } else {
    //Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  strftime(day, sizeof("Wednesdayx"), "%A", tick_time);
  strftime(date, sizeof("00 MTH"), "%e %b", tick_time);
  strftime(secs, sizeof("00"), "%S", tick_time);
  
  //text_layer_set_text(s_date_layer, "00 MTH");
   
  
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
    text_layer_set_text(s_day_layer, day);
    text_layer_set_text(s_date_layer, date);
    text_layer_set_text(s_right_layer, secs);
    text_layer_set_text_alignment(s_right_layer, GTextAlignmentRight);

  text_layer_set_text_alignment(s_date_layer, GTextAlignmentRight);
  text_layer_set_text(s_left_layer, percent_show);

}

static void main_window_load(Window *window) {
  static GFont s_time_font;
  static GFont s_day_font;


//  s_day_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_RENEGADO_14));
  s_day_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SARA_27));

  //s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_RENEGADO_39));
//  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SARA_53));
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TIME_68));
//  GFont custom_font = fonts_load_custom_font (resource_get_handle(RESOURCE_ID_FONT_OSP_DIN_44));

  
  //day
  s_day_layer = text_layer_create(GRect(0, 15, 144, 35));
  text_layer_set_background_color(s_day_layer, GColorClear);
  text_layer_set_text_color(s_day_layer, GColorPictonBlue);
  text_layer_set_text(s_day_layer, "Thisaday");
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 43, 144, 69));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text(s_time_layer, "00:00");
  //date       from left, from top, size from left, size from top
  //s_date_layer = text_layer_create(GRect(60, 104, 84, 40));
  s_date_layer = text_layer_create(GRect(0, 110, 144, 30));
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorPictonBlue);
  text_layer_set_text(s_date_layer, "00 MTH");
   text_layer_set_text_alignment(s_date_layer, GTextAlignmentRight);
  

  

 //------  NOT NEEDED?? -------------------------------------------
  s_leftbar_layer = text_layer_create(GRect(0, 157, 72, 11));
  text_layer_set_background_color(s_leftbar_layer, GColorWhite);
  text_layer_set_text_color(s_leftbar_layer, GColorBlack);
  

  s_rightbar_layer = text_layer_create(GRect(72, 157, 144, 11));
  text_layer_set_background_color(s_rightbar_layer, GColorWhite);
  text_layer_set_text_color(s_rightbar_layer, GColorBlack);
//------  NOT NEEDED??----------------------------------------------
  
#ifdef PBL_COLOR
  //window_set_background_color(s_main_window, GColorDukeBlue);
  window_set_background_color(s_main_window, GColorBlack);
#else
  window_set_background_color(s_main_window, GColorBlack);
#endif
  
  //percent       from left, from top, size from left, size from top
  #ifdef PBL_COLOR
    s_left_layer = text_layer_create(GRect(0, 149, 52, 20));
  #else
    s_left_layer = text_layer_create(GRect(0, 153, 52, 20));
  #endif
  text_layer_set_background_color(s_left_layer, GColorClear);
  text_layer_set_text_color(s_left_layer, GColorDarkGray);

  text_layer_set_text(s_left_layer, "00 %");

  //seconds       from left, from top, size from left, size from top
  #ifdef PBL_COLOR
    s_right_layer = text_layer_create(GRect(124, 149, 20, 20)); /// CHECK DIMENSIONS
  #else
    s_right_layer = text_layer_create(GRect(124, 153, 20, 20)); /// CHECK DIMENSIONS
  #endif
  text_layer_set_background_color(s_right_layer, GColorClear);
  text_layer_set_text_color(s_right_layer, GColorDarkCandyAppleRed);

  text_layer_set_text(s_right_layer, "00");  /// SECONDS

  
  // Improve the layout to be more like a watchface
  //text_layer_set_font(s_time_layer, fonts_get_system_font(s_time_font));
  text_layer_set_font(s_time_layer, s_time_font);

  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
//  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_font(s_date_layer, s_day_font);
  
//  text_layer_set_font(s_day_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_font(s_day_layer, s_day_font);
  
  
  
  text_layer_set_font(s_left_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));


  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_day_layer));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
//  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_leftbar_layer));
//  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_rightbar_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_left_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_right_layer));
  


  // Make sure the time is displayed from the start
  update_time(battery_state_service_peek());
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_day_layer);
  text_layer_destroy(s_date_layer);

  
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(battery_state_service_peek());
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_set_background_color(s_main_window, GColorBlack);

  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
