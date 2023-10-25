#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>

#include "FileCategory.hpp"

namespace loki::system {

class FileManager {
 public:
  using Path = std::filesystem::path;

  void loadDirectories(const core::json& directoriesData);
  void setDirectoryForCategory(FileCategory category, Path&& directory);
  const Path& getDirectoryForCategory(FileCategory category) const;
  std::ifstream openFileForRead(FileCategory category, const Path& relativePath) const;
  std::ofstream openFileForWrite(FileCategory category, const Path& relativePath) const;
  std::ofstream openFileForReadWrite(FileCategory category, const Path& relativePath) const;
};

}  // namespace loki::system
