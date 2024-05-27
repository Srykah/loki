#pragma once

#include <loki/system/res/ResourceListener.hpp>

namespace loki::system {

class BaseResource : public ResourceListener {
 public:
  enum class LoadingStatus {
    Unloaded,
    Loading,
    Loaded,
  };

 public:
  ~BaseResource() override = default;

  [[nodiscard]] LoadingStatus getLoadingStatus() const { return loadingStatus; }

 private:
  friend class ResourceHolder;

  void load(const std::filesystem::path& path) {
    loadImpl(path);
    loadingStatus = LoadingStatus::Loading;
  }
  void onResourcesLoaded() override {
    onChildResourcesLoadedImpl();
    loadingStatus = LoadingStatus::Loaded;
  }
  void unload() {
    unloadImpl();
    loadingStatus = LoadingStatus::Unloaded;
  }

 protected:
  virtual void loadImpl(const std::filesystem::path& path) = 0;
  virtual bool addChildResourcesToHolder(ResourceHolder& holder) { return false; }
  virtual void onChildResourcesLoadedImpl(){};
  virtual void unloadImpl() {}

 private:
  LoadingStatus loadingStatus = LoadingStatus::Unloaded;
};

template <class T>
class Resource : public BaseResource {
 public:
  using DataType = T;

  [[nodiscard]] virtual const T& getData() const = 0;
};

}  // namespace loki::system
