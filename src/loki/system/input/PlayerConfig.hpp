#pragma once

#include <string>

namespace loki::system {

struct PlayerConfig {
  std::string config;
  int joystickId = -1;  // -1 means keyboard
};

}  // namespace loki::system