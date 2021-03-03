/*!
 * \file Animated.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Animated.hpp"

namespace loki::anim {

Animated::Animated(sf::Time duration, bool isRepeated) : duration(duration), repeated(isRepeated) {}

void Animated::setDuration(sf::Time _duration) {
  duration = _duration;
}

sf::Time Animated::getDuration() const {
  return duration;
}

bool Animated::hasEnded() const {
  return paused && elapsedTime == duration;
}

void Animated::restart() {
  elapsedTime = sf::Time::Zero;
}

void Animated::update(sf::Time delta) {
  if (!paused) {
    elapsedTime += delta;
    if (elapsedTime > duration) {
      auto overtime = elapsedTime - duration;
      elapsedTime = duration;
      updateImpl();
      if (repeated) {
        restart();
        elapsedTime = overtime;
        updateImpl();
      } else {
        pause();
      }
    }
  }
}

sf::Time Animated::getElapsedTime() const {
  return elapsedTime;
}

float Animated::getProgression() const {
  return elapsedTime / duration;
}

void Animated::setRepeated(bool _repeated) {
  repeated = _repeated;
}

bool Animated::isRepeated() const {
  return repeated;
}

void Animated::pause() {
  paused = true;
}

void Animated::unpause() {
  paused = false;
}

bool Animated::isPaused() const {
  return paused;
}

}
