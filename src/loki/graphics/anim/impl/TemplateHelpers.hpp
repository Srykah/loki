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

#define LOKI_ANIM_FEATURE_TEST(Feature, Type) \
template <typename T> using has_get##Feature = std::is_same<std::decay_t<std::invoke_result_t<decltype(&T::get##Feature), T>>, Type>; \
template <typename T> using has_set##Feature = std::is_invocable<decltype(&T::set##Feature), T, Type&&>;

LOKI_ANIM_FEATURE_TEST(Origin, sf::Vector2f)
LOKI_ANIM_FEATURE_TEST(Position, sf::Vector2f)
LOKI_ANIM_FEATURE_TEST(Rotation, float)
LOKI_ANIM_FEATURE_TEST(Scale, sf::Vector2f)
LOKI_ANIM_FEATURE_TEST(Color, sf::Color)
LOKI_ANIM_FEATURE_TEST(FillColor, sf::Color)
LOKI_ANIM_FEATURE_TEST(TextureRect, sf::IntRect)

#undef LOKI_ANIM_FEATURE_TEST

}
