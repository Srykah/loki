namespace loki::system {

template <class Res>
void ResourceHolder::add(ResourceHandle<Res>& handle) {
  auto it = std::find_if(resources.begin(), resources.end(),
                         [&handle](const ResPtr& ptr) {
                           return ptr->getPath() == handle.getPath();
                         });
  if (it == resources.end()) {
    it = resources.emplace(new Res(handle.getPath())).first;
  }
  handle.ptr = static_pointer_cast<Res>(it->borrow());
}

template <class Container>
void ResourceHolder::add(Container& handles) {
  for (auto& handle : handles) {
    add(handle);
  }
}

}  // namespace loki::system
