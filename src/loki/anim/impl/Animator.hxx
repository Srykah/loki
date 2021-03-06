/*!
 * \file Animator.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include <loki/anim/Animator.hpp>

#include "ADLHelpers.hpp"
#include "TemplateHelpers.hpp"

namespace loki::anim {

namespace impl {

sf::Vector2f compMult(const sf::Vector2f& a, const sf::Vector2f& b) {
  return sf::Vector2f{a.x * b.x, a.y * b.y};
}

}  // namespace impl

template <typename T>
Animator<T>::Animator(T& animated, const AnimationViewData& viewData)
    : animated(animated), viewData(viewData) {
  start();
}

template <typename T>
void Animator<T>::start() {
  baseKeyframe.origin = getOrigin(animated);
  baseKeyframe.position = getPosition(animated);
  baseKeyframe.rotation = getRotation(animated);
  baseKeyframe.scale = getScale(animated);
  baseKeyframe.color = getColor(animated);
  isPaused = false;
}

template <typename T>
void Animator<T>::pause() {
  isPaused = true;
}

template <typename T>
void Animator<T>::unpause() {
  isPaused = false;
}

template <typename T>
bool Animator<T>::hasEnded() const {
  return elapsedTime >= viewData.getDuration();
}

template <typename T>
void Animator<T>::update(sf::Time delta) {
  if (!isPaused) {
    elapsedTime += delta;
    if (elapsedTime >= viewData.getDuration()) {
      if (viewData.isRepeated()) {
        elapsedTime %= viewData.getDuration();
      } else {
        elapsedTime = viewData.getDuration();
      }
    }
    setOrigin(animated, viewData.getOrigin(elapsedTime) + *baseKeyframe.origin);
    setPosition(animated,
                viewData.getPosition(elapsedTime) + *baseKeyframe.position);
    setRotation(animated,
                viewData.getRotation(elapsedTime) + *baseKeyframe.rotation);
    setScale(animated, impl::compMult(viewData.getScale(elapsedTime),
                                      *baseKeyframe.scale));
    setColor(animated, viewData.getColor(elapsedTime) * *baseKeyframe.color);
    setTextureRect(animated, viewData.getTextureRect(elapsedTime));
  }
}

}  // namespace loki::anim
