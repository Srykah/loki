loki_create_lib(
  NAME states MODULE core
  HEADERS
  State.hpp
  StateIndex.hpp
  StateMachine.hpp
  Transition.hpp
  SOURCES
  StateMachine.cpp
  PUBLIC_DEPS
  sfml-system
)
