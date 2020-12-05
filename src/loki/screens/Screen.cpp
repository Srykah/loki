/*!
 * \file Screen.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Screen.hpp"

namespace loki::screens {

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
      trigger, [fun = std::move(fun)](std::any args) { return fun(); });
}

void Screen::removeSignalHandler(const Signal::Trigger& trigger) {
  for(auto iter = signalHandlers.begin(); iter != signalHandlers.end(); ) {
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

}
