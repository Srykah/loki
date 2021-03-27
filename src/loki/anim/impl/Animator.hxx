/*!
 * \file Animator.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include "ADLHelpers.hpp"
#include "TemplateHelpers.hpp"

namespace loki::anim {

template <typename T>
Animator<T>::Animator(T& animated, const AnimationData& data)
: animated(animated)
, data(data) {
  if (common::is_detected_as_true<impl::has_setOrigin, T>
      && data.keyframes) {

  }
}

}
