#include "PhysicsBodyComponent.hpp"

#include <render/RendererModule.hpp>

#include <loki/system/scene/SceneManager.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>

namespace loki::physics {

void PhysicsBodyComponent::onBeginInit() {
  body =
      getScene().getRoot().getComponent<PhysicsWorldComponent>()->getWorld()->createBody(PhysicsBodyParams{bodyParams});
  for (const auto& shapeParam : shapeParams) {
    body.createShape(*shapeParam);
  }
}

void PhysicsBodyComponent::onEndInit() {
  body.setTransformable(getActor().getTransformable());  // init position and rotation
}

void PhysicsBodyComponent::onPrePhysics(sf::Time dt) {
  if (bodyParams.type == PhysicsBodyType::Static) {
    body.setTransformable(getActor().getTransformable());
  }
}

void PhysicsBodyComponent::onPhysicsResult(sf::Time dt) {
  auto transformable = getActor().getTransformable();
  transformable.setPosition(body.getPosition());
  transformable.setRotation(body.getRotation());
  getActor().setTransformable(std::move(transformable));
}

sf::FloatRect PhysicsBodyComponent::getBoundingBox() const {
  return body.getBoundingBox();
}

}  // namespace loki::physics
