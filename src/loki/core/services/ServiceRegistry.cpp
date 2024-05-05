#include "ServiceRegistry.hpp"

namespace loki::system {

ServiceRegistry::ServiceRegistry() {
  assert(!s_instance);
  s_instance = this;
}

}  // namespace loki::system
