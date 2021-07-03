#include "eadk.h"

static_assert(sizeof(EADK::Display::Color) == 2, "EADK::Display::Color should be 2 bytes long");
static_assert(sizeof(EADK::Display::Rect) == 8, "EADK::Display::Rect should be 4*2 bytes long");
static_assert(sizeof(EADK::Keyboard::State) == 8, "EADK::Display::State should be 64 bits long");

extern "C" {

// Display
void eadk_display_push_rect(EADK::Display::Rect rect, const EADK::Display::Color * pixels);
void eadk_display_push_rect_uniform(EADK::Display::Rect rect, EADK::Display::Color color);

// Keyboard
EADK::Keyboard::State eadk_keyboard_scan();

// Timing
void eadk_timing_msleep(uint32_t ms);

// Misc
uint32_t eadk_random();

}

namespace EADK {

namespace Display {

void pushRect(Rect rect, const Color * pixels) {
  eadk_display_push_rect(rect, pixels);
}

void pushRectUniform(Rect rect, Color color) {
  eadk_display_push_rect_uniform(rect, color);
}

}

namespace Keyboard {

State scan() {
  return eadk_keyboard_scan();
}

}

namespace Timing {

void msleep(uint32_t ms) {
  return eadk_timing_msleep(ms);
}

}

uint32_t random() {
  return eadk_random();
}

}

