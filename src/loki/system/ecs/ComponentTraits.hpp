#pragma once

#include <type_traits>

#include <loki/system/scheduler/UpdateTraits.hpp>

namespace loki::system {

class Component;
class Drawable;
class DebugDrawable;

class BaseComponentTraits {
 public:
  virtual ~BaseComponentTraits() {}

  virtual Component& getAsComponent(void* obj) const = 0;
  const Component& getAsComponent(const void* obj) const { return getAsComponent(const_cast<void*>(obj)); }
  virtual const BaseUpdateTraits& getUpdateTraits() const = 0;
  virtual bool isDrawable() const = 0;
  virtual bool isDebugDrawable() const = 0;
  virtual const Drawable* getAsDrawable(const Component& comp) const = 0;
  virtual const DebugDrawable* getAsDebugDrawable(const Component& comp) const = 0;
};

namespace details {
template <class Comp>
concept IsDrawable = std::is_base_of_v<Drawable, Comp>;
template <class Comp>
concept IsDebugDrawable = std::is_base_of_v<DebugDrawable, Comp>;
}  // namespace details

template <class T>
  requires std::is_base_of_v<Component, T>
class ComponentTraits final : public BaseComponentTraits {
 public:
  ~ComponentTraits() override {}

  Component& getAsComponent(void* obj) const override { return static_cast<Component&>(*static_cast<T*>(obj)); }
  const BaseUpdateTraits& getUpdateTraits() const override {
    static UpdateTraits<T> updateTraits;
    return updateTraits;
  }
  bool isDrawable() const override { return details::IsDrawable<T>; }
  bool isDebugDrawable() const override { return details::IsDebugDrawable<T>; }
  const Drawable* getAsDrawable(const Component& comp) const override {
    if constexpr (details::IsDrawable<T>) {
      return &static_cast<const Drawable&>(static_cast<const T&>(comp));
    }
    return nullptr;
  }
  const DebugDrawable* getAsDebugDrawable(const Component& comp) const override {
    if constexpr (details::IsDebugDrawable<T>) {
      return &static_cast<const DebugDrawable&>(static_cast<const T&>(comp));
    }
    return nullptr;
  }
};

}  // namespace loki::system