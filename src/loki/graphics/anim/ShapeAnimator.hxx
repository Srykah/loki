#include <loki/core/math/Misc.hpp>
#include <loki/core/math/Vector2Ops.hpp>
#include <loki/graphics/anim/ShapeAnimator.hpp>

#include "ADLHelpers.hpp"

namespace loki::graphics {

template <typename T>
void ShapeAnimator<T>::setAnimated(T& _animated) {
  resetAnimated();
  animated = &_animated;
}

template <typename T>
void ShapeAnimator<T>::resetAnimated() {
  stop();
  animated = nullptr;
  initValues = {};
}

template <typename T>
void ShapeAnimator<T>::setData(const ShapeAnimationData& _data) {
  resetData();
  data = &_data;
}

template <typename T>
void ShapeAnimator<T>::resetData() {
  stop();
  data = nullptr;
}

template <typename T>
void ShapeAnimator<T>::start() {
  initValues.origin = getOrigin(*animated);
  initValues.position = getPosition(*animated);
  initValues.rotation = getRotation(*animated);
  initValues.scale = getScale(*animated);
  initValues.color = getColor(*animated);
  elapsedTime = sf::Time::Zero;
  paused = false;
}

template <typename T>
void ShapeAnimator<T>::pause() {
  paused = true;
}

template <typename T>
void ShapeAnimator<T>::unpause() {
  paused = false;
}

template <typename T>
bool ShapeAnimator<T>::isPaused() const {
  return paused;
}

template <typename T>
void ShapeAnimator<T>::stop() {
  elapsedTime = sf::Time::Zero;
  paused = true;
}

template <typename T>
bool ShapeAnimator<T>::hasEnded() const {
  return elapsedTime >= data->duration;
}

template <typename T>
void ShapeAnimator<T>::setTime(sf::Time time) {
  elapsedTime = time;
  updateInternal();
}

template <typename T>
void ShapeAnimator<T>::update(sf::Time delta) {
  if (paused)
    return;

  elapsedTime += delta;
  updateInternal();
}

template <typename T>
void ShapeAnimator<T>::updateInternal() {
  if (elapsedTime < sf::Time::Zero) {
    if (data->repeat) {
      elapsedTime = core::mod(elapsedTime, data->duration, sf::Time::Zero);
    } else {
      elapsedTime = sf::Time::Zero;
    }
  }
  if (elapsedTime >= data->duration) {
    if (data->repeat) {
      elapsedTime = core::mod(elapsedTime, data->duration, sf::Time::Zero);
    } else {
      elapsedTime = data->duration;
    }
  }
  if (!data->ipOrigin.points.empty())
    setOrigin(*animated, initValues.origin + interpolate(data->ipOrigin, elapsedTime));
  if (!data->ipPos.points.empty())
    setPosition(*animated, initValues.position + interpolate(data->ipPos, elapsedTime));
  if (!data->ipRot.points.empty())
    setRotation(*animated, initValues.rotation + interpolate(data->ipRot, elapsedTime));
  if (!data->ipScale.points.empty())
    setScale(*animated, initValues.scale + interpolate(data->ipScale, elapsedTime));
  if (!data->ipColor.points.empty())
    setColor(*animated, initValues.color * toColor(interpolate(data->ipColor, elapsedTime)));
  if (!data->ipTexRect.points.empty())
    setTextureRect(*animated, core::toRect<int>(interpolate(data->ipTexRect, elapsedTime)));
}

}  // namespace loki::graphics
