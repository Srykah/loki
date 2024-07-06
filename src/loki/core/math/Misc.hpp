#pragma once

#include <numbers>

namespace loki::core {

template <class T>
T mod(const T& x, const T& q, const T& zero = T{0}) {
  auto rem = x % q;
  if ((rem < zero) != (q < zero))
    rem += q;
  return rem;
}

constexpr float toRadians(float degrees) {
  return degrees / 180.f * std::numbers::pi;
}

constexpr float toDegrees(float radians) {
  return radians * 180.f * std::numbers::inv_pi;
}

}  // namespace loki::core