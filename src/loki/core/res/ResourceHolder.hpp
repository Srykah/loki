/*!
 * \file ResourceHolder.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <loki/core/utils/Memory.hpp>
#include <unordered_set>
#include "Resource.hpp"
#include "ResourceHandle.hpp"

namespace loki::res {

class ResourceHolder {
 public:
  template <class Res>
  void add(ResourceHandle<Res>& handle);
  template <class Container>
  void add(Container& handles);

  void load();

 private:
  using ResPtr = OwnerPtr<Resource>;

  struct ResPtrHash {
    std::size_t operator()(const ResPtr& sptr) const {
      return std::hash<std::string>{}(sptr->getPath().generic_u8string());
    }
  };

  struct ResPtrComp {
    bool operator()(const ResPtr& lhs, const ResPtr& rhs) const {
      return lhs->getPath() == rhs->getPath();
    }
  };

  std::unordered_set<ResPtr, ResPtrHash, ResPtrComp> resources;
};

}  // namespace loki::res

#include "impl/ResourceHolder.hxx"
