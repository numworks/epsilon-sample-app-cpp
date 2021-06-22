#include "spaceship.h"
#include "palette.h"

Spaceship::Spaceship() :
  m_x(Display::Width/2),
  m_y(Display::Height - Display::CommonVerticalMargin),
  m_numberOfLives(k_maxNumberOfLives)
{

  draw(Yellow);
  for (int i = 0; i < k_maxNumberOfLives; i++) {
    m_lives[i].setIndex(i);
    m_lives[i].draw();
  }
}
void Spaceship::draw(const eadk_color color) const {
  int xMin = m_x - k_width/2;
  int xMax = xMin + k_width;
  int yMin = m_y - k_height/2;
  eadk_display_push_rect_uniform({.x = xMin + 11, .y = yMin + 10, .width = 13, .height = 11}, color);
  // Wings
  eadk_display_push_rect_uniform({.x = xMin, .y = yMin + 14, .width = k_width, .height = 2}, color);
  eadk_display_push_rect_uniform({.x = xMin + 3, .y = yMin + 17, .width = k_width - 6, .height = 2}, color);
  eadk_display_push_rect_uniform({.x = xMin + 2, .y = yMin + 8, .width = 1, .height = 6}, color);
  eadk_display_push_rect_uniform({.x = xMax - 3, .y = yMin + 8, .width = 1, .height = 6}, color);
  // Nose
  eadk_display_push_rect_uniform({.x = xMin + 15, .y = yMin + 6, .width = 5, .height = 4}, color);
  eadk_display_push_rect_uniform({.x = xMin + 16, .y = yMin + 4, .width = 3, .height = 2}, color);
  eadk_display_push_rect_uniform({.x = xMin + 17, .y = yMin, .width = 1, .height = 4}, color);
}

void Spaceship::move(int deltaX, int deltaY) {
  draw(Black);
  m_x += deltaX;
  m_y += deltaY;
  m_x = m_x <= k_xLowerBound ? k_xLowerBound : m_x;
  m_y = m_y <= k_yLowerBound ? k_yLowerBound : m_y;
  m_x = m_x >= k_xUpperBound ? k_xUpperBound : m_x;
  m_y = m_y >= k_yUpperBound ? k_yUpperBound : m_y;
  draw(Yellow);
}

bool Spaceship::hit() {
  m_lives[m_numberOfLives - 1].breaks();
  m_numberOfLives--;
  for (int i = 0; i < 5; i++) {
    draw(Red);
    eadk_timing_msleep(10);
    draw(Yellow);
    eadk_timing_msleep(10);
  }
  return m_numberOfLives == 0;
}

void Spaceship::createRockets() {
  int deltaX[] = {-15, 0, 14};
  for (int dx : deltaX) {
    int x = m_x + dx;
    int y = m_y - k_height;
    for (int i = 0; i < k_maxNumberOfRockets; i++) {
      if (m_rockets[i].x() == x && m_rockets[i].y() == y) {
        // A rocket has already been launched at this location
        continue;
      }
    }
    for (int i = 0; i < k_maxNumberOfRockets; i++) {
      if (m_rockets[i].off()) {
        m_rockets[i].setLocation(x, y);
        break;
      }
    }
  }
}
