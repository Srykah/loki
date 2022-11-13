#pragma once

#include <map>

#include <loki/core/reflection/BaseObject.hpp>
#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/utils/Memory.hpp>

namespace loki::system {

class ServiceRegistry {
 public:
  template <class T>
  static bool registerService(core::OwnerPtr<T>&& service);

  template <class T>
  static T& get();

 private:
  friend class Application;
  ServiceRegistry();

  static const ServiceRegistry& getInstance();

 private:
  inline static ServiceRegistry* instance = nullptr;

  std::map<core::TypeInfo, core::OwnerPtr<core::BaseObject>> services;
};

}  // namespace loki::system

#include "ServiceRegistry.hxx"
