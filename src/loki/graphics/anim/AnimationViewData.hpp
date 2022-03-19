/*!
 * \file Animation.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <loki/core/utils/Vector4.hpp>
#include "AnimationData.hpp"

namespace loki::anim {

class AnimationViewData {
 public:
  explicit AnimationViewData(const AnimationData& data);

  [[nodiscard]] const sf::Time& getDuration() const;
  [[nodiscard]] bool isRepeated() const;

  [[nodiscard]] sf::Vector2f getOrigin(sf::Time instant) const;
  [[nodiscard]] sf::Vector2f getPosition(sf::Time instant) const;
  [[nodiscard]] float getRotation(sf::Time instant) const;
  [[nodiscard]] sf::Vector2f getScale(sf::Time instant) const;
  [[nodiscard]] sf::Transform getTransform(sf::Time instant) const;
  [[nodiscard]] sf::Color getColor(sf::Time instant) const;
  [[nodiscard]] sf::IntRect getTextureRect(sf::Time instant) const;

 private:
  const sf::Time duration;
  const bool repeat;
  std::shared_ptr<math::InterpolationBase<float, sf::Vector2f>> ipOrigin;
  std::shared_ptr<math::InterpolationBase<float, sf::Vector2f>> ipPos;
  std::shared_ptr<math::InterpolationBase<float, float>> ipRot;
  std::shared_ptr<math::InterpolationBase<float, sf::Vector2f>> ipScale;
  std::shared_ptr<math::InterpolationBase<float, Vector4f>> ipColor;
  std::shared_ptr<math::InterpolationBase<float, Vector4f>> ipTexRect;
};

}  // namespace loki::anim
