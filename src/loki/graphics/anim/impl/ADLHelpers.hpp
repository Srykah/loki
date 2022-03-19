/*!
 * \file ADLHelpers.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <loki/core/utils/TemplateHelpers.hpp>
#include "TemplateHelpers.hpp"

namespace loki::anim {

// Origin

template <typename T>
sf::Vector2f getOrigin(T& animated) {
  if constexpr (is_detected_as_true<impl::has_getOrigin, T>) {
    return animated.getOrigin();
  }
  return sf::Vector2f{};
}

template <typename T>
void setOrigin(T& animated, sf::Vector2f origin) {
  if constexpr (is_detected_as_true<impl::has_setOrigin, T>) {
    animated.setOrigin(origin);
  }
}

// Position

template <typename T>
sf::Vector2f getPosition(T& animated) {
  if constexpr (is_detected_as_true<impl::has_getPosition, T>) {
    return animated.getPosition();
  }
  return sf::Vector2f{};
}

template <typename T>
void setPosition(T& animated, sf::Vector2f position) {
  if constexpr (is_detected_as_true<impl::has_setPosition, T>) {
    animated.setPosition(position);
  }
}

// Rotation

template <typename T>
float getRotation(T& animated) {
  if constexpr (is_detected_as_true<impl::has_getRotation, T>) {
    return animated.getRotation();
  }
  return 0.f;
}

template <typename T>
void setRotation(T& animated, float rotation) {
  if constexpr (is_detected_as_true<impl::has_setRotation, T>) {
    animated.setRotation(rotation);
  }
}

// Scale

template <typename T>
sf::Vector2f getScale(T& animated) {
  if constexpr (is_detected_as_true<impl::has_getScale, T>) {
    return animated.getScale();
  }
  return sf::Vector2f{};
}

template <typename T>
void setScale(T& animated, sf::Vector2f scale) {
  if constexpr (is_detected_as_true<impl::has_setScale, T>) {
    animated.setScale(scale);
  }
}

// Color

template <typename T>
sf::Color getColor(T& animated) {
  if constexpr (is_detected_as_true<impl::has_getFillColor, T>) {
    return animated.getFillColor();
  } else if constexpr (is_detected_as_true<impl::has_getColor, T>) {
    return animated.getColor();
  }
  return sf::Color{};
}

template <typename T>
void setColor(T& animated, sf::Color color) {
  if constexpr (is_detected_as_true<impl::has_setFillColor, T>) {
    animated.setFillColor(color);
  } else if constexpr (is_detected_as_true<impl::has_setColor, T>) {
    animated.setColor(color);
  }
}

// TextureRect

template <typename T>
sf::IntRect getTextureRect(T& animated) {
  if constexpr (is_detected_as_true<impl::has_getTextureRect, T>) {
    return animated.getTextureRect();
  }
  return sf::IntRect{};
}

template <typename T>
void setTextureRect(T& animated, sf::IntRect textureRect) {
  if constexpr (is_detected_as_true<impl::has_setTextureRect, T>) {
    animated.setTextureRect(textureRect);
  }
}

}  // namespace loki::anim
