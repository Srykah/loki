/*!
 * \file Animation.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimationViewData.hpp"

#include <SFML/Graphics/Transformable.hpp>

namespace {

template <typename T>
using IpPts = std::vector<std::pair<float, T>>;

template <typename T>
using NoneIp = loki::math::NoneInterpolation<float, T>;

template <typename T>
using LinIp = loki::math::LinearInterpolation<float, T>;

template <typename T>
using CubIp = loki::math::LinearInterpolation<float, T>;  // todo

template <class T>
std::shared_ptr<loki::math::InterpolationBase<float, T>> buildInterpolation(
    const IpPts<T>& points,
    loki::math::InterpolationType interpolationType) {
  switch (interpolationType) {
    case loki::math::InterpolationType::NONE:
      return std::make_shared<NoneIp<T>>(points);
    case loki::math::InterpolationType::LINEAR:
      return std::make_shared<LinIp<T>>(points);
    case loki::math::InterpolationType::CUBIC:
    default:
      return std::make_shared<CubIp<T>>(points);
  }
}

}  // namespace

namespace loki::anim {

AnimationViewData::AnimationViewData(const AnimationData& data)
    : duration(data.duration), repeat(data.repeat) {
  if (data.keyframes.size() >= 2) {
    auto end = data.keyframes.end();
    --end;
    const auto& [firstTime, firstKeyframe] = *data.keyframes.begin();
    const auto& [lastTime, lastKeyframe] = *end;

#define LOKI_ANIM_TEST_COMPONENT_TRF(comp, ipComp, COMP, trf, _firstValue) \
  {                                                                        \
    auto firstValue = _firstValue;                                         \
    IpPts<decltype(firstValue)> points;                                    \
    auto* last = &firstValue;                                              \
    for (const auto& [time, keyframe] : data.keyframes) {                  \
      if (keyframe.comp.has_value()) {                                     \
        points.emplace_back(time, trf(keyframe.comp.value()));             \
      } else {                                                             \
        points.emplace_back(time, *last);                                  \
      }                                                                    \
      last = &points.back().second;                                        \
    }                                                                      \
    ipComp = buildInterpolation(                                           \
        points, data.interpolationTypes.at(Keyframe::Component::COMP));    \
  }

#define LOKI_ANIM_TEST_COMPONENT(comp, ipComp, COMP, _firstValue) \
  LOKI_ANIM_TEST_COMPONENT_TRF(comp, ipComp, COMP, , _firstValue)

    LOKI_ANIM_TEST_COMPONENT(origin, ipOrigin, ORIGIN, sf::Vector2f{})
    LOKI_ANIM_TEST_COMPONENT(position, ipPos, POSITION, sf::Vector2f{})
    LOKI_ANIM_TEST_COMPONENT(rotation, ipRot, ROTATION, 0.f)
    LOKI_ANIM_TEST_COMPONENT(scale, ipScale, SCALE, sf::Vector2f(1.f, 1.f))
    LOKI_ANIM_TEST_COMPONENT_TRF(color, ipColor, COLOR, fromColor<float>,
                                 Vector4<float>(1.f, 1.f, 1.f, 1.f))
    LOKI_ANIM_TEST_COMPONENT_TRF(textureRect, ipTexRect, TEXTURE_RECT,
                                 fromRect<float>, Vector4<float>{})

#undef LOKI_ANIM_TEST_COMPONENT_TRF
#undef LOKI_ANIM_TEST_COMPONENT
  }
}

const sf::Time& AnimationViewData::getDuration() const {
  return duration;
}

bool AnimationViewData::isRepeated() const {
  return repeat;
}

sf::Vector2f AnimationViewData::getOrigin(sf::Time instant) const {
  if (ipOrigin) {
    return ipOrigin->interpolate(instant / duration);
  }
  return sf::Vector2f{};
}

sf::Vector2f AnimationViewData::getPosition(sf::Time instant) const {
  if (ipPos) {
    return ipPos->interpolate(instant / duration);
  }
  return sf::Vector2f{};
}

float AnimationViewData::getRotation(sf::Time instant) const {
  if (ipRot) {
    return ipRot->interpolate(instant / duration);
  }
  return 0;
}

sf::Vector2f AnimationViewData::getScale(sf::Time instant) const {
  if (ipScale) {
    return ipScale->interpolate(instant / duration);
  }
  return sf::Vector2f{1.f, 1.f};
}

sf::Transform AnimationViewData::getTransform(sf::Time instant) const {
  sf::Transformable tr;
  tr.setOrigin(getOrigin(instant));
  tr.setPosition(getPosition(instant));
  tr.setRotation(getRotation(instant));
  tr.setScale(getScale(instant));
  return tr.getTransform();
}

sf::Color AnimationViewData::getColor(sf::Time instant) const {
  if (ipColor) {
    return toColor(ipColor->interpolate(instant / duration));
  }
  return sf::Color::White;
}
sf::IntRect AnimationViewData::getTextureRect(sf::Time instant) const {
  if (ipTexRect) {
    return toRect<int>(ipTexRect->interpolate(instant / duration));
  }
  return sf::IntRect{};
}

}  // namespace loki::anim
