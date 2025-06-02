#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/system/scheduler/UpdateTraits.hpp>
#include <loki/graphics/sprites/Sprite.hpp>

namespace loki::graphics {
class SpriteComponent : public system::Component, public sf::Drawable {
 public:
  void onBeginInit() override;
  void onEndInit() override;
  void onUpdate(sf::Time delta) override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  system::ResourceHandle<SpriteDataResource> spriteData;
  Sprite sprite;

  LOKI_RTTI_CLASS_DECLARE(SpriteComponent)
};

}  // namespace loki::graphics

LOKI_REFLECTION_COMPONENT_BEGIN(loki::graphics::SpriteComponent)
LOKI_REFLECTION_CLASS_FIELD(spriteData)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::graphics::SpriteComponent)
