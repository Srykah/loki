/*!
 * \file TextBox.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#if 0

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <loki/graphics/styles/ShapeStyle.hpp>
#include <loki/graphics/text/AnimatedText.hpp>
#include <loki/graphics/text/Stylesheet.hpp>
#include <memory>
#include "loki/gui/interfaces/Widget.hpp"

namespace loki::gui {

class TextBoxView : public AWidgetView {
 public:
  TextBoxView(sf::Vector2f size,
              float padding,
              unsigned int lineCount,
              const styles::ShapeStyle& frameStyle,
              const text::Stylesheet& textStylesheet);

  void setAnnotatedString(const std::string& annotatedString);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void update(sf::Time delta) override {}
  void advance();
  void skipAnimation();
  void clear();

  [[nodiscard]] bool hasAnimationStopped() const;
  [[nodiscard]] bool hasEnded() const;

 protected:
  void hideImpl() override {}
  void unhideImpl() override {}
  void enableImpl() override {}
  void disableImpl() override {}
  void focusImpl() override {}
  void unfocusImpl() override {}
  void activateImpl() override {}
  void deactivateImpl() override {}

 private:
  sf::RectangleShape frame;
  const float padding;
  const unsigned int lineCount;
  const text::Stylesheet& textStylesheet;
  const styles::ShapeStyle& frameStyle;
  std::vector<std::vector<text::AnimatedText>> lines;
};

}  // namespace loki::gui

#endif