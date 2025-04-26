#pragma once

#include <SFML/System/Time.hpp>
#include <ecs/Component.hpp>
#include <scheduler/UpdateTraits.hpp>

namespace loki::system {

class BoundingBoxComponent final : public Component {
 public:
  const sf::FloatRect& getLocalBox() const { return localBox; }
  const sf::FloatRect& getGlobalBox() const { return globalBox; }
  void setDirty() { isDirty = true; }

  void onUpdate(sf::Time delta);
  void onDebugDraw(sf::Time delta);

 private:
  sf::FloatRect localBox;
  sf::FloatRect globalBox;
  bool isDirty = true;

  LOKI_RTTI_CLASS_DECLARE(BoundingBoxComponent)
};

}  // namespace loki::system

LOKI_UPDATE_TRAITS_BEGIN(loki::system::BoundingBoxComponent)
LOKI_UPDATE_TRAITS_METHOD(Default, onUpdate)
LOKI_UPDATE_TRAITS_METHOD(DebugRender, onDebugDraw)
LOKI_UPDATE_TRAITS_END()

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::system::BoundingBoxComponent)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::BoundingBoxComponent)
