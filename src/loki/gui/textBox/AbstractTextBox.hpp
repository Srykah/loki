/*!
 * \file AbstractTextBox.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/String.hpp>
#include <loki/gui/base/Widget.hpp>
#include <vector>

namespace loki::gui {

class AbstractTextBox : public Widget,
                        public sf::Drawable,
                        public sf::Transformable {
 public:
  ~AbstractTextBox() override = default;

  virtual bool hasEnded() const = 0;
  virtual bool canFitInLine(const sf::String& string,
                            unsigned int line) const = 0;
  virtual std::size_t getLineCount() const = 0;
  virtual void setLines(std::vector<sf::String> lines) = 0;
  virtual void clear() = 0;
};

}  // namespace loki::gui
