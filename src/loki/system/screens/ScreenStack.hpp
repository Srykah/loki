/*!
 * \file StateStack.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <any>
#include <memory>
#include <stack>
#include "Signal.hpp"

namespace loki::screens {

class Screen;

class ScreenStack : public sf::Drawable {
 public:
  ~ScreenStack() override;

  void push(std::unique_ptr<Screen>&& statePtr);
  void close(const Screen* screen);
  void closeAbove(const Screen* screen);
  void clear();
  void sendSignal(Signal signal);
  [[nodiscard]] bool empty() const;

  void update(sf::Time delta);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  std::vector<std::unique_ptr<Screen>> stack;
};

}  // namespace loki::screens
