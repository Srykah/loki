/*!
 * \file Animator.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include "ShapeAnimationData.hpp"

namespace loki::anim {

template <typename T>
class ShapeAnimator {
 public:
  ShapeAnimator(T& animated, const ShapeAnimationData& data);

  void start();
  void setTime(sf::Time time);
  void update(sf::Time delta);
  [[nodiscard]] bool hasEnded() const;
  void pause();
  void unpause();

 private:
  void updateInternal();

  struct ShapeInitValues {
    sf::Vector2f origin;
    sf::Vector2f position;
    float rotation = 0.f;
    sf::Vector2f scale;
    sf::Color color;
    sf::IntRect textureRect;
  };

  T& animated;
  const ShapeAnimationData& data;
  ShapeInitValues initValues;
  sf::Time elapsedTime;
  bool isPaused = false;
};

}  // namespace loki::anim

#include "ShapeAnimator.hxx"
