/*!
 * \file Screen.inl
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

namespace loki::screens {

template <typename... Args>
void Screen::registerSignalHandler(const Signal::Trigger& trigger,
                                   std::function<bool(Args...)> fun) {
  signalHandlers.emplace(trigger, [fun = std::move(fun)](std::any args) {
    return std::apply(fun, std::any_cast<std::tuple<Args...>>(args));
  });
}

template <typename Fun>
void Screen::registerSignalHandler(const Signal::Trigger& trigger, Fun fun) {
  registerSignalHandler(trigger, std::function{fun});
}

}  // namespace loki::screens
