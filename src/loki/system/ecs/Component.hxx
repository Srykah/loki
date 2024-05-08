#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/res/ResourceHolder.hpp>

namespace loki::system {

template <class... Ts>
void Component::addResources(ResourceHandle<Ts>&... handles) {
  auto& resHolder = getService<system::ResourceHolder>();
  (resHolder.add(handles, this), ...);
  status = Status::LOADING_RESOURCES;
}

}  // namespace loki::system