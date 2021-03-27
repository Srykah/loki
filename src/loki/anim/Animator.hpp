/*!
 * \file Animator.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include "AnimationData.hpp"

namespace loki::anim {

template <typename T>
class Animator {
 public:
  Animator(T& animated, const AnimationData& data);

  void update(sf::Time delta);
  [[nodiscard]] bool hasEnded() const;
  void restart();

 private:
  T& animated;
  const AnimationData& data;
  Keyframe base;
  std::shared_ptr<common::InterpolationBase<float, sf::Vector2f>> ipOrigin;
  std::shared_ptr<common::InterpolationBase<float, sf::Vector2f>> ipPos;
  std::shared_ptr<common::InterpolationBase<float, float>> ipRot;
  std::shared_ptr<common::InterpolationBase<float, sf::Vector2f>> ipScale;
  std::shared_ptr<common::InterpolationBase<float, sf::Color>> ipColor;
  std::shared_ptr<common::InterpolationBase<float, sf::Vector2f>> ipTexRectPos;
  std::shared_ptr<common::InterpolationBase<float, sf::Vector2f>> ipTexRectSize;
  sf::Time elapsedTime;
};

}

#include "impl/Animator.hxx"
