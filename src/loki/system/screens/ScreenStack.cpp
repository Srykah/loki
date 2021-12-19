/*!
 * \file ScreenStack.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include "ScreenStack.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <loki/core/utils/IterAdapters.hpp>
#include <variant>
#include "Screen.hpp"

namespace loki::screens {

ScreenStack::~ScreenStack() = default;

void ScreenStack::update(sf::Time delta) {
  // init new screens in order
  // new screens may be added while doing this
  for (std::size_t i{0u}; i < stack.size(); ++i) {
    if (!stack[i]->isReady()) {
      stack[i]->init();
    }
  }

  // now update in reverse order and stop if told to
  for (int i(stack.size() - 1); i >= 0; --i) {
    if (!stack[i]->update(delta)) {
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
  for (int i(stack.size() - 1); i >= 0; --i) {
    if (stack[i].get() == signal.trigger.origin) {
      continue;
    }
    if (!stack[i]->handleSignal(signal)) {
      break;
    }
  }
}

void ScreenStack::close(const Screen* screen) {
  const auto pred = [screen](const auto& ptr) { return ptr.get() == screen; };
  if (std::find_if(stack.begin(), stack.end(), pred) != stack.end()) {
    sendSignal({screen, "close"});
    // stack could have been changed, search again
    stack.erase(std::remove_if(stack.begin(), stack.end(), pred), stack.end());
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
