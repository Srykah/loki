#pragma once

#include <type_traits>

#include <loki/system/scheduler/UpdateTraits.hpp>

namespace loki::system {

class Component;

class BaseComponentTraits {
 public:
  virtual ~BaseComponentTraits() = default;

  virtual Component& getAsComponent(void* obj) const = 0;
  const Component& getAsComponent(const void* obj) const { return getAsComponent(const_cast<void*>(obj)); }
  [[nodiscard]] virtual const BaseUpdateTraits& getUpdateTraits() const = 0;
};

template <class T>
  requires std::is_base_of_v<Component, T>
class ComponentTraits final : public BaseComponentTraits {
 public:
  ~ComponentTraits() override = default;

  Component& getAsComponent(void* obj) const override { return static_cast<Component&>(*static_cast<T*>(obj)); }
  [[nodiscard]] const BaseUpdateTraits& getUpdateTraits() const override {
    static UpdateTraits<T> updateTraits;
    return updateTraits;
  }
};

}  // namespace loki::system