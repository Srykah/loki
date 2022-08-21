#pragma once

namespace loki::core {

template <class T>
T mod(const T& x, const T& q, const T& zero = T{0}) {
  auto rem = x % q;
  if ((rem < zero) != (q < zero))
    rem += q;
  return rem;
}

}  // namespace loki::core