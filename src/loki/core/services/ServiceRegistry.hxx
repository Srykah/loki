#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::system {

template <core::ReflectedRuntimeObject T>
bool ServiceRegistry::registerService(T& service) {
  auto [it, ok] = services.emplace(&core::getTypeInfo<T>(), &service);
  return ok;
}

template <core::ReflectedRuntimeObject T>
T& ServiceRegistry::get() {
  return static_cast<T&>(*s_instance->services.at(&core::getTypeInfo<T>()));
}

}  // namespace loki::system

namespace loki {
template <core::ReflectedRuntimeObject T>
T& getService() {
  return system::ServiceRegistry::get<T>();
}
}  // namespace loki