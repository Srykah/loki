#pragma once

#include <filesystem>
#include <map>
#include <string>

#include <nlohmann/json.hpp>

#include <loki/core/json/Path.hpp>

namespace loki::system {

using SceneId = std::string;

class SceneManager {
 private:
  std::map<SceneId, std::filesystem::path> paths;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneManager, paths)
};

}  // namespace loki::system