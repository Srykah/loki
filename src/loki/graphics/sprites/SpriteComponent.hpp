#pragma once

#include <loki/system/ecs/DrawableComponent.hpp>
#include <loki/graphics/sprites/Sprite.hpp>

namespace loki::graphics {
class SpriteComponent : public system::DrawableComponent {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;
  void update(sf::Time dt) override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  system::ResourceHandle<SpriteDataResource> spriteData;
  Sprite sprite;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(SpriteComponent)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::graphics::SpriteComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::SpriteComponent, spriteData)
LOKI_REFLECTION_CLASS_END_RTTI(loki::graphics::SpriteComponent)