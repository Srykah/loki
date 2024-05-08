#pragma once

#include <vector>

#include <loki/system/ecs/Actor.hpp>

namespace loki::system {

struct ActorHierarchy {
  Actor parent;
  std::vector<Actor> children;
};

}  // namespace loki::system