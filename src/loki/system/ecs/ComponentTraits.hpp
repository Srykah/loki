#pragma once

#include <type_traits>

namespace loki::system {

class Component;
class DrawableComponent;

class BaseComponentTraits {
 public:
  virtual ~BaseComponentTraits() = default;

  virtual Component& getAsComponent(void* obj) const = 0;
  virtual bool isDrawable() const = 0;
  virtual const DrawableComponent* getAsDrawableComponent(const void* obj) const = 0;
};

namespace details {
template <class Comp>
concept IsDrawable = std::is_base_of_v<DrawableComponent, Comp>;
}  // namespace details

template <class T>
class ComponentTraits : public BaseComponentTraits {
  Component& getAsComponent(void* obj) const override { return static_cast<Component&>(*static_cast<T*>(obj)); }
  bool isDrawable() const override { return details::IsDrawable<T>; }
  const DrawableComponent* getAsDrawableComponent(const void* obj) const override {
    if constexpr (details::IsDrawable<T>) {
      return static_cast<const DrawableComponent*>(static_cast<const T*>(obj));
    }
    return nullptr;
  }
};

}  // namespace loki::system