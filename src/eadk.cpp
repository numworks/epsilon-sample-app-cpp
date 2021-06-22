#include "eadk.h"

extern "C" {

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

// Keyboard
typedef uint64_t eadk_keyboard_state;
eadk_keyboard_state eadk_keyboard_scan();

// Timing
void eadk_timing_msleep(uint32_t ms);

// Misc
uint32_t eadk_random();

}

namespace EADK {

namespace Display {

void pushRect(Rect rect, const Color * pixels) {
  eadk_display_push_rect({rect.x(), rect.y(), rect.width(), rect.height()}, reinterpret_cast<const eadk_color *>(pixels));
}

void pushRectUniform(Rect rect, Color color) {
  eadk_display_push_rect_uniform({rect.x(), rect.y(), rect.width(), rect.height()}, color);
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

