#include "SceneNode.hpp"

#include <loki/core/math/Vector2Ops.hpp>

namespace loki::system {

SceneNode::SceneNode(SceneNode* parent, const sf::Transformable& trs, const sf::FloatRect& bounds)
    : parent(parent), bounds(bounds) {
  setTrs(trs);
}

void SceneNode::setTrs(const sf::Transformable& trs) {
  setOrigin(trs.getOrigin());
  setPosition(trs.getPosition());
  setRotation(trs.getRotation());
  setScale(trs.getScale());
}

sf::Transform SceneNode::getGlobalTransform() const {
  auto trs = getTransform();
  for (auto* par = parent; par; par = par->parent) {
    trs = par->getTransform() * trs;
  }
  return trs;
}

sf::Vector2f SceneNode::getGlobalPosition() const {
  auto pos = getPosition();
  for (auto* par = parent; par; par = par->parent) {
    pos = par->getTransform().transformPoint(pos);
  }
  return pos;
}

float SceneNode::getGlobalRotation() const {
  float rot = getRotation();
  for (auto* par = parent; par; par = par->parent) {
    rot += par->getRotation();
  }
  return rot;
}

sf::Vector2f SceneNode::getGlobalScale() const {
  auto scale = getScale();
  for (auto* par = parent; par; par = par->parent) {
    core::compMult(scale, par->getScale());
  }
  return scale;
}

const sf::FloatRect& SceneNode::getLocalBounds() const {
  return bounds;
}

sf::FloatRect SceneNode::getGlobalBounds() const {
  return getGlobalTransform().transformRect(bounds);
}
const core::TypeInfo& SceneNode::getTypeInfo() const {
  return {.typeInfo = typeid(SceneNode),
          .name = "loki::core::SceneNode",
          .description = "A node in the scene's transform graph",
          .parents = {},
          .fields = {}};
}

}  // namespace loki::system
