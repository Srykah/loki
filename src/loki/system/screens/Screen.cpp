#include "ScreenStack.hpp"

#include "Screen.hpp"

namespace loki::system {

void Screen::init() {
  ready = true;
}

bool Screen::isReady() const {
  return ready;
}

void Screen::clearScreens() {
  getScreenStack().clear();
}

void Screen::sendSignal(const std::string& signalName) {
  getScreenStack().sendSignal({this, signalName});
}

void Screen::closeScreen(const loki::system::Screen* screen) {
  getScreenStack().close(screen);
}

void Screen::closeScreensAbove() {
  getScreenStack().closeAbove(this);
}

void Screen::closeThisScreen() {
  getScreenStack().close(this);
}

bool Screen::handleSignal(Signal& signal) {
  auto it = signalHandlers.find(signal.trigger);
  if (it == signalHandlers.end()) {
    it = signalHandlers.find({nullptr, signal.trigger.signalName});
  }
  if (it != signalHandlers.end()) {
    return it->second(signal.value);
  } else {
    return true;
  }
}

void Screen::registerSignalHandler(const Signal::Trigger& trigger,
                                   std::function<bool()> fun) {
  signalHandlers.emplace(
      trigger, [fun = std::move(fun)](std::any& args) { return fun(); });
}

void Screen::removeSignalHandler(const Signal::Trigger& trigger) {
  for (auto iter = signalHandlers.begin(); iter != signalHandlers.end();) {
    if (iter->first == trigger) {
      iter = signalHandlers.erase(iter);
    } else {
      ++iter;
    }
  }
}

void Screen::clearAllSignalHandlers() {
  signalHandlers.clear();
}

}  // namespace loki::system
