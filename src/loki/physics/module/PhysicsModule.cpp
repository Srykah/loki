#include "PhysicsModule.hpp"

#include <loki/core/services/ServiceRegistry.hpp>

namespace loki::physics {
void PhysicsModule::registerAsAService(system::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

core::BorrowerPtr<PhysicsWorld> PhysicsModule::createWorld(PhysicsWorldParams&& params) {
  return worlds.emplace_back(new PhysicsWorld{std::move(params)}).borrow();
}
}  // namespace loki::physics
