namespace loki::system {

template <class T>
bool ServiceRegistry::registerService(core::OwnerPtr<T>&& service) {
  auto [it, ok] = getInstance().services.emplace(core::getTypeInfo<T>(), move(service));
  return ok;
}

}  // namespace loki::system