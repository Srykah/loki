#pragma once

#include <type_traits>

#include <SFML/Graphics/Rect.hpp>

#include <loki/system/scheduler/UpdateTraits.hpp>

namespace loki::system {

class Component;

class BaseComponentTraits {
 public:
  virtual ~BaseComponentTraits() = default;

  [[nodiscard]] virtual const core::TypeInfo& getTypeInfo() const = 0;
  [[nodiscard]] virtual Component& getAsComponent(void* obj) const = 0;
  [[nodiscard]] const Component& getAsComponent(const void* obj) const {
    return getAsComponent(const_cast<void*>(obj));
  }
  [[nodiscard]] virtual const BaseUpdateTraits& getUpdateTraits() const = 0;
  [[nodiscard]] virtual bool hasBoundingBox() const = 0;
  [[nodiscard]] virtual sf::FloatRect getBoundingBox(const void* obj) const = 0;
};

template <class T>
  requires std::is_base_of_v<Component, T>
class ComponentTraits final : public BaseComponentTraits {
 public:
  ~ComponentTraits() override = default;

  [[nodiscard]] const core::TypeInfo& getTypeInfo() const override { return core::getTypeInfo<T>(); }
  [[nodiscard]] Component& getAsComponent(void* obj) const override {
    return static_cast<Component&>(*static_cast<T*>(obj));
  }
  [[nodiscard]] const BaseUpdateTraits& getUpdateTraits() const override {
    static UpdateTraits<T> updateTraits;
    return updateTraits;
  }
  [[nodiscard]] bool hasBoundingBox() const override {
    return requires { std::declval<T>().getBoundingBox(); };
  }
  [[nodiscard]] sf::FloatRect getBoundingBox(const void* obj) const override {
    if constexpr (requires { std::declval<T>().getBoundingBox(); }) {
      return static_cast<const T*>(obj)->getBoundingBox();
    }
    return {};
  }
};

}  // namespace loki::system