#pragma once

namespace loki::system {

class ResourceListener {
 public:
  virtual ~ResourceListener() = default;
  virtual void onResourcesLoaded() = 0;
};

}  // namespace loki::system
