#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include "AnimatedText.hpp"
#include "Stylesheet.hpp"

namespace loki::gfx {

using AnnotatedString = std::vector<std::pair<std::string, AnimatedTextStyle>>;

class AnnotatedText : public sf::Drawable, public sf::Transformable {
 public:
  explicit AnnotatedText() = default;
  explicit AnnotatedText(const AnnotatedString& annotatedString) {
    setAnnotatedString(annotatedString);
  }

  void setAnnotatedString(const AnnotatedString& annotatedString);

  void update(sf::Time delta);
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

  void skip();

 private:
  std::vector<AnimatedText> blocks;
};

}  // namespace loki::gfx
