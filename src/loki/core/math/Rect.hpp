#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <cmath>

namespace loki::core {

// component-wise

template <class T, class U, class Op>
auto compOp(const sf::Rect<T>& a, const sf::Rect<U>& b, const Op& op) {
  return sf::Rect{op(a.left, b.left), op(a.top, b.top), op(a.width, b.width),
                  op(a.height, b.height)};
}

template <class T, class U>
auto compMult(const sf::Rect<T>& a, const sf::Rect<U>& b) {
  return sf::Rect{a.left * b.left, a.top * b.top, a.width * b.width,
                  a.height * b.height};
}

template <class T, class U>
auto compDiv(const sf::Rect<T>& a, const sf::Rect<U>& b) {
  return sf::Rect{a.left / b.left, a.top / b.top, a.width / b.width,
                  a.height / b.height};
}

template <class T, class U>
auto compMin(const sf::Rect<T>& a, const sf::Rect<U>& b) {
  return sf::Rect{std::min(a.left, b.left), std::min(a.top, b.top),
                  std::min(a.width, b.width), std::min(a.height, b.height)};
}

template <class T, class U>
auto compMax(const sf::Rect<T>& a, const sf::Rect<U>& b) {
  return sf::Rect{std::max(a.left, b.left), std::max(a.top, b.top),
                  std::max(a.width, b.width), std::max(a.height, b.height)};
}

}  // namespace loki::core
