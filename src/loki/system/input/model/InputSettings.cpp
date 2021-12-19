/*!
 * \file InputSettings.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "InputSettings.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace loki::input {

InputSettings::InputSettings(const std::filesystem::path& filepath) {
  load(filepath);
}

bool InputSettings::load(const std::filesystem::path &filepath) {
  std::ifstream fs(filepath);
  nlohmann::json json;
  fs >> json;

  for (auto&& [configName, configData] : json.items()) {
    Config config;
    for (auto&& [inputName, triggerData]: configData.items()) {
      std::vector<InputTrigger> triggers;
      for (const auto& triggerDatum : triggerData) {
        triggers.emplace_back(loadTrigger(triggerDatum));
      }
      config.emplace(inputName, std::move(triggers));
    }
    configs.emplace(configName, std::move(config));
  }

  return true;
}

}
