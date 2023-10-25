#include <nlohmann/json.hpp>

namespace loki::core {

template <RTTIObject T>
void ReflectionFactory::registerClass() {
  registerClass<T>([]() { return new T(); });
}

template <RTTIObject T>
void ReflectionFactory::registerClass(ReflectionFactory::Builder&& builder) {
  builders.emplace(getTypeInfo<T>()->name, std::move(builder));
}

template <RTTIObject T>
std::unique_ptr<T> ReflectionFactory::build(std::string_view realClassName) {
  return std::unique_ptr<T>{static_cast<T*>(builders.at(realClassName)())};
}

}  // namespace loki::core