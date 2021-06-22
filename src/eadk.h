#ifndef EADK_H
#define EADK_H

#include <stdint.h>

namespace EADK {

namespace Display {

class Color {
public:
  constexpr Color(uint32_t rgb) : m_value(((rgb&0xF80000)>>8)|((rgb&0x00FC00)>>5)|((rgb&0x0000F8)>>3)) {}
  operator uint16_t() const { return m_value; }
private:
  uint16_t m_value;
};

class Rect {
public:
  constexpr Rect(int x, int y, int width, int height) :
    m_x(x), m_y(y), m_width(width), m_height(height) {}
  uint16_t x() const { return m_x; }
  uint16_t y() const { return m_y; }
  uint16_t width() const { return m_width; }
  uint16_t height() const { return m_height; }
private:
  uint16_t m_x;
  uint16_t m_y;
  uint16_t m_width;
  uint16_t m_height;
};

void pushRect(Rect rect, const Color * pixels);
void pushRectUniform(Rect rect, Color color);

}

namespace Keyboard {

enum class Key : uint8_t {
  Left=0,  Up=1,     Down=2,    Right=3,           OK=4,              Back=5,
  Home=6,  /*B2=7,*/ OnOff=8,   /*B4=9,            B5=10,             B6=11, */
  Shift=12,Alpha=13, XNT=14,    Var=15,            Toolbox=16,        Backspace=17,
  Exp=18,  Ln=19,    Log=20,    Imaginary=21,      Comma=22,          Power=23,
  Sine=24, Cosine=25,Tangent=26,Pi=27,             Sqrt=28,           Square=29,
  Seven=30,Eight=31, Nine=32,   LeftParenthesis=33,RightParenthesis=34,// F6=35,
  Four=36, Five=37,  Six=38,    Multiplication=39, Division=40,        // G6=41,
  One=42,  Two=43,   Three=44,  Plus=45,           Minus=46,           // H6=47,
  Zero=48, Dot=49,   EE=50,     Ans=51,            EXE=52,             // I6=53,
  None = 54
};

class State {
public:
  constexpr State(uint64_t s = 0) :
    m_bitField(s)
  {}
  inline bool keyDown(Key k) const {
    return (m_bitField>>(uint8_t)k) & 1;
  }
  operator uint64_t() const { return m_bitField; }
private:
  uint64_t m_bitField;
};

State scan();

}

namespace Timing {

void msleep(uint32_t ms);

}

uint32_t random();

}

#endif