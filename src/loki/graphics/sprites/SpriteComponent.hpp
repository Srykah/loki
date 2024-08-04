#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/system/render/Drawable.hpp>
#include <loki/graphics/sprites/Sprite.hpp>

namespace loki::graphics {
class SpriteComponent : public system::Component, public system::Drawable {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;
  void update(sf::Time dt) override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  system::ResourceHandle<SpriteDataResource> spriteData;
  Sprite sprite;

  LOKI_RTTI_CLASS_DECLARE(SpriteComponent)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::graphics::SpriteComponent)
LOKI_REFLECTION_CLASS_FIELD(spriteData)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::graphics::SpriteComponent)