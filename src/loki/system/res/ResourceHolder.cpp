#include "ResourceHolder.hpp"

#include <algorithm>

namespace loki::system {

void ResourceHolder::load() {
  std::vector<BaseResource*> newlyLoadingResources;
  for (auto&& [path, res] : resources) {
    if (auto status = res->getLoadingStatus(); status != BaseResource::LoadingStatus::Unloaded)
      continue;
    res->load(path);
    newlyLoadingResources.emplace_back(res.get());
  }
  for (BaseResource* newlyLoadingResource : newlyLoadingResources) {
    if (!newlyLoadingResource->addChildResourcesToHolder(*this))
      newlyLoadingResource->onResourcesLoaded();  // if no child resource, consider they're loaded
  }
  for (auto&& [listener, listenerData] : listeners) {
    if (!listenerData.hasAlreadyNotified &&
        std::ranges::all_of(listenerData.listenedResources, [](const BaseResource* child) {
          return child->getLoadingStatus() == BaseResource::LoadingStatus::Loaded;
        })) {
      listener->onResourcesLoaded();
      listenerData.hasAlreadyNotified = true;
    }
  }
}

}  // namespace loki::system
