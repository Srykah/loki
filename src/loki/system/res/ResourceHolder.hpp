#pragma once

#include <filesystem>
#include <unordered_map>

#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/utils/Memory.hpp>
#include <loki/system/res/Resource.hpp>
#include <loki/system/res/ResourceHandle.hpp>

namespace loki::system {

class ResourceHolder : public core::BaseObject {
 public:
  template <class Res>
  void add(ResourceHandle<Res>& handle, ResourceListener* listener = nullptr);

  void load();
  void clearOrphans();

 private:
  using ResPtr = core::OwnerPtr<BaseResource>;
  struct ListenerData {
    std::vector<const BaseResource*> listenedResources;
    bool hasAlreadyNotified = false;
  };

  std::unordered_map<std::filesystem::path, ResPtr> resources;
  std::unordered_map<ResourceListener*, ListenerData> listeners;

  LOKI_RTTI_CLASS_DECLARE(ResourceHolder)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::ResourceHolder)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::ResourceHolder)

#include "ResourceHolder.hxx"
