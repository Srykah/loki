#pragma once

#include "InputConfig.hpp"
#include "InputMethod.hpp"

namespace loki::system {

using PlayerId = unsigned int;
using InputConfigId = std::string;

struct PlayerConfig {
  InputConfigId configId;
  InputMethod inputMethod = InputMethod::KeyboardAndMouse;
};

}  // namespace loki::system