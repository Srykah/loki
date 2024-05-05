#pragma once

#include <loki/system/ecs/DrawableComponent.hpp>
#include <loki/graphics/sprites/Sprite.hpp>

namespace loki::components {
class SpriteComponent : public system::DrawableComponent, public system::ResourceListener {
 public:
  void init();
  void onResourcesLoaded() override;
  void update(sf::Time dt);
  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  system::ResourceHandle<graphics::SpriteDataResource> spriteData;
  graphics::Sprite sprite;

  bool isInit = false;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(SpriteComponent)
};

}  // namespace loki::components

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::components::SpriteComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::components::SpriteComponent, spriteData)
LOKI_REFLECTION_CLASS_END_RTTI(loki::components::SpriteComponent)