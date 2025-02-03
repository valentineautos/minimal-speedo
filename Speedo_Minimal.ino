#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <lvgl.h>
#include "lvgl_port_v8.h"
#include "fonts/ubuntu_24.h"
#include "fonts/ubuntu_100.h"
#include "fonts/ubuntu_200.h"
#include "fonts/font_awesome_icons_small.h"
#include "splash_5.h"
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <Preferences.h>
#include "GaugeMinimal.h"

// Intialise memory
Preferences prefs;

// ESPNow structures
typedef struct struct_speedo {
  uint8_t flag;
  uint8_t speed_mph;
  uint8_t speed_kmph;
  int8_t fuel_perc;
} struct_speedo;

struct_speedo SpeedoData;
struct_buttons ButtonData;

// Global components

// Screens
lv_obj_t *startup_scr;              // Black startup screen
lv_obj_t *splash_scr;               // Splash screen
lv_obj_t *daily_scr;                // Daily screen
lv_obj_t *track_scr;                // Track screen
lv_obj_t *dimmer;                   // Dimmer overlay

// Daily screen
lv_obj_t *speed_meter;              // Speed meter
lv_obj_t *speed_label;              // Daily speed value display
lv_obj_t *speed_unit;               // Daily speed unit display
lv_obj_t *fuel_arc;                 // Fuel arc
lv_obj_t *fuel_icon;                // Fuel icon
lv_obj_t *fuel_label;               // Fuel label

lv_meter_scale_t *speed_scale;      // Scale for the indicator
lv_meter_indicator_t *outline;      // Dynamic sized outline
lv_meter_indicator_t *speed_indic;  // Speed moving part
lv_meter_indicator_t *fuel_indic;   // Fuel moving part

// Track screen
lv_obj_t *track_speed_value;        // Track speed value display
lv_obj_t *track_speed_unit;         // Track speed unit display

// Global styles
static lv_style_t style_unit_text;
static lv_style_t style_icon;

// Font Awesome symbols
#define FUEL_SYMBOL "\xEF\x94\xAF"

// Display labels
#define UNIT_MPH "mph"
#define UNIT_KMPH "kmph"
const int MAX_MPH = 160;
const int MAX_MPH_TICK_FREQ = 20;
const int MAX_KMPH = 270;
const int MAX_KMPH_TICK_FREQ = 30;

// ESPNow checks
volatile bool data_ready = false;
volatile bool button_pressed = false;
bool startup_ready = false;
bool startup_complete = false;

// LVGL Time
hw_timer_t* timer = nullptr;

// Speed unit switcher
bool is_mph; // true for mph, false for kmph

// Icons using the above structure.
// Positions are for the single icon only - labels will be calculated automatically
// Structure: horz_pos, vert_pos, vert_offset, alert, warning, flag_when
struct_icon_parts FuelData = {0, 180, 5, 0, 100, 25, 10, BELOW, "%"};

// ------------------------------------------------------------
// Various initialisations for the ESP32-S3 LCD Driver Board &
// ST7701 LCD Screen featured in the project videos.
//
// Only change if you know what you're doing
// ------------------------------------------------------------
void scr_init() {
  ESP_Panel *panel = new ESP_Panel();
  panel->init();

  #if LVGL_PORT_AVOID_TEAR
    ESP_PanelBus_RGB *rgb_bus = static_cast<ESP_PanelBus_RGB *>(panel->getLcd()->getBus());
    rgb_bus->configRgbFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
    rgb_bus->configRgbBounceBufferSize(LVGL_PORT_RGB_BOUNCE_BUFFER_SIZE);
  #endif
  panel->begin();

  lvgl_port_init(panel->getLcd(), panel->getTouch());

  startup_scr = lv_scr_act(); // Make startup screen active
  lv_obj_set_style_bg_color(startup_scr, PALETTE_BLACK, 0);
  lv_obj_set_style_bg_opa(startup_scr, LV_OPA_COVER, 0);
}

