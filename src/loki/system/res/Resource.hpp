/*!
 * \file Resource.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <memory>

#include <nlohmann/json.hpp>

#include <loki/core/json/Path.hpp>
#include <loki/core/utils/Memory.hpp>

namespace loki::res {

class ResourceHolder;

class Resource {
 public:
  explicit Resource(std::filesystem::path path) : path(std::move(path)) {}

  virtual ~Resource() = default;

  void load(ResourceHolder& resourceHolder) {
    this->loadImpl(path, resourceHolder);
    loaded = true;
  }

  void unload() {
    this->unloadImpl();
    loaded = false;
  }

  [[nodiscard]] const std::filesystem::path& getPath() const { return path; }

  [[nodiscard]] bool isLoaded() const { return loaded; }

 protected:
  virtual void loadImpl(const std::filesystem::path& path,
                        ResourceHolder& resourceHolder) = 0;

  virtual void unloadImpl() {}

 private:
  std::filesystem::path path;
  bool loaded = false;
};

}  // namespace loki::res
