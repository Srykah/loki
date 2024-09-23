#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include <loki/system/render/Drawable.hpp>

namespace loki::system {

class RenderQueue final : public sf::Drawable {
 public:
  void registerDrawable(DrawOrder drawOrder, const system::Drawable* drawable);
  void registerDebugDrawable(DrawOrder drawOrder, const DebugDrawable* debugDrawable);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void clear();

  void setOverdraw(bool flag);

 private:
  struct DrawList {
    std::vector<const system::Drawable*> drawables;
    std::vector<const DebugDrawable*> debugDrawables;
  };
  std::map<DrawOrder, DrawList> drawLists;
  bool overdraw = false;
};

}  // namespace loki::system