void wifi_init() {
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void IRAM_ATTR onTimer() {
  lv_tick_inc(1);
}

void timer_init() {
  const uint32_t lv_tick_frequency = 1000;  // 1 kHz = 1ms period

  timer = timerBegin(lv_tick_frequency);  // Configure the timer with 1kHz frequency
  if (!timer) {
    Serial.println("Failed to configure timer!");
    while (1)
      ;  // Halt execution on failure
  }

  timerAttachInterrupt(timer, &onTimer);  // Attach the ISR to the timer
  Serial.println("Timer initialized for LVGL tick");
}

// Styles
void make_styles(void) {
    lv_style_init(&style_unit_text);
    lv_style_set_text_font(&style_unit_text, &ubuntu_24);
    lv_style_set_text_color(&style_unit_text, PALETTE_WHITE);

    lv_style_init(&style_icon);
    lv_style_set_text_font(&style_icon, &font_awesome_icons_small);
    lv_style_set_text_color(&style_icon, PALETTE_GREY);
}

// ESPNow received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  // Write to the correct structure based on ESPNow flag
  switch (incomingData[0]) {
    case (FLAG_STARTUP):
      startup_ready = true;
      break;
    case (FLAG_SET_CHANNEL): {
      int8_t new_channel = incomingData[1];
      esp_wifi_set_channel(new_channel, WIFI_SECOND_CHAN_NONE);
      break;
    }
    case (FLAG_BUTTONS):
      memcpy(&ButtonData, incomingData, sizeof(ButtonData));
      button_pressed = true;
      break;
    case (FLAG_CANBUS):
      memcpy(&SpeedoData, incomingData, sizeof(SpeedoData));
      data_ready = true;
      break;
  }
}

// Check and update colors
void update_alert_colors(void) {
  lv_obj_set_style_text_color(fuel_icon, get_state_color(FuelData, SpeedoData.fuel_perc, true), 0);
  lv_obj_set_style_arc_color(fuel_arc, get_state_color(FuelData, SpeedoData.fuel_perc, false), LV_PART_INDICATOR);
}

// Move icons and set opacities
void update_show_num(void) {
  // Set battery icon position
  Serial.print("showing nums");
  lv_obj_align(fuel_icon, LV_ALIGN_CENTER, FuelData.horz_pos, FuelData.vert_pos - (is_show_num ? (ICON_MOVEMENT - FuelData.vert_offset) : 0));
  lv_obj_set_style_opa(fuel_label, (is_show_num) ? LV_OPA_COVER : LV_OPA_TRANSP, 0);

  update_alert_colors();
}

// Switch between screens
void update_mode(void) {
  if (is_track_mode) {
    lv_scr_load_anim(track_scr, LV_SCR_LOAD_ANIM_MOVE_TOP, 1000, 0, false);
  } else {
    lv_scr_load_anim(daily_scr, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 1000, 0, false);
  }
}

// Update fuel arc with warnings
void update_fuel(int8_t new_fuel = SpeedoData.fuel_perc) {
  // check for -1 initialisation
  if (new_fuel == -1) {
    lv_label_set_text(fuel_label, DEFAULT_LABEL);   // Icon label with unit
    lv_arc_set_value(fuel_arc, FuelData.min);
    return;
  }
  
  Serial.print("new fuel: ");
  Serial.println(new_fuel);

  // Convert to text for labels
  char fuel_text_unit[6];  // With unit

  // // Convert to strings and add unit
  sprintf(fuel_text_unit, "%d%s", new_fuel, FuelData.unit);

  Serial.print("fuel_text_unit: ");
  Serial.println(fuel_text_unit);

  // Daily screen
  lv_label_set_text(fuel_label, fuel_text_unit);   // Icon label with unit
  lv_arc_set_value(fuel_arc, new_fuel);      // Arc position
}

// Update speed value and needle
// Recieves float kmph
void update_speed() {
  int speed_now = (is_mph) ? SpeedoData.speed_mph : SpeedoData.speed_kmph;

  char speed_text[4];
  sprintf(speed_text, "%d", speed_now);

  lv_label_set_text(speed_label, speed_text);
  lv_meter_set_indicator_value(speed_meter, speed_indic, speed_now);

  lv_label_set_text(track_speed_value, speed_text);
}

