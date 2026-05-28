#pragma once

#include <SFML/Config.hpp>
#include <SFML/Window/WindowEnums.hpp>

#include <loki/core/reflection/enumMacros.hpp>
#include <loki/core/utils/EnumAsBitField.hpp>

namespace loki::system {

enum class WindowStyle : std::uint32_t {
  NONE = sf::Style::None,
  TITLEBAR = sf::Style::Titlebar,
  RESIZE = sf::Style::Resize,
  CLOSE = sf::Style::Close,
  SFML_MASK = sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,

  FULLSCREEN = 1u << 5u,
  LETTERBOXED = 1u << 6u,
  INTEGER_SCALING = 1u << 7u,

  DEFAULT = sf::Style::Default,
  DEFAULT_LETTERBOXED = DEFAULT | LETTERBOXED,
  DEFAULT_INTEGER_SCALING = DEFAULT | INTEGER_SCALING,
};

LOKI_ENUM_AS_BITFIELD(WindowStyle)

[[nodiscard]] constexpr std::uint32_t toSFMLWindowStyle(WindowStyle style) noexcept {
  return std::to_underlying(style & WindowStyle::SFML_MASK);
}

[[nodiscard]] constexpr WindowStyle fromSMFLWindowStyle(std::uint32_t sfmlStyle) noexcept {
  return static_cast<WindowStyle>(sfmlStyle) & WindowStyle::SFML_MASK;
}

}  // namespace loki::system

LOKI_REFLECTION_ENUM_BEGIN(loki::system::WindowStyle)
LOKI_REFLECTION_ENUMERATOR(NONE)
LOKI_REFLECTION_ENUMERATOR(TITLEBAR)
LOKI_REFLECTION_ENUMERATOR(RESIZE)
LOKI_REFLECTION_ENUMERATOR(CLOSE)
LOKI_REFLECTION_ENUMERATOR(FULLSCREEN)
LOKI_REFLECTION_ENUMERATOR(SFML_MASK)
LOKI_REFLECTION_ENUMERATOR(LETTERBOXED)
LOKI_REFLECTION_ENUMERATOR(INTEGER_SCALING)
LOKI_REFLECTION_ENUMERATOR(DEFAULT)
LOKI_REFLECTION_ENUMERATOR(DEFAULT_LETTERBOXED)
LOKI_REFLECTION_ENUMERATOR(DEFAULT_INTEGER_SCALING)
LOKI_REFLECTION_ENUM_END()
