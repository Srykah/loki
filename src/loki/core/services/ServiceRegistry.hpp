#pragma once

#include <unordered_map>

#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/rtti/rttiConcepts.hpp>

namespace loki::core {

class ServiceRegistry {
 public:
  ServiceRegistry();

  template <ReflectedRuntimeObject T>
  bool registerService(T& service);

  template <ReflectedRuntimeObject T>
  T& get() const;

  static void setInstance(const ServiceRegistry* instance);
  static const ServiceRegistry& getInstance();

 private:
  static const ServiceRegistry* s_instance;

  std::unordered_map<ClassId, BaseObject*> services;
};

}  // namespace loki::core

// shortcut
namespace loki {
template <core::ReflectedRuntimeObject T>
T& getService();
}  // namespace loki

#include "ServiceRegistry.hxx"
