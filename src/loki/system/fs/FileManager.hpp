#pragma once

#include <filesystem>
#include "FileCategory.hpp"

#if 0
#include <nlohmann/json.hpp>
#endif

namespace loki::system {

class FileManager {
 public:
  using Path = std::filesystem::path;

#if 0
  void loadDirectories(const nlohmann::json& directoriesData);
#endif

  void setDirectoryForCategory(FileCategory category, Path&& directory);
  const Path& getDirectoryForCategory(FileCategory category) const;
  std::ifstream openFileForRead(FileCategory category, const Path& relativePath) const;
  std::ofstream openFileForWrite(FileCategory category, const Path& relativePath) const;
  std::ofstream openFileForReadWrite(FileCategory category, const Path& relativePath) const;
};

}  // namespace loki::system
