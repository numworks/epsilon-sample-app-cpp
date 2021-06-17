#ifndef ALIEN_H
#define ALIEN_H

#include "../eadk/eadk.h"
#include "spaceship.h"

class Alien {
public:
  Alien(uint16_t x = -1);
  uint16_t x() const { return m_x; }
  uint16_t y() const { return m_y; }
  void step();
  bool hits(Spaceship * s);
  bool isGhost() const { return m_x == -1; }
  void killed();
  static constexpr int k_stepPeriod = 10;
  static constexpr int k_materializationPeriod = 20;
  static constexpr uint16_t k_width = 15;
  static constexpr uint16_t k_height = 18;
private:
  void draw(const eadk_color c) const;
  void hide() const;
  void ghostify() { m_x = -1; }
  static constexpr uint16_t k_step = 10;
  uint16_t m_x;
  uint16_t m_y;
};

#endif
