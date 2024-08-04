#pragma once

#include <utility>

#define LOKI_ENUM_AS_BITFIELD(Enum)                                                   \
  [[nodiscard]] constexpr Enum operator|(Enum first, Enum second) noexcept {          \
    return static_cast<Enum>(std::to_underlying(first) | std::to_underlying(second)); \
  }                                                                                   \
  constexpr Enum& operator|=(Enum& first, Enum second) noexcept {                     \
    return first = first | second;                                                    \
  }                                                                                   \
  [[nodiscard]] constexpr Enum operator&(Enum first, Enum second) noexcept {          \
    return static_cast<Enum>(std::to_underlying(first) & std::to_underlying(second)); \
  }                                                                                   \
  [[nodiscard]] constexpr bool contains(Enum value, Enum flags) noexcept {            \
    return (value & flags) == flags;                                                  \
  }
