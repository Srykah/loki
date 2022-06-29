/*!
 * \file Wrappers.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#if 0

#include <utility>

namespace loki {
inline namespace utils {

template <class T>
class ReassignableConst {
 public:
  template <class... Args>
  explicit Protected(Args&&... args) : value(std::forward<Args>(args)...) {}
  explicit Protected(const T& other) : value(other) {}
  explicit Protected(T&& other) : value(std::move(other)) {}
  Protected& operator=(const T& other) {
    value = other;
    return *this;
  }
  Protected& operator=(T&& other) {
    value = std::move(other);
    return *this;
  }

  const T& operator T() const { return value; }
  const T& get() const { return value; }

 private:
  T value;
};

}  // namespace utils
}  // namespace loki

#endif
