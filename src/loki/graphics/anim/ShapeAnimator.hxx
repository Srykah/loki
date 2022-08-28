#include <loki/core/math/Misc.hpp>
#include <loki/core/math/Vector2Ops.hpp>
#include <loki/graphics/anim/ShapeAnimator.hpp>

#include "ADLHelpers.hpp"
#include "TemplateHelpers.hpp"

namespace loki::gfx {

template <typename T>
ShapeAnimator<T>::ShapeAnimator(T& animated, const ShapeAnimationData& data)
    : animated(animated), data(data) {
  start();
}

template <typename T>
void ShapeAnimator<T>::start() {
  initValues.origin = getOrigin(animated);
  initValues.position = getPosition(animated);
  initValues.rotation = getRotation(animated);
  initValues.scale = getScale(animated);
  initValues.textureRect = getTextureRect(animated);
  initValues.color = getColor(animated);
  elapsedTime = sf::Time::Zero;
  isPaused = false;
}

template <typename T>
void ShapeAnimator<T>::pause() {
  isPaused = true;
}

template <typename T>
void ShapeAnimator<T>::unpause() {
  isPaused = false;
}

template <typename T>
bool ShapeAnimator<T>::hasEnded() const {
  return elapsedTime >= data.duration;
}

template <typename T>
void ShapeAnimator<T>::setTime(sf::Time time) {
  elapsedTime = time;
  updateInternal();
}

template <typename T>
void ShapeAnimator<T>::update(sf::Time delta) {
  if (isPaused)
    return;

  elapsedTime += delta;
  updateInternal();
}

template <typename T>
void ShapeAnimator<T>::updateInternal() {
  if (elapsedTime < sf::Time::Zero) {
    if (data.repeat) {
      elapsedTime = core::mod(elapsedTime, data.duration, sf::Time::Zero);
    } else {
      elapsedTime = sf::Time::Zero;
    }
  }
  if (elapsedTime >= data.duration) {
    if (data.repeat) {
      elapsedTime = core::mod(elapsedTime, data.duration, sf::Time::Zero);
    } else {
      elapsedTime = data.duration;
    }
  }
  setOrigin(animated,
            initValues.origin + interpolate(data.ipOrigin, elapsedTime));
  setPosition(animated,
              initValues.position + interpolate(data.ipPos, elapsedTime));
  setRotation(animated,
              initValues.rotation + interpolate(data.ipRot, elapsedTime));
  setScale(animated, initValues.scale + interpolate(data.ipScale, elapsedTime));
  setColor(animated,
           initValues.color * toColor(interpolate(data.ipColor, elapsedTime)));
  setTextureRect(animated,
                 toRect<int>(core::fromRect<float>(initValues.textureRect) +
                             interpolate(data.ipTexRect, elapsedTime)));
}

}  // namespace loki::gfx
