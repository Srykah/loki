#pragma once

#include <SFML/Window.hpp>
#include <filesystem>
#include <map>
#include <string>
#include <variant>
#include "InputType.hpp"

namespace loki::system {

struct InputSettings {
  InputSettings() = default;
  explicit InputSettings(const std::filesystem::path& filepath);

  bool load(const std::filesystem::path& filepath);

 public:
  using Config = std::map<std::string, std::vector<InputTrigger>>;

  std::map<std::string, Config> configs;
};

}  // namespace loki::system
