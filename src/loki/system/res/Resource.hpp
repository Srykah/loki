#pragma once

#include <loki/system/res/ResourceListener.hpp>
#include <loki/system/res/ResourceLoadingStatus.hpp>

namespace loki::system {

class ResourceHolder;

class BaseResource : public ResourceListener {
 public:
  ~BaseResource() override = default;

 private:
  friend ResourceHolder;

  void onResourcesLoaded() override { onChildResourcesLoaded(); }

 protected:
  virtual void load(const std::filesystem::path& path) = 0;
  virtual bool addChildResourcesToHolder(ResourceHolder& holder) { return false; }
  virtual void onChildResourcesLoaded() {}
  virtual void unload() {}
};

template <class T>
class Resource : public BaseResource {
 public:
  using DataType = T;

  [[nodiscard]] virtual const T& getData() const = 0;
};

}  // namespace loki::system
