#pragma once

#include <cassert>

#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/reflection/classMeta.hpp>
#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/rtti/rttiMacros.hpp>

namespace loki::core {

/* How to use:
 * 1. Put all your classes & enums in the same namespace (e.g. `myGame`), they can be in sub-namespaces if you want.
 * 2. Annotate the classes & enums you want to reflect with [[=loki::reflect]].
 * 3. Include all the headers of the classes & enums you want to reflect in your module's entry point (e.g.
 * `myGameModule.cpp`).
 * 4. In your module's `registerTypes` function, call
 * `loki::core::registerReflectedClasses<^^myGame>(registry)`.
 */
class TypeRegistry : public BaseObject {
 public:
  void registerType(TypeInfo&& typeInfo);

  [[nodiscard]] const TypeInfo& getFromId(const TypeId& id) const;
  template <class T>
  [[nodiscard]] const TypeInfo& get() const {
    return getFromId(getTypeId<^^T>());
  }

  // Registers all classes and enums with the [[=loki::reflect]] annotation
  template <std::meta::info namespaceMeta>
  void registerReflectedClasses(loki::core::TypeRegistry& registry) {
    static constexpr auto membersMeta =
        std::define_static_array(std::meta::members_of(namespaceMeta, std::meta::access_context::unchecked()));
    template for (constexpr auto memberMeta : membersMeta) {
      if constexpr (hasReflectAnnotation<memberMeta>()) {
        registry.registerType(details::computeTypeInfo<([:memberMeta:])>());
      }
      registerReflectedClasses<memberMeta>(registry);  // Recurse into nested namespaces / classes
    }
  }

  void* asAncestor(void* ptr, const TypeInfo* ptrType, const TypeId& ancestorId);

 private:
  std::unordered_map<TypeId, TypeInfo> typeIdToTypeInfo;

  LOKI_RTTI_CLASS_DECLARE()
};

}  // namespace loki::core

// shortcuts
namespace loki {

[[nodiscard]] const core::TypeInfo& getTypeInfoFromId(const core::TypeId& id);
template <class T>
[[nodiscard]] const core::TypeInfo& getTypeInfo() {
  return getTypeInfoFromId(core::getTypeId<^^T>());
}

}  // namespace loki
