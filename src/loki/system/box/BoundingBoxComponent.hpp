#pragma once

#include <SFML/System/Time.hpp>

#include <loki/system/ecs/Component.hpp>
#include <loki/system/scheduler/UpdateTraits.hpp>

namespace loki::system {

class BoundingBoxComponent final : public Component {
 public:
  const sf::FloatRect& getLocalBox() const { return localBox; }
  const sf::FloatRect& getGlobalBox() const { return globalBox; }
  void setDirty() { isDirty = true; }

  void onUpdate(sf::Time delta) override;

 private:
  sf::FloatRect localBox;
  sf::FloatRect globalBox;
  bool isDirty = true;

  LOKI_RTTI_CLASS_DECLARE(BoundingBoxComponent)
};

}  // namespace loki::system

LOKI_REFLECTION_COMPONENT_BEGIN(loki::system::BoundingBoxComponent)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::BoundingBoxComponent)
