#pragma once

#include <any>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include "Signal.hpp"

namespace loki::system {

class ScreenStack;

class Screen {
 public:
  virtual ~Screen() = default;

  virtual void init();
  [[nodiscard]] bool isReady() const;

  virtual bool update(sf::Time delta) = 0;
  virtual bool render(sf::RenderTarget& target,
                      sf::RenderStates states) const = 0;

 protected:
  // ScreenStack shortcuts
  virtual ScreenStack& getScreenStack() = 0;

  template <typename ScreenType, typename... Args>
  const ScreenType* pushScreen(Args&&... args);
  void closeScreen(const Screen* screen);
  void closeScreensAbove();
  void closeThisScreen();
  void clearScreens();

  // Signals stuff
  void sendSignal(const std::string& signalName);
  template <typename... Args>
  void sendSignal(const std::string& signalName, Args&&... args);

  void registerSignalHandler(const Signal::Trigger& trigger,
                             std::function<bool()> fun);
  template <typename... Args>
  void registerSignalHandler(const Signal::Trigger& trigger,
                             std::function<bool(Args...)> fun);
  template <typename Fun>
  void registerSignalHandler(const Signal::Trigger& trigger, Fun fun);
  void removeSignalHandler(const Signal::Trigger& trigger);
  void clearAllSignalHandlers();

 private:
  bool ready = false;
  std::unordered_map<Signal::Trigger, std::function<bool(std::any&)>>
      signalHandlers;

  friend ScreenStack;
  bool handleSignal(Signal& signal);
};

}  // namespace loki::system

#include "Screen.hxx"
