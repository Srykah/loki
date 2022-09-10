#pragma once

#include <any>
#include <string>
#include <variant>

#include <loki/core/hash/CombineHash.hpp>

namespace loki::system {

class Screen;

struct Signal {
  struct Trigger {
    const Screen* origin;
    std::string signalName;

    [[nodiscard]] bool operator<=>(const Trigger&) const = default;
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
