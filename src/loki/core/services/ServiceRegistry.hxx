#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::system {

template <core::ReflectedRuntimeObject T>
bool ServiceRegistry::registerService(T& service) {
  const auto& classInfo = std::get<core::ClassInfo>(core::getTypeInfo<T>().info);
  auto [it, ok] = services.emplace(classInfo.id, &service);
  return ok;
}

template <core::ReflectedRuntimeObject T>
T& ServiceRegistry::get() const {
  const auto& classInfo = std::get<core::ClassInfo>(core::getTypeInfo<T>().info);
  return static_cast<T&>(*s_instance->services.at(classInfo.id));
}

}  // namespace loki::system

namespace loki {
template <core::ReflectedRuntimeObject T>
T& getService() {
  return system::ServiceRegistry::getInstance().get<T>();
}
}  // namespace loki