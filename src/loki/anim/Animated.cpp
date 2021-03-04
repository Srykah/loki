/*!
 * \file Animated.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Animated.hpp"
#include <algorithm>

namespace loki::anim {

Animated::Animated(sf::Time duration) : duration(duration) {}

void Animated::setDuration(sf::Time _duration) {
  duration = _duration;
}

sf::Time Animated::getDuration() const {
  return duration;
}

bool Animated::hasEnded() const {
  return elapsedTime >= duration;
}

void Animated::update(sf::Time delta) {
  if (!hasEnded()) {
    elapsedTime += delta;
  }
}

sf::Time Animated::getElapsedTime() const {
  return elapsedTime;
}

float Animated::getProgression() const {
  return elapsedTime / duration;
}

void Animated::setElapsedTime(sf::Time _elapsedTime) {
  elapsedTime = std::clamp(_elapsedTime, sf::Time::Zero, duration);
}

void Animated::setProgression(float progression) {
  elapsedTime = std::clamp(progression * duration, sf::Time::Zero, duration);
}

}
