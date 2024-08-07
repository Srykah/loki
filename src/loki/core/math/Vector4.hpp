#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <loki/core/reflection/classMacros.hpp>

namespace loki::core {

template <typename T>
struct Vector4 {
  T a = T{}, b = T{}, c = T{}, d = T{};

  Vector4() = default;
  template <typename A, typename B, typename C, typename D>
  Vector4(A&& a, B&& b, C&& c, D&& d);
  template <typename U>
  explicit Vector4(const Vector4<U>& v);

  [[nodiscard]] Vector4<T> operator-() const;
  Vector4<T>& operator+=(const Vector4<T>& v);
  Vector4<T>& operator-=(const Vector4<T>& v);
  [[nodiscard]] Vector4<T> operator+(const Vector4<T>& v) const;
  [[nodiscard]] Vector4<T> operator-(const Vector4<T>& v) const;
  Vector4<T>& operator*=(const T& t);
  Vector4<T>& operator/=(const T& t);
  [[nodiscard]] Vector4<T> operator*(const T& t) const;
  [[nodiscard]] Vector4<T> operator/(const T& t) const;
  [[nodiscard]] bool operator==(const Vector4<T>& v) const;
  [[nodiscard]] bool operator!=(const Vector4<T>& v) const;

  LOKI_REFLECTION_CLASS_DECLARE(Vector4)
};

template <typename T>
Vector4<T> operator*(const T& t, const Vector4<T>& v);

template <typename T, typename U>
Vector4<T> fromRect(const sf::Rect<U>& rect);
template <typename U, typename T>
sf::Rect<U> toRect(const Vector4<T>& v);

template <typename T>
Vector4<T> fromColor(const sf::Color& color);
template <typename T>
sf::Color toColor(const Vector4<T>& v);

using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;

}  // namespace loki::core

LOKI_REFLECTION_TEMPLATE_CLASS_BEGIN(loki::core::Vector4)
LOKI_REFLECTION_CLASS_FIELD(a)
LOKI_REFLECTION_CLASS_FIELD(b)
LOKI_REFLECTION_CLASS_FIELD(c)
LOKI_REFLECTION_CLASS_FIELD(d)
LOKI_REFLECTION_CLASS_END()

#include "Vector4.hxx"
