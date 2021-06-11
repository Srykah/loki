/*!
 * \file LinAlg2D.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace loki::math {

// linalg

template <class T>
T dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
  return a.x * b.x + a.y * b.y;
}

template <class T>
T norm(const sf::Vector2<T>& a) {
  return std::sqrt(dot(a, a));
}

template <class T>
T det(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
  return a.x * b.y - a.y * b.x;
}

template <class T>
sf::Vector2<T> unit(const sf::Vector2<T>& a) {
  return a / norm(a);
}

// transforms

// note : rotations are here named according to the "classic" coordinate system,
// with x towards the right and y towards the top.
// This is coherent with the order of the Shapes's vertices :
// They appear clockwise on the screen, which has an inverted y axis.
// ... Yeah that's a bit confusing, sorry ^^'

template <class T>
sf::Vector2<T> cw90(const sf::Vector2<T>& a) {
  return { a.y, -a.x };
}

template <class T>
sf::Vector2<T> ccw90(const sf::Vector2<T>& a) {
  return { -a.y, a.x };
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

}
