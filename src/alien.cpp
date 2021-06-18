#include "alien.h"
#include "palette.h"
#include "stdlib.h"

Alien::Alien(int x) :
  m_x(x),
  m_y(2*Display::CommonVerticalMargin)
{
  if (!isGhost()) {
    draw(Orange);
  }
}

void Alien::hide() const {
  eadk_display_push_rect_uniform({.x = m_x + 2, .y = m_y - k_height/2, .width = k_width, .height = k_height}, Black);
}

void Alien::draw(const eadk_color c) const {
  int xMin = m_x - k_width/2;
  int xMax = xMin + k_width;
  int yMin = m_y - k_height/2;
  int yMax = yMin + k_height;
  eadk_display_push_rect_uniform({.x = xMin, .y = yMin, .width = k_width, .height = k_height - 4}, c);
  eadk_display_push_rect_uniform({.x = xMin + 3, .y =  yMax - 4, .width = 2, .height = 4}, c);
  eadk_display_push_rect_uniform({.x = xMax - 4 - 2, .y = yMax - 4, .width = 2, .height = 4}, c);
  eadk_display_push_rect_uniform({.x = xMin + 2, .y = yMin + 3, .width = 3, .height = 7}, Black);
  eadk_display_push_rect_uniform({.x = xMax - 2 - 3, .y = yMin + 3, .width = 3, .height = 7}, Black);
}

void Alien::step() {
  if (!isGhost()) {
    hide();
    m_y += k_step;
    if (m_y >= Display::Height) {
      ghostify();
    }
    if (!isGhost()) {
      draw(Orange);
    }
  }
}

bool Alien::hits(Spaceship * s) {
  if (isGhost()) {
   return false;
  }
  if (abs(m_x - s->x()) < Spaceship::k_width/2 + k_width/2 &&
      abs(m_y - s->y()) < Spaceship::k_height/2 + k_height/2) {
    hide();
    ghostify();
    return s->hit();
  }
  return false;
}

void Alien::killed() {
  if (isGhost()) {
    return;
  }
  for (int i = 0; i < 5; i++) {
    draw(Green);
    eadk_timing_msleep(10);
    draw(Orange);
    eadk_timing_msleep(10);
  }
  hide();
  ghostify();
}
