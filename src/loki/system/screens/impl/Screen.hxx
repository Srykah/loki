/*!
 * \file Screen.inl
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

namespace loki::screens {

template <typename... Args>
void Screen::sendSignal(const std::string& signalName, Args&&... args) {
  std::any value{std::make_tuple(std::forward<Args>(args)...)};
  getScreenStack().sendSignal({this, signalName, value});
}

template <typename ScreenType, typename... Args>
const ScreenType* Screen::pushScreen(Args&&... args) {
  auto ptr = std::make_unique<ScreenType>(std::forward<Args>(args)...);
  auto rawPtr = ptr.get();
  getScreenStack().push(std::move(ptr));
  return rawPtr;
}

template <typename... Args>
void Screen::registerSignalHandler(const Signal::Trigger& trigger,
                                   std::function<bool(Args...)> fun) {
  signalHandlers.emplace(trigger, [fun = std::move(fun)](std::any& args) {
    return std::apply(fun, std::any_cast<std::tuple<Args...>>(args));
  });
}

template <typename Fun>
void Screen::registerSignalHandler(const Signal::Trigger& trigger, Fun fun) {
  registerSignalHandler(trigger, std::function{fun});
}

}  // namespace loki::screens
