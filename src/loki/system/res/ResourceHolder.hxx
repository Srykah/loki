namespace loki::system {

template <class Res>
void ResourceHolder::add(ResourceHandle<Res>& handle, ResourceListener* listener) {
  const auto& path = handle.getPath();
  auto it = resources.find(path);
  if (it == resources.end()) {
    it = resources.emplace_hint(it, path, new Res());
  }
  handle.ptr = static_pointer_cast<Res>(it->second.borrow());
  if (!listener)
    return;
  auto it2 = listeners.find(listener);
  if (it2 == listeners.end())
    it2 = listeners.insert(it2, {listener, {}});
  auto& listenerData = it2->second;
  listenerData.listenedResources.emplace_back(handle.ptr.get());
}

}  // namespace loki::system
