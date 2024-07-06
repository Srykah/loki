#include "ServiceRegistry.hpp"

namespace loki::system {

const ServiceRegistry* ServiceRegistry::s_instance = nullptr;

ServiceRegistry::ServiceRegistry() {
  assert(!s_instance);
  s_instance = this;
}

void ServiceRegistry::setInstance(const ServiceRegistry* instance) {
  s_instance = instance;
}

const ServiceRegistry& ServiceRegistry::getInstance() {
  return *s_instance;
}

}  // namespace loki::system
