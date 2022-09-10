#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

namespace loki::core {

// linalg

template <class T, class U>
auto dot(const sf::Vector2<T>& a, const sf::Vector2<U>& b) {
  return a.x * b.x + a.y * b.y;
}

template <class T>
T norm(const sf::Vector2<T>& a) {
  return std::sqrt(dot(a, a));
}

template <class T, class U>
auto det(const sf::Vector2<T>& a, const sf::Vector2<U>& b) {
  return a.x * b.y - a.y * b.x;
}

template <class T>
sf::Vector2<T> unit(const sf::Vector2<T>& a) {
  return a / norm(a);
}

// component-wise

template <class T, class U, class Op>
auto compOp(const sf::Vector2<T>& a, const sf::Vector2<U>& b, const Op& op) {
  return sf::Vector2{op(a.x, b.x), op(a.y, b.y)};
}

template <class T, class U>
auto compMult(const sf::Vector2<T>& a, const sf::Vector2<U>& b) {
  return sf::Vector2{a.x * b.x, a.y * b.y};
}

template <class T, class U>
auto compDiv(const sf::Vector2<T>& a, const sf::Vector2<U>& b) {
  return sf::Vector2{a.x / b.x, a.y / b.y};
}

template <class T, class U>
auto compMin(const sf::Vector2<T>& a, const sf::Vector2<U>& b) {
  return sf::Vector2{std::min(a.x, b.x), std::min(a.y, b.y)};
}

template <class T, class U>
auto compMax(const sf::Vector2<T>& a, const sf::Vector2<U>& b) {
  return sf::Vector2{std::max(a.x, b.x), std::max(a.y, b.y)};
}

// transforms

// note : rotations are here named according to the "classic" coordinate system,
// with x towards the right and y towards the top.
// This is coherent with the order of the Shapes's vertices :
// They appear clockwise on the screen, which has an inverted y axis.
// ... Yeah that's a bit confusing, sorry ^^'

template <class T>
sf::Vector2<T> cw90(const sf::Vector2<T>& a) {
  return {a.y, -a.x};
}

template <class T>
sf::Vector2<T> ccw90(const sf::Vector2<T>& a) {
  return {-a.y, a.x};
}

// clamping

template <class T>
T minCoord(const sf::Vector2<T>& a) {
  return std::min(a.x, a.y);
}

template <class T>
T maxCoord(const sf::Vector2<T>& a) {
  return std::max(a.x, a.y);
}

}  // namespace loki::core
