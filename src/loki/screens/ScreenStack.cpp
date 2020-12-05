/*!
 * \file ScreenStack.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include "ScreenStack.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <loki/common/IterAadapters.hpp>
#include <variant>
#include "Screen.hpp"

namespace loki::screens {

ScreenStack::~ScreenStack() = default;

void ScreenStack::update(sf::Time delta) {
  for (const auto& screen : common::reversed(stack)) {
    if (!screen->update(delta)) {
      break;
    }
  }
  for (const auto& screen : common::reversed(stack)) {
    if (!screen->updateView(delta)) {
      break;
    }
  }
}

void ScreenStack::push(std::unique_ptr<Screen> statePtr) {
  stack.push_back(std::move(statePtr));
}

void ScreenStack::clear() {
  for (const auto& screen : common::reversed(stack)) {
    sendSignal({screen.get(), "close"});
  }
  stack.clear();
}

bool ScreenStack::empty() const {
  return stack.empty();
}

void ScreenStack::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const {
  for (const auto& screen : common::reversed(stack)) {
    if (!screen->render(target, states)) {
      break;
    }
  }
}

void ScreenStack::sendSignal(Signal signal) {
  for (const auto& screen : common::reversed(stack)) {
    if (screen.get() != signal.trigger.origin &&
        !screen->handleSignal(signal)) {
      break;
    }
  }
}

void ScreenStack::close(const Screen* screen) {
  const auto it =
      std::remove_if(stack.begin(), stack.end(),
                     [screen](const auto& ptr) { return ptr.get() == screen; });
  if (it != stack.end()) {
    sendSignal({it->get(), "close"});
    stack.erase(it, stack.end());
  }
}

void ScreenStack::closeAbove(const Screen* screen) {
  const auto it =
      std::find_if(stack.begin(), stack.end(),
                   [screen](const auto& ptr) { return ptr.get() == screen; });
  if (it != stack.end() && it + 1 != stack.end()) {
    for (auto it2 = stack.rbegin(); it2.base() != it + 1; ++it2) {
      sendSignal({it2->get(), "close"});
    }
    stack.erase(it + 1, stack.end());
  }
}

}  // namespace loki::screens