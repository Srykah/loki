#pragma once

#include <unordered_set>

#include <loki/core/utils/Memory.hpp>

#include "Resource.hpp"
#include "ResourceHandle.hpp"

namespace loki::system {

class ResourceHolder {
 public:
  template <class Res>
  void add(ResourceHandle<Res>& handle);
  template <class Container>
  void add(Container& handles);

  void load();

 private:
  using ResPtr = core::OwnerPtr<Resource>;

  struct ResPtrHash {
    std::size_t operator()(const ResPtr& sptr) const {
      return std::hash<std::string>{}(sptr->getPath().generic_string());
    }
  };

  struct ResPtrComp {
    bool operator()(const ResPtr& lhs, const ResPtr& rhs) const {
      return lhs->getPath() == rhs->getPath();
    }
  };

  std::unordered_set<ResPtr, ResPtrHash, ResPtrComp> resources;
};

}  // namespace loki::system

#include "ResourceHolder.hxx"
