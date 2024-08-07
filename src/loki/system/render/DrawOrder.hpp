#pragma once

#include <cstdint>

namespace loki::system {

struct DrawOrder {
  std::int32_t layer = 0;
  float priority = 0;

  auto operator<=>(const DrawOrder&) const = default;
};

}  // namespace loki::system