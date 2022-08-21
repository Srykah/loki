#include "StateMachine.hpp"

namespace loki::core {

StateMachine::StateMachine(std::size_t size) {
  states.reserve(size);
  transitions.reserve(size * size / 2);  // estimate
}

void StateMachine::addState(StateIndex index, State state) {
  if (index >= states.size()) {
    states.resize(index + 1);
  }
  states[index] = std::move(state);
}

void StateMachine::addTransition(Transition transition) {
  transitions.push_back(std::move(transition));
}

void StateMachine::shrinkToFit() {
  states.shrink_to_fit();
  transitions.shrink_to_fit();
}

void StateMachine::update(sf::Time delta) {
  checkTransitions();
  if (curState != NONE && states.at(curState).onUpdate) {
    states.at(curState).onUpdate(delta);
  }
}

void StateMachine::checkTransitions() {
  for (auto& transition : transitions) {
    if ((transition.from == ANY || transition.from == curState) &&
        transition.isActive()) {
      setCurrentStateWithTrigger(transition.to, transition.onTrigger);
      return;
    }
  }
}

void StateMachine::setCurrentStateWithTrigger(
    StateIndex to,
    const std::function<void()>& onTrigger) {
  if (curState != NONE && states.at(curState).onLeave) {
    states.at(curState).onLeave();
  }
  if (onTrigger) {
    onTrigger();
  }
  curState = to;
  if (states.at(curState).onEnter) {
    states.at(curState).onEnter();
  }
}

}  // namespace loki::core
