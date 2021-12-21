/*!
 * \file Transition.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <functional>
#include <utility>
#include "StateIndex.hpp"

namespace loki::states {

struct Transition {
  Transition(StateIndex from,
             StateIndex to,
             std::function<bool()> isActive,
             std::function<void()> onTrigger = nullptr)
      : from(from),
        to(to),
        isActive(std::move(isActive)),
        onTrigger(std::move(onTrigger)) {}

  template <class Enum, std::enable_if_t<std::is_enum_v<Enum>, bool> = true>
  Transition(Enum from,
             Enum to,
             const std::function<bool()>& isActive,
             const std::function<void()>& onTrigger = nullptr)
      : Transition(static_cast<StateIndex>(from),
                   static_cast<StateIndex>(to),
                   isActive,
                   onTrigger) {}

  StateIndex from, to;
  std::function<bool()> isActive;
  std::function<void()> onTrigger;
};

}  // namespace loki::states
