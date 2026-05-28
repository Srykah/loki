#include "ServiceRegistry.hpp"

#include <cassert>

namespace loki::core {

ServiceRegistry::ServiceRegistry() {
  assert(!getInstancePtr());
  getInstancePtr() = this;
}

void ServiceRegistry::setInstance(const ServiceRegistry* instance) {
  getInstancePtr() = instance;
}

const ServiceRegistry& ServiceRegistry::getInstance() {
  return *getInstancePtr();
}

const ServiceRegistry*& ServiceRegistry::getInstancePtr() {
  static const ServiceRegistry* s_instance = nullptr;
  return s_instance;
}

}  // namespace loki::core
