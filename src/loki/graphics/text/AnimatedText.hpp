#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include "AnimatedGlyph.hpp"
#include "Stylesheet.hpp"

namespace loki::gfx {

class AnimatedText : public sf::Drawable, public sf::Transformable {
 public:
  AnimatedText(const std::string& str, AnimatedTextStyle style);
  ~AnimatedText() override = default;

  void update(sf::Time delta);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void skip();
  [[nodiscard]] bool hasFinishedAppearing() const;
  void end();

  [[nodiscard]] sf::FloatRect getLocalBounds() const;

 private:
  void init(const std::string& str);

 private:
  bool isEnding = false;
  sf::Time elapsedTime;
  AnimatedTextStyle style;
  sf::VertexArray vertices;
  std::vector<AnimatedGlyph> glyphs;
};

}  // namespace loki::text
