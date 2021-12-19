/*!
 * \file State.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <functional>
#include <SFMl/System/Time.hpp>

namespace loki::states {

struct State {
  std::function<void()> onEnter;
  std::function<void(sf::Time)> onUpdate;
  std::function<void()> onLeave = nullptr;
};

}
