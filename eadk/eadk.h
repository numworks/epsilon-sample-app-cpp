#ifndef EADK_H
#define EADK_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// Backlight
uint8_t eadk_backlight_brightness();
void eadk_backlight_set_brightness(uint8_t brightness);

// Battery
bool eadk_battery_is_charging();
uint8_t eadk_battery_level();
float eadk_battery_voltage();

// Display
typedef uint16_t eadk_color;
typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
} eadk_rect;
void eadk_display_push_rect(eadk_rect rect, const eadk_color * pixels);
void eadk_display_push_rect_uniform(eadk_rect rect, eadk_color color);
void eadk_display_pull_rect(eadk_rect rect, eadk_color * pixels);
void eadk_display_wait_for_vblank();

// Keyboard
typedef enum {
  left=0,  up=1,     down=2,    right=3,            ok=4,              back=5,
  home=6,  /*B2=7,*/ on_off=8,   /*B4=9,            B5=10,             B6=11, */
  shift=12,alpha=13, xnt=14,    bar=15,             toolbox=16,        backspace=17,
  exp=18,  ln=19,    log=20,    im=21,              comma=22,          Power=23,
  sine=24, cosine=25,tangent=26,pi=27,              sqrt=28,           square=29,
  seven=30,eight=31, nine=32,   left_parenthesis=33,rightParenthesis=34,// F6=35,
  four=36, five=37,  six=38,    multiplication=39,  division=40,        // G6=41,
  one=42,  two=43,   three=44,  plus=45,            minus=46,           // H6=47,
  zero=48, dot=49,   ee=50,     ans=51,             exe=52,             // I6=53,
  none = 54
} eadk_key;
uint64_t eadk_keyboard_scan();
uint64_t eadk_keyboard_pop_state();

// Timing
void eadk_timing_usleep(uint32_t us);
void eadk_timing_msleep(uint32_t ms);
uint64_t eadk_timing_millis();

// USB
bool eadk_timing_usb_is_plugged();

// Misc
uint32_t eadk_random();

#endif
