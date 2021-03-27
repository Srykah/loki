/*!
 * \file Animation.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Animation.hpp"

#include <SFML/Graphics/Transformable.hpp>

namespace {

template <typename T>
using IpPts = std::vector<std::pair<float, T>>;

template <typename T>
using NoneIp = loki::common::NoneInterpolation<float, T>;

template <typename T>
using LinIp = loki::common::LinearInterpolation<float, T>;

template <typename T>
using CubIp = loki::common::LinearInterpolation<float, T>; // todo

}

namespace loki::anim {

Animation::Animation(const AnimationData& data)
: duration(data.duration) {
  if (data.keyframes.size() >= 2) {
    auto end = data.keyframes.end();
    --end;
    const auto& [firstTime, firstKeyframe] = *data.keyframes.begin();
    const auto& [lastTime, lastKeyframe] = *end;

#define TEST_ANIMATED_FEATURE(feature, ip, Type, def) \
    if (firstKeyframe.feature.has_value() && lastKeyframe.feature.has_value()) { \
      IpPts<Type> points; \
      for (const auto& [time, keyframe] : data.keyframes) { \
        points.emplace_back(time, keyframe.feature.value_or(def)); \
      } \
      if (data.interpolation == common::InterpolationType::NONE) { \
        ip = std::make_shared<NoneIp<Type>>(points); \
      } else if (data.interpolation == common::InterpolationType::LINEAR) { \
        ip = std::make_shared<LinIp<Type>>(points); \
      } else if (data.interpolation == common::InterpolationType::CUBIC) { \
        ip = std::make_shared<CubIp<Type>>(points); \
      } \
    }

    TEST_ANIMATED_FEATURE(origin, ipOrigin, sf::Vector2f, sf::Vector2f {})
    TEST_ANIMATED_FEATURE(position, ipPos, sf::Vector2f, sf::Vector2f {})
    TEST_ANIMATED_FEATURE(rotation, ipRot, float, 0.f)
    TEST_ANIMATED_FEATURE(scale, ipScale, sf::Vector2f, sf::Vector2f(1.f, 1.f))
    
#undef TEST_ANIMATED_FEATURE
    
    if (firstKeyframe.color.has_value() && lastKeyframe.color.has_value()) {
      IpPts<common::Vector4f> points;
      for (const auto& [time, keyframe] : data.keyframes) {
        points.emplace_back(time, common::fromColor<float>(keyframe.color.value_or(
                                      sf::Color::White)));
      }
      if (data.interpolation == common::InterpolationType::NONE) {
        ipColor = std::make_shared<NoneIp<common::Vector4f>>(points);
      } else if (data.interpolation == common::InterpolationType::LINEAR) {
        ipColor = std::make_shared<LinIp<common::Vector4f>>(points);
      } else if (data.interpolation == common::InterpolationType::CUBIC) {
        ipColor = std::make_shared<CubIp<common::Vector4f>>(points);
      }
    }
    
    if (firstKeyframe.textureRect.has_value() && lastKeyframe.textureRect.has_value()) {
      IpPts<common::Vector4f> points;
      for (const auto& [time, keyframe] : data.keyframes) {
        points.emplace_back(time, common::fromRect<float>(keyframe.textureRect.value_or(sf::IntRect {})));
      }
      if (data.interpolation == common::InterpolationType::NONE) {
        ipTexRect = std::make_shared<NoneIp<common::Vector4f>>(points);
      } else if (data.interpolation == common::InterpolationType::LINEAR) {
        ipTexRect = std::make_shared<LinIp<common::Vector4f>>(points);
      } else if (data.interpolation == common::InterpolationType::CUBIC) {
        ipTexRect = std::make_shared<CubIp<common::Vector4f>>(points);
      }
    }

  }
}

const sf::Time& Animation::getDuration() const {
  return duration;
}

sf::Vector2f Animation::getOrigin(sf::Time instant) const {
  if (ipOrigin) {
    return ipOrigin->interpolate(instant / duration);
  }
  return sf::Vector2f {};
}

sf::Vector2f Animation::getPosition(sf::Time instant) const {
  if (ipPos) {
    return ipPos->interpolate(instant / duration);
  }
  return sf::Vector2f {};
}

float Animation::getRotation(sf::Time instant) const {
  if (ipRot) {
    return ipRot->interpolate(instant / duration);
  }
  return 0;
}

sf::Vector2f Animation::getScale(sf::Time instant) const {
  if (ipScale) {
    return ipScale->interpolate(instant / duration);
  }
  return sf::Vector2f {1.f, 1.f};
}

sf::Transform Animation::getTransform(sf::Time instant) const {
  sf::Transformable tr;
  tr.setOrigin(getOrigin(instant));
  tr.setPosition(getPosition(instant));
  tr.setRotation(getRotation(instant));
  tr.setScale(getScale(instant));
  return tr.getTransform();
}

sf::Color Animation::getColor(sf::Time instant) const {
  if (ipColor) {
    return common::toColor(ipColor->interpolate(instant / duration));
  }
  return sf::Color::White;
}

sf::IntRect Animation::getTextureRect(sf::Time instant) const {
  if (ipTexRect) {
    return common::toRect<int>(ipTexRect->interpolate(instant / duration));
  }
  return sf::IntRect {};
}

}
