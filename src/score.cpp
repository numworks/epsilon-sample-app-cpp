#include "score.h"
#include "life.h"
#include "palette.h"

void Score::draw() const {
  char buffer[k_maximalScoreNumberOfDigits + 1];
  char * c = buffer + k_maximalScoreNumberOfDigits;
  *c = 0;
  int score = m_value;
  while (c > buffer) {
    c--;
    *c = '0' + score % 10;
    score /= 10;
  }
  EADK::Display::drawString(buffer, EADK::Display::Point(Display::Width - 10 * k_maximalScoreNumberOfDigits - Display::CommonHorizontalMargin, 2 * Display::CommonVerticalMargin + Life::k_height), true, White, Black);
}

void Score::increment() {
  m_value++;
  if (m_value == k_maximalScore) {
    EADK::Display::pushRectUniform(EADK::Display::Rect(0, 0, Display::Width, Display::Height), Yellow);
    EADK::Display::drawString("Well done", EADK::Display::Point((Display::Width - 9 * 10) / 2, (Display::Height - 18) / 2), true, Black, Yellow);
    while(1) {}
  }
}
