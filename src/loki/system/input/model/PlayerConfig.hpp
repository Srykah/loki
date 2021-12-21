/*!
 * \file PlayerConfig.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <string>

namespace loki::input {

struct PlayerConfig {
  std::string config;
  int joystickId = -1;  // -1 means keyboard
};

}  // namespace loki::input