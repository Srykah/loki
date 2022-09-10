#pragma once

#include <functional>

#include <SFML/System/Time.hpp>

namespace loki::core {

struct State {
  std::function<void()> onEnter;
  std::function<void(sf::Time)> onUpdate;
  std::function<void()> onLeave = nullptr;
};

}  // namespace loki::core
