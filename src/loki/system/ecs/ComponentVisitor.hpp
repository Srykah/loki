#pragma once

#include <functional>

namespace loki::system {

class BaseComponentTraits;

using ComponentVisitor = std::function<void(const BaseComponentTraits&, void*)>;
using ComponentTraitsFilter = std::function<bool(const BaseComponentTraits&)>;

}  // namespace loki::system
