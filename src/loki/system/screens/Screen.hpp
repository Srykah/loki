/*!
 * \file State.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <any>
#include <unordered_map>
#include "Signal.hpp"

namespace loki::screens {

class ScreenStack;

class Screen {
 public:
  explicit Screen(ScreenStack& stack);
  virtual ~Screen() = default;

  virtual void init();
  [[nodiscard]] bool isReady() const;

  virtual bool update(sf::Time delta) = 0;
  virtual bool updateView(sf::Time delta) = 0;
  virtual bool render(sf::RenderTarget& target,
                      sf::RenderStates states) const = 0;

  void registerSignalHandler(const Signal::Trigger& trigger,
                             std::function<bool()> fun);
  template <typename... Args>
  void registerSignalHandler(const Signal::Trigger& trigger,
                             std::function<bool(Args...)> fun);
  template <typename Fun>
  void registerSignalHandler(const Signal::Trigger& trigger, Fun fun);
  void removeSignalHandler(const Signal::Trigger& trigger);
  void clearAllSignalHandlers();
  bool handleSignal(Signal& signal);

 private:
  bool ready;
  std::unordered_map<Signal::Trigger, std::function<bool(std::any)>>
      signalHandlers;

 protected:
  ScreenStack& stack;
};

}  // namespace loki::screens

#include "impl/Screen.hxx"
