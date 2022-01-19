#include "alien.h"
#include "display.h"
#include "eadk.h"
#include "palette.h"
#include "spaceship.h"

extern "C" const char eadk_app_name[] = "Voord";

void checkForSpaceshipAlienCollisions(Alien aliens[], int numberOfAliens, Spaceship * spaceship) {
  for (int i = 0; i < numberOfAliens; i++) {
    if (aliens[i].tryToHit(spaceship)) {
      EADK::Display::pushRectUniform(EADK::Display::Rect(0, 0, Display::Width, Display::Height), Red);
      while (1) {}
    }
  }
}

void eadk_main() {
  EADK::Display::pushRectUniform(EADK::Display::Rect(0, 0, Display::Width, Display::Height), Black);

  constexpr int k_maxNumberOfAliens = 10;
  Alien aliens[k_maxNumberOfAliens];

  Spaceship spaceship;

  int rocketTimer = 0;
  int alienStepTimer = 0;
  int alienMaterializationTimer = 0;
  while (1) {
    EADK::Keyboard::State keyboardState = EADK::Keyboard::scan();
    if (keyboardState.keyDown(EADK::Keyboard::Key::OK)) {
      spaceship.createRockets();
    }
    if (keyboardState.keyDown(EADK::Keyboard::Key::Up)) {
      spaceship.move(0, -Spaceship::k_step);
    }
    if (keyboardState.keyDown(EADK::Keyboard::Key::Down)) {
      spaceship.move(0, Spaceship::k_step);
    }
    if (keyboardState.keyDown(EADK::Keyboard::Key::Left)) {
      spaceship.move(-Spaceship::k_step, 0);
    }
    if (keyboardState.keyDown(EADK::Keyboard::Key::Right)) {
      spaceship.move(Spaceship::k_step, 0);
    }

    checkForSpaceshipAlienCollisions(aliens, k_maxNumberOfAliens, &spaceship);

    // Rockets move forward and potentially collide
    if (rocketTimer == Rocket::k_period) {
      rocketTimer = 0;
      spaceship.rocketsAction(aliens, k_maxNumberOfAliens);
    }

    // Aliens move forward and potentially collide with rockets or spaceship
    if (alienStepTimer == Alien::k_stepPeriod) {
      alienStepTimer = 0;
      for (int i = 0; i < k_maxNumberOfAliens; i++) {
        aliens[i].step();
      }
      checkForSpaceshipAlienCollisions(aliens, k_maxNumberOfAliens, &spaceship);
      spaceship.checkForRocketsAliensCollisions(aliens, k_maxNumberOfAliens);
    }

    EADK::Timing::msleep(20);

    // New alien
    if (alienMaterializationTimer == Alien::k_materializationPeriod) {
      alienMaterializationTimer = 0;
      for (int i = 0; i < k_maxNumberOfAliens; i++) {
        if (aliens[i].isGhost()) {
          aliens[i] = Alien(Display::CommonHorizontalMargin + (float)EADK::random()/(float)0xFFFFFFFF * (Display::Width - 2*Display::CommonHorizontalMargin));
          break;
        }
      }
    }

    // Increment timers
    rocketTimer++;
    alienStepTimer++;
    alienMaterializationTimer++;
  }
}
