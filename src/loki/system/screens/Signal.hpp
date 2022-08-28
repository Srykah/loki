#pragma once

#include <any>
#include <loki/core/hash/CombineHash.hpp>
#include <string>
#include <variant>

namespace loki::system {

class Screen;

struct Signal {
  struct Trigger {
    const Screen* origin;
    std::string signalName;

    bool operator==(const Trigger& other) const {
      return origin == other.origin && signalName == other.signalName;
    }
  } trigger;
  std::any value = std::monostate{};
};

}  // namespace loki::system

namespace std {

template <>
struct hash<loki::system::Signal::Trigger> {
  bool operator()(const loki::system::Signal::Trigger& trigger) const {
    return loki::core::combineHash(trigger.origin, trigger.signalName);
  }
};

}  // namespace std
