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
  Animated(sf::Time duration, bool isRepeated = false);
  virtual ~Animated() = default;

  void setDuration(sf::Time getDuration);
  [[nodiscard]] sf::Time getDuration() const;
  [[nodiscard]] bool hasEnded() const;

  void restart();
  virtual void update(sf::Time delta) final;
  [[nodiscard]] sf::Time getElapsedTime() const;
  [[nodiscard]] float getProgression() const;

  void setRepeated(bool repeated);
  [[nodiscard]] bool isRepeated() const;

  void pause();
  void unpause();
  [[nodiscard]] bool isPaused() const;

 private:
  virtual void updateImpl() = 0;

 private:
  sf::Time duration, elapsedTime;
  bool repeated = false;
  bool paused = false;
};

}
