#pragma once

#include "loki/gui/Widget.hpp"
#include "loki/system/input/EventHandler.hpp"

namespace loki::gui {

class TextBox : public Widget {
 public:
  TextBox(const loki::system::EventHandler& eventHandler,
          std::string nextInputName);

  void setNextInputName(std::string nextInputName);
  [[nodiscard]] const std::string& getNextInputName() const;

  void setAnnotatedString(const std::string& annotatedString);

  void update(sf::Time delta) override;
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = {}) const override {}

 private:
  const loki::system::EventHandler& eventHandler;
  std::string nextInputName;
  std::vector<std::string> splitString;
  std::size_t curString = 0;
};

}  // namespace loki::gui
