/*!
 * \file InputSettings.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Window.hpp>
#include <map>
#include <string>
#include <variant>
#include <filesystem>
#include "InputType.hpp"

namespace loki::input {

struct InputSettings {
  InputSettings() = default;
  explicit InputSettings(const std::filesystem::path& filepath);

  bool load(const std::filesystem::path& filepath);

 public:
  using Config = std::map<std::string, std::vector<InputTrigger>>;

  std::map<std::string, Config> configs;
};

}
