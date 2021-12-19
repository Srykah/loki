/*!
 * \file TextBox.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <loki/gui/frame/AbstractFrame.hpp>
#include <loki/graphics/styles/TextStyle.hpp>
#include <memory>
#include "AbstractTextBox.hpp"

namespace loki::gui {

class TextBox : public AbstractTextBox {
 public:
  TextBox(unsigned int lineCount, styles::TextStyle textStyle, std::unique_ptr<AbstractFrame> frame);
  bool hasEnded() const override;
  bool canFitInLine(const sf::String& string, unsigned int line) const override;
  size_t getLineCount() const override;
  void setLines(std::vector<sf::String> lines) override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void clear() override;

 private:
  unsigned int lineCount;
  styles::TextStyle textStyle;
  std::unique_ptr<AbstractFrame> frame;
  std::vector<sf::Text> lines;
};

}
