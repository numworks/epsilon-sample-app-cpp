#include "alien.h"
#include "display.h"
#include "palette.h"
#include "spaceship.h"
extern "C" {
#include "../eadk/eadk.h"
}
extern "C" void eadk_main();
extern "C" const char eadk_app_name[] = "Voord";

//__attribute((used)) eadk_app_name;
void checkForSpaceshipAlienCollisions(Alien aliens[], int numberOfAliens, Spaceship * spaceship) {
  for (int i = 0; i < numberOfAliens; i++) {
    if (aliens[i].hits(spaceship)) {
      eadk_display_push_rect_uniform({.x = 0, .y = 0, .width = Display::Width, .height = Display::Height}, Red);
      while (1) {}
    }
  }
}

void checkForRocketsAliensCollisions(Spaceship * spaceship, Alien aliens[], int numberOfAliens) {
  for (int i = 0; i < spaceship->numberOfRockets(); i++) {
    for (int j = 0; j < numberOfAliens; j++) {
      spaceship->rocketAtIndex(i)->tryToKill(&aliens[j]);
    }
  }
}

uint64_t stateWithKeyDown(eadk_key k) { return (uint64_t)1 << k; }

void eadk_main() {
  eadk_display_push_rect_uniform({.x = 0, .y = 0, .width = Display::Width, .height = Display::Height}, Black);

  constexpr int k_maxNumberOfAliens = 10;
  Alien aliens[k_maxNumberOfAliens];

  Spaceship spaceship;

  int rocketTimer = 0;
  int alienStepTimer = 0;
  int alienMaterializationTimer = 0;
  while (1) {
    eadk_keyboard_state keyboardState = eadk_keyboard_scan();
    if (keyboardState & stateWithKeyDown(eadk_key::OK)) {
      spaceship.createRockets();
    }
    if (keyboardState & stateWithKeyDown(eadk_key::UP)) {
      spaceship.move(0, -Spaceship::k_step);
    }
    if (keyboardState & stateWithKeyDown(eadk_key::DOWN)) {
      spaceship.move(0, Spaceship::k_step);
    }
    if (keyboardState & stateWithKeyDown(eadk_key::LEFT)) {
      spaceship.move(-Spaceship::k_step, 0);
    }
    if (keyboardState & stateWithKeyDown(eadk_key::RIGHT)) {
      spaceship.move(Spaceship::k_step, 0);
    }

    checkForSpaceshipAlienCollisions(aliens, k_maxNumberOfAliens, &spaceship);

    if (rocketTimer == Rocket::k_period) {
      rocketTimer = 0;
      for (int i = 0; i < spaceship.numberOfRockets(); i++) {
        spaceship.rocketAtIndex(i)->forward();
      }
      checkForRocketsAliensCollisions(&spaceship, aliens, k_maxNumberOfAliens);
    }
    if (alienStepTimer == Alien::k_stepPeriod) {
      alienStepTimer = 0;
      for (int i = 0; i < k_maxNumberOfAliens; i++) {
        aliens[i].step();
      }
      checkForSpaceshipAlienCollisions(aliens, k_maxNumberOfAliens, &spaceship);
      checkForRocketsAliensCollisions(&spaceship, aliens, k_maxNumberOfAliens);
    }

    eadk_timing_msleep(20);

    // New alien
    if (alienMaterializationTimer == Alien::k_materializationPeriod) {
      alienMaterializationTimer = 0;
      for (int i = 0; i < k_maxNumberOfAliens; i++) {
        if (aliens[i].isGhost()) {
          aliens[i] = Alien(Display::CommonHorizontalMargin + (float)eadk_random()/(float)0xFFFFFFFF * (Display::Width - 2*Display::CommonHorizontalMargin));
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
