/*!
 * \file StateMachine.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/System/Time.hpp>
#include "StateIndex.hpp"
#include "State.hpp"
#include "Transition.hpp"

namespace loki::states {

class StateMachine {
 private:
  template <class T>
  using enable_if_enum = std::enable_if_t<std::is_enum_v<T>, bool>;

 public:
  explicit StateMachine(std::size_t size = 0);
  template <class Enum, enable_if_enum<Enum> = true>
  explicit StateMachine(Enum count)
      : StateMachine(static_cast<StateIndex>(count)) {}

  void addState(StateIndex index, State state);
  template <class Enum, enable_if_enum<Enum> = true>
  void addState(Enum e, const State& state) { addState(static_cast<StateIndex>(e), state); }
  void addTransition(Transition transition);
  void shrinkToFit();
  void setCurrentState(StateIndex index) { setCurrentStateWithTrigger(index); }
  template <class Enum, enable_if_enum<Enum> = true>
  void setCurrentState(Enum e) { setCurrentStateWithTrigger(static_cast<StateIndex>(e)); }
  [[nodiscard]] StateIndex getCurrentState() const { return curState; }
  template <class Enum, enable_if_enum<Enum> = true>
  [[nodiscard]] Enum getCurrentState() const { return static_cast<Enum>(curState); }
  void update(sf::Time delta);

 private:
  void setCurrentStateWithTrigger(StateIndex to, const std::function<void()>& onTrigger = nullptr);
  void checkTransitions();

 private:
  StateIndex curState = NONE;
  std::vector<State> states;
  std::vector<Transition> transitions;
};

}
