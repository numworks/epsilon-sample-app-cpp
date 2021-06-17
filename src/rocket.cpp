#include "rocket.h"
#include "alien.h"
#include "palette.h"
#include "../eadk/eadk.h"
#include "stdlib.h"

void Rocket::setLocation(int x, int y) {
  m_x = x;
  m_y = y;
  draw(LightBlue);
}

void Rocket::draw(const eadk_color c) const {
  if (off()) {
    return;
  }
  eadk_display_push_rect_uniform({.x = m_x, .y = m_y - k_length/2, .width = 1, .height = 8}, c);
  eadk_display_push_rect_uniform({.x = m_x, .y = m_y - k_length/2 + 8 + 1, .width = 1, .height = 2}, c);
  eadk_display_push_rect_uniform({.x = m_x, .y = m_y + k_length/2, .width = 1, .height = 1}, c);
}

void Rocket::forward() {
  draw(Black);
  if (!off()) {
    m_y -= k_length;
  }
  draw(LightBlue);
}

void Rocket::tryToKill(Alien * a) {
  if (off() || a->isGhost()) {
    return;
  }
  if (abs(m_x - a->x()) < Alien::k_width/2 &&
      abs(m_y - a->y()) < Alien::k_height/2 + k_length/2) {
    a->killed();
    draw(Black);
    switchOff();
  }
}
