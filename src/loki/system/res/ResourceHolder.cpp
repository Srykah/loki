#include "ResourceHolder.hpp"

#include <algorithm>

namespace loki::system {

void ResourceHolder::load() {
  std::vector<BaseResource*> newlyLoadingResources;
  for (auto&& [path, res] : resources) {
    auto& status = res->resourceLoadingStatus;
    if (status == ResourceLoadingStatus::Loading || status == ResourceLoadingStatus::Loaded) {
      continue;
    }
    if (res->load(path)) {
      status = ResourceLoadingStatus::Loading;
      newlyLoadingResources.emplace_back(res.get());
    } else {
      status = ResourceLoadingStatus::Failed;
    }
  }
  for (BaseResource* newlyLoadingResource : newlyLoadingResources) {
    if (!newlyLoadingResource->addChildResourcesToHolder(*this)) {
      newlyLoadingResource->onResourcesLoaded();  // if no child resource, consider they're loaded
      newlyLoadingResource->resourceLoadingStatus = ResourceLoadingStatus::Loaded;
    }
  }
  for (auto&& [listener, listenerData] : listeners) {
    if (!listenerData.hasAlreadyNotified &&
        std::ranges::all_of(listenerData.listenedResources, [](const BaseResource* child) {
          return child->getResourceLoadingStatus() == ResourceLoadingStatus::Loaded;
        })) {
      listener->resourceLoadingStatus = ResourceLoadingStatus::Loaded;
      listener->onResourcesLoaded();
      listenerData.hasAlreadyNotified = true;
    }
  }
}

}  // namespace loki::system