void update_levels(void) {
  update_fuel();
  update_speed();

  // Check and adjust colors
  update_alert_colors();
}

// Change between mph / kpmh
void update_units(void) {
  uint16_t max_value = (is_mph) ? MAX_MPH : MAX_KMPH;
  uint8_t minor_ticks = (max_value / ((is_mph) ? MAX_MPH_TICK_FREQ : MAX_KMPH_TICK_FREQ)) + 1;

  lv_meter_set_scale_ticks(speed_meter, speed_scale, minor_ticks, TICK_WIDTH, TICK_LENGTH, PALETTE_DARK_GREY);
  lv_meter_set_scale_major_ticks(speed_meter, speed_scale, 1, TICK_WIDTH, TICK_LENGTH, PALETTE_WHITE, TICK_TEXT_OFFSET);
  lv_meter_set_scale_range(speed_meter, speed_scale, 0, max_value, 270, 135);

  lv_meter_set_indicator_end_value(speed_meter, outline, max_value);
  
  lv_label_set_text(speed_unit, (is_mph) ? UNIT_MPH : UNIT_KMPH);
  lv_label_set_text(track_speed_unit, (is_mph) ? UNIT_MPH : UNIT_KMPH);
}

void update_brightness(void) {
  // convert from 0-11 to dimmed value
  uint8_t dimmed_perc = dimmer_lv * 22;
  lv_obj_set_style_bg_opa(dimmer, dimmed_perc, 0);
}


// Save states to memory
void save_units(bool new_mph) {
  is_mph = new_mph;
  prefs.putBool("is_mph", is_mph);

  update_units();
}

void save_mode(bool new_mode) {
  is_track_mode = new_mode;
  prefs.putBool("is_track_mode", new_mode);

  update_mode();
}

void save_show_num(bool new_show) {
  is_show_num = new_show;
  prefs.putBool("is_show_num", new_show);

  // update display after save
  update_show_num();
}

void save_brightness() {
  prefs.putInt("dimmer_lv", dimmer_lv);

  // update brightness after save
  update_brightness();
}

// Button press handling
void handle_button_press(void) {
  // 350z - Top left button
  if (ButtonData.button == BUTTON_SETTING) {
    switch (ButtonData.press_type) {
      case CLICK_EVENT_CLICK:
        // Show minimal design
        save_show_num(false);
        break;
      case CLICK_EVENT_DOUBLE: 
        save_units(!is_mph);
        break;
      case CLICK_EVENT_HOLD:
        // Show daily mode
        save_mode(false);
        break;
    }
  }

  // 350z - Top right button
  if (ButtonData.button == BUTTON_MODE) {
    switch (ButtonData.press_type) {
      case CLICK_EVENT_CLICK:
        // Show minimal design
        save_show_num(true);
        break;
      case CLICK_EVENT_HOLD:
        // show track mode
        save_mode(true);
        break;
    }
  }

  // 350z - Top right button
  if (ButtonData.button == BUTTON_BRIGHTNESS_UP) {
    switch (ButtonData.press_type) {
      case CLICK_EVENT_CLICK:
        // Increase brightness / lower overlay opacity
        if (dimmer_lv > 0) {
          dimmer_lv--;
          save_brightness();
        }
        break;
    }
  }

  // 350z - Bottom right button
  if (ButtonData.button == BUTTON_BRIGHTNESS_DOWN) {
    switch (ButtonData.press_type) {
      case CLICK_EVENT_CLICK:
      // Lower brightness / increase overlay opacity
        if (dimmer_lv < 9) {
          dimmer_lv++;
          save_brightness();
        }
        break;
    }
  }
}

