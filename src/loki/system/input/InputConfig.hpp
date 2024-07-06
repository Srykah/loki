#pragma once

#include <map>

#include <loki/system/input/InputTriggers.hpp>

namespace loki::system {

using InputId = std::string;
using InputConfig = std::map<InputId, std::vector<std::unique_ptr<InputTrigger>>>;

}  // namespace loki::system
