/*!
 * \file Animator.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include "AnimationViewData.hpp"

namespace loki::anim {

template <typename T>
class Animator {
 public:
  Animator(T& animated, const AnimationViewData& viewData);

  void start();
  void update(sf::Time delta);
  [[nodiscard]] bool hasEnded() const;
  void pause();
  void unpause();

 private:
  T& animated;
  const AnimationViewData& viewData;
  Keyframe baseKeyframe;
  sf::Time elapsedTime;
  bool isPaused = false;
};

}

#include "impl/Animator.hxx"
