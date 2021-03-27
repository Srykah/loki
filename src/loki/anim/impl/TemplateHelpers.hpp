/*!
 * \file TemplateHelpers.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

namespace loki::anim::impl {

// Origin
template <typename T>
using has_getOrigin = std::is_same<std::invoke_result<std::decay<decltype(&T::getOrigin)>>, sf::Vector2f>;
template <typename T>
using has_setOrigin = std::is_invocable<decltype(&T::setOrigin), sf::Vector2f&&>;

// Position
template <typename T>
constexpr bool has_getPosition = std::is_same_v<std::invoke_result<std::decay<decltype(&T::getPosition)>>, sf::Vector2f>;
template <typename T>
constexpr bool has_setPosition = std::is_invocable_v<decltype(&T::setPosition), sf::Vector2f&&>;

// Rotation
template <typename T>
constexpr bool has_getRotation = std::is_same_v<std::invoke_result<std::decay<decltype(&T::getRotation)>>, float>;
template <typename T>
constexpr bool has_setRotation = std::is_invocable_v<decltype(&T::setRotation), float>;

// Scale
template <typename T>
constexpr bool has_getScale = std::is_same_v<std::invoke_result<std::decay<decltype(&T::getScale)>>, sf::Vector2f>;
template <typename T>
constexpr bool has_setScale = std::is_invocable_v<decltype(&T::setScale), sf::Vector2f&&>;

// Color
template <typename T>
constexpr bool has_getColor = std::is_same_v<std::invoke_result<std::decay<decltype(&T::getColor)>>, sf::Color>;
template <typename T>
constexpr bool has_getFillColor = std::is_same_v<std::invoke_result<std::decay<decltype(&T::getFillColor)>>, sf::Color>;
template <typename T>
constexpr bool has_setColor = std::is_invocable_v<decltype(&T::setColor), sf::Color&&>;
template <typename T>
constexpr bool has_setFillColor = std::is_invocable_v<decltype(&T::setFillColor), sf::Color&&>;

// TextureRect
template <typename T>
constexpr bool has_getTextureRect = std::is_same_v<std::invoke_result<std::decay<decltype(&T::getTextureRect)>>, sf::IntRect>;
template <typename T>
constexpr bool has_setTextureRect = std::is_invocable_v<decltype(&T::setTextureRect), sf::IntRect&&>;

}
