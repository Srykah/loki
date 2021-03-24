/*!
 * \file Signal.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <any>
#include <loki/hash/CombineHash.hpp>
#include <string>
#include <variant>

namespace loki::screens {

class Screen;

struct Signal {
  struct Trigger {
    const Screen* origin;
    std::string signalName;

    bool operator==(const Trigger& other) const {
      return origin == other.origin && signalName == other.signalName;
    }
  } trigger;
  std::any value = std::monostate {};
};

}  // namespace loki::screens

namespace std {

template <>
struct hash<loki::screens::Signal::Trigger> {
  bool operator()(const loki::screens::Signal::Trigger& trigger) const {
    return loki::hash::combineHash(trigger.origin, trigger.signalName);
  }
};

}  // namespace std
