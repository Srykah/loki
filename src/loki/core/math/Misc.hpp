/*!
 * \file Misc.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::math {

template <class T>
T mod(const T& x, const T& q, const T& zero = T{0}) {
  auto rem = x % q;
  if ((rem < zero) != (q < zero))
    rem += q;
  return rem;
}

}  // namespace loki::math