void make_speed_meter(void) {
  speed_meter = lv_meter_create(daily_scr);
  lv_obj_set_style_pad_all(speed_meter, 0, 10);
  lv_obj_set_style_bg_color(speed_meter, PALETTE_BLACK, 0);
  lv_obj_set_style_border_width(speed_meter, 0, 0);
  lv_obj_center(speed_meter);
  lv_obj_set_size(speed_meter, 470, 470);
  lv_obj_remove_style(speed_meter, NULL, LV_PART_INDICATOR);
  
  // Add a scale
  speed_scale = lv_meter_add_scale(speed_meter);

  outline = lv_meter_add_arc(speed_meter, speed_scale, OUTLINE_WIDTH, PALETTE_WHITE, 2);
  lv_meter_set_indicator_start_value(speed_meter, outline, 0);

  lv_obj_set_style_text_font(speed_meter, &ubuntu_24, LV_PART_TICKS);
  lv_obj_set_style_text_color(speed_meter, PALETTE_WHITE, LV_PART_TICKS);

  speed_indic = lv_meter_add_needle_line(speed_meter, speed_scale, 5, PALETTE_RED, -10);

  lv_obj_t *inner_circle = lv_obj_create(daily_scr);
  lv_obj_set_size(inner_circle, 200, 200);
  lv_obj_center(inner_circle);
  lv_obj_set_style_bg_color(inner_circle, PALETTE_BLACK, 0);
  lv_obj_set_style_bg_opa(inner_circle, LV_OPA_COVER, 0);
  lv_obj_set_style_radius(inner_circle, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_border_width(inner_circle, 1, 0);
  lv_obj_set_style_border_color(inner_circle, PALETTE_GREY, 0);
}

void make_fuel_arc(void) {
  fuel_arc = lv_arc_create(daily_scr);
  lv_obj_set_size(fuel_arc, 446, 446);
  lv_arc_set_rotation(fuel_arc, 65);
  lv_arc_set_bg_angles(fuel_arc, 0, 50);
  lv_arc_set_range(fuel_arc, FuelData.min, FuelData.max);
  lv_obj_center(fuel_arc);
  lv_arc_set_mode(fuel_arc, LV_ARC_MODE_REVERSE);

  lv_obj_set_style_arc_color(fuel_arc, PALETTE_WHITE, LV_PART_INDICATOR);
  lv_obj_set_style_arc_color(fuel_arc, PALETTE_DARK_GREY, LV_PART_MAIN);
  lv_obj_set_style_arc_rounded(fuel_arc, false, LV_PART_MAIN);
  lv_obj_set_style_arc_rounded(fuel_arc, false, LV_PART_INDICATOR);
  lv_obj_set_style_arc_width(fuel_arc, 4, LV_PART_MAIN);
  lv_obj_set_style_arc_width(fuel_arc, 4, LV_PART_INDICATOR);
  lv_obj_remove_style(fuel_arc, NULL, LV_PART_KNOB);

  lv_arc_set_value(fuel_arc, FuelData.max);
}

void make_speed_number(void) {
  static lv_style_t style_speed_text;
  lv_style_init(&style_speed_text);
  lv_style_set_text_font(&style_speed_text, &ubuntu_100);
  lv_style_set_text_color(&style_speed_text, PALETTE_WHITE);

  speed_label = lv_label_create(daily_scr);
  lv_obj_add_style(speed_label, &style_speed_text, 0);
  lv_obj_align(speed_label, LV_ALIGN_CENTER, 0, -5);

  speed_unit = lv_label_create(daily_scr);
  lv_obj_add_style(speed_unit, &style_unit_text, 0);
  lv_obj_align(speed_unit, LV_ALIGN_CENTER, 0, 50);
}

void make_track_speed_number(void) {
  static lv_style_t style_track_speed_text;
  lv_style_init(&style_track_speed_text);
  lv_style_set_text_font(&style_track_speed_text, &ubuntu_200);
  lv_style_set_text_color(&style_track_speed_text, PALETTE_WHITE);

  track_speed_value = lv_label_create(track_scr);
  lv_obj_add_style(track_speed_value, &style_track_speed_text, 0);
  lv_obj_align(track_speed_value, LV_ALIGN_CENTER, 0, -5);

  track_speed_unit = lv_label_create(track_scr);
  lv_obj_add_style(track_speed_unit, &style_unit_text, 0);
  lv_obj_align(track_speed_unit, LV_ALIGN_CENTER, 0, 100);
}

void make_icons(void) {
  fuel_icon = lv_label_create(daily_scr);
  lv_label_set_text(fuel_icon, FUEL_SYMBOL);
  lv_obj_add_style(fuel_icon, &style_icon, 0);

  fuel_label = lv_label_create(daily_scr);
  lv_obj_add_style(fuel_label, &style_unit_text, 0);
  lv_obj_align(fuel_label, LV_ALIGN_CENTER, FuelData.horz_pos, FuelData.vert_pos + LABEL_LOWER);
}

void make_splash_screen(void) {
  splash_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(splash_scr, PALETTE_BLACK, 0);

  lv_obj_t *icon_five = lv_img_create(splash_scr);
  lv_img_set_src(icon_five, &splash_5);
  lv_obj_align(icon_five, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_img_recolor(icon_five, PALETTE_WHITE, 0);
  lv_obj_set_style_img_recolor_opa(icon_five, LV_OPA_COVER, 0);
}

void make_daily_screen(void) {
  daily_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(daily_scr, PALETTE_BLACK, 0);

  make_speed_meter();
  make_fuel_arc();
  make_speed_number();
  make_icons();
}

void make_track_screen(void) {
  track_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(track_scr, PALETTE_BLACK, 0);

  make_track_speed_number();
}

void make_dimmer(void) {
    dimmer = lv_layer_top();

    lv_obj_set_size(dimmer, 480, 480);
    lv_obj_center(dimmer);
    lv_obj_set_style_bg_color(dimmer, PALETTE_BLACK, 0);
    
    update_brightness();
}

// Two step managed 
bool complete = false; // flag for screen changes to prevent recurssion

void change_loading_scr(lv_timer_t *timer) {
  lv_obj_t *next_scr = (lv_obj_t *)timer->user_data;
  lv_scr_load_anim(next_scr, LV_SCR_LOAD_ANIM_FADE_IN, 1000, 0, true); // delete startup on exit

  if (!complete) {
    lv_timer_t *exit_timer = lv_timer_create(change_loading_scr, 2000, (is_track_mode) ? track_scr : daily_scr); // back to blank
    lv_timer_set_repeat_count(exit_timer, 1);
    complete = true;
  }
}

// if no startup message received, start anyway
void force_splash(lv_timer_t *timer) {
  // avoid refire if complete
  if (!startup_complete) {
    start_splash();
    startup_complete = true;
  }
}

// load the splash screen
void start_splash() {
  lv_scr_load_anim(splash_scr, LV_SCR_LOAD_ANIM_FADE_IN, 1000, 0, false);
  
  lv_timer_t *exit_timer = lv_timer_create(change_loading_scr, 3500, startup_scr); // back to blank
  lv_timer_set_repeat_count(exit_timer, 1);
}

// initial load and default screens
void make_ui() {
  make_styles();

  // Create initial screen
  make_splash_screen();
  make_daily_screen();
  make_track_screen(); 
  make_dimmer();
}

// Initialise startup values
void init_values() {
  SpeedoData.speed_mph = 0;
  SpeedoData.speed_kmph = 0;
  SpeedoData.fuel_perc = -1;

  update_show_num(); // Initialise show num
  update_units(); // Initialise units
  update_levels(); // Populate labels with defaults
}

void setup()
{
  Serial.begin(115200);

  // defaults and setting from memory
  prefs.begin("speedo_store", false);
  is_mph = prefs.getBool("is_mph", true);
  is_track_mode = prefs.getBool("is_track_mode", false);
  is_show_num = prefs.getBool("is_show_num", true);
  dimmer_lv = prefs.getInt("dimmer_lv", 0);

  scr_init();
  wifi_init();

  // Make the UI
  make_ui();
  init_values();

  timer_init();

  lv_timer_t *startup_timer = lv_timer_create(force_splash, STARTUP_OVERRIDE_TIMER, startup_scr); // back to blank
  lv_timer_set_repeat_count(startup_timer, 1);
}

void loop(){
  lv_timer_handler();

  if (startup_ready && !startup_complete) {
      delay(120);
      start_splash();
      startup_ready = false;
    }

  if (data_ready) {
    update_levels();
    data_ready = false;
  }

  if (button_pressed) {
    handle_button_press();
    button_pressed = false;
  }
}