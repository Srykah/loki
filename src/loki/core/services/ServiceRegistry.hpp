#pragma once

#include <stdexcept>
#include <unordered_map>

#include <loki/core/rtti/BaseObject.hpp>

namespace loki::core {

using TypeId = std::string;

class ServiceRegistry {
 public:
  template <RuntimeObject T>
  bool registerService(T& service) {
    auto [it, ok] = services.emplace(getTypeId<^^T>(), &service);
    if (!ok) {
      throw std::runtime_error("Service of this type is already registered!");
    }
    return ok;
  }

  template <RuntimeObject T>
  T& get() const {
    return static_cast<T&>(*services.at(getTypeId<^^T>()));
  }

  static void setInstance(const ServiceRegistry* instance) { s_instance = instance; }
  static const ServiceRegistry& getInstance() {
    if (s_instance == nullptr) {
      throw std::runtime_error("ServiceRegistry instance is not set!");
    }
    return *s_instance;
  }

 private:
  inline static const ServiceRegistry* s_instance = nullptr;

  std::unordered_map<TypeId, BaseObject*> services;
};

}  // namespace loki::core

namespace loki {

// shortcut
template <core::RuntimeObject T>
T& getService() {
  return core::ServiceRegistry::getInstance().get<T>();
}

}  // namespace loki
