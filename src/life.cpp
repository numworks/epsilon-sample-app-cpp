#include "life.h"
#include "palette.h"

void Life::setIndex(int index) {
  m_x = Display::Width - (index + 1) * Display::CommonHorizontalMargin;
}

constexpr eadk_color k_heart[Life::k_height*Life::k_width] = {
 rgb24(0x000000), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0x000000),
 rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0x000000), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81),
 rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81),
 rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81),
 rgb24(0x000000), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0x000000),
 rgb24(0x000000), rgb24(0x000000), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0x000000), rgb24(0x000000),
 rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000),
 rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0xFC7F81), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000),
 rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0xFC7F81), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000), rgb24(0x000000)
};

void Life::draw() const {
  if (m_broken) {
    eadk_display_push_rect_uniform({.x = m_x - k_width/2, .y = m_y - k_height/2, .width = k_width, .height = k_height}, Black);
  } else {
    eadk_display_push_rect({.x = m_x - k_width/2, .y = m_y - k_height/2, .width = k_width, .height = k_height}, k_heart);
  }
}

void Life::breaks() {
  m_broken = true;
  draw();
}
