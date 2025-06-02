#pragma once

#include <loki/system/res/ResourceLoadingStatus.hpp>

namespace loki::system {

class ResourceListener {
 public:
  virtual ~ResourceListener() = default;
  virtual void onResourcesLoaded() {}

  ResourceLoadingStatus getResourceLoadingStatus() const { return resourceLoadingStatus; }

 private:
  friend class ResourceHolder;
  ResourceLoadingStatus resourceLoadingStatus = ResourceLoadingStatus::Unloaded;
};

}  // namespace loki::system
