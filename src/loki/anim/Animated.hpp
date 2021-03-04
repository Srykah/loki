/*!
 * \file Animated.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/System/Time.hpp>

namespace loki::anim {

class Animated {
 public:
  Animated() = default;
  Animated(sf::Time duration);
  virtual ~Animated() = default;

  void setDuration(sf::Time getDuration);
  [[nodiscard]] sf::Time getDuration() const;

  virtual void update(sf::Time delta);
  [[nodiscard]] sf::Time getElapsedTime() const;
  [[nodiscard]] float getProgression() const;

  [[nodiscard]] bool hasEnded() const;

 protected:
  void setElapsedTime(sf::Time elapsedTime);
  void setProgression(float progression);

 private:
  sf::Time duration, elapsedTime;
};

}
