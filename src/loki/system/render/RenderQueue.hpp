#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include <loki/system/render/DrawOrder.hpp>

namespace loki::system {

class RenderQueue final : public sf::Drawable {
 public:
  void registerDrawable(const sf::Drawable* drawable, DrawOrder drawOrder, bool isDebug = false);
  void updateDrawOrder(const sf::Drawable* drawable, DrawOrder drawOrder);
  void unregisterDrawable(const sf::Drawable* drawable);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void clear();

  void setOverdraw(bool flag);

 private:
  struct DrawEntry {
    const sf::Drawable* drawable = nullptr;
    DrawOrder drawOrder;
    bool isDebug = false;

    static bool less(const DrawEntry& _lhs, const DrawEntry& _rhs);
    static bool lessOverdraw(const DrawEntry& _lhs, const DrawEntry& _rhs);
  };
  std::vector<DrawEntry> drawEntries;
  bool overdraw = true;
};

}  // namespace loki::system