#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::core {

template <ReflectedRuntimeObject T>
bool ServiceRegistry::registerService(T& service) {
  const auto& classInfo = std::get<ClassInfo>(core::getTypeInfo<T>().info);
  auto [it, ok] = services.emplace(classInfo.id, &service);
  return ok;
}

template <ReflectedRuntimeObject T>
T& ServiceRegistry::get() const {
  const auto& classInfo = std::get<ClassInfo>(core::getTypeInfo<T>().info);
  return static_cast<T&>(*s_instance->services.at(classInfo.id));
}

}  // namespace loki::core

namespace loki {
template <core::ReflectedRuntimeObject T>
T& getService() {
  return core::ServiceRegistry::getInstance().get<T>();
}
}  // namespace loki