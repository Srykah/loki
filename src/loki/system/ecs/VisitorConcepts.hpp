#pragma once

#include <functional>

namespace loki::system {

class BaseComponentTraits;
class Actor;

using ComponentVisitor = std::move_only_function<void(const BaseComponentTraits&, void*)>;
using ConstComponentVisitor = std::move_only_function<void(const BaseComponentTraits&, const void*)>;
using ComponentTraitsFilter = std::move_only_function<bool(const BaseComponentTraits&)>;
using ActorFilter = std::move_only_function<bool(Actor)>;
using ActorVisitor = std::move_only_function<void(Actor)>;

}  // namespace loki::system
