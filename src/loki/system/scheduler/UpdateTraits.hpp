#pragma once

#include <map>

#include <SFML/System/Time.hpp>

#include <loki/system/scheduler/UpdateSteps.hpp>

namespace loki::system {

class BaseUpdateTraits {
 public:
  virtual ~BaseUpdateTraits() = default;
  [[nodiscard]] virtual bool hasUpdateStep(UpdateStep step) const = 0;
  virtual void runUpdateStep(void* obj, sf::Time dt, UpdateStep step) const = 0;
};

template <class T>
class UpdateTraits;

template <class T>
class UpdateTraits : public BaseUpdateTraits {
 public:
  ~UpdateTraits() override = default;
  [[nodiscard]] bool hasUpdateStep(UpdateStep step) const override { return false; }
  void runUpdateStep(void* obj, sf::Time delta, UpdateStep step) const override {}
};

}  // namespace loki::system

#define LOKI_UPDATE_TRAITS_BEGIN(Updatable)                                               \
  template <>                                                                             \
  class loki::system::UpdateTraits<Updatable> : public ::loki::system::BaseUpdateTraits { \
    using MyUpdatable = Updatable;                                                        \
    std::map<::loki::system::UpdateStep, void (MyUpdatable::*)(sf::Time)> updateSteps = {
#define LOKI_UPDATE_TRAITS_METHOD(Step, Method) {::loki::system::UpdateStep::Step, &MyUpdatable::Method},

#define LOKI_UPDATE_TRAITS_END()                                                                  \
  }                                                                                               \
  ;                                                                                               \
                                                                                                  \
 public:                                                                                          \
  bool hasUpdateStep(::loki::system::UpdateStep step) const override {                            \
    return updateSteps.contains(step);                                                            \
  }                                                                                               \
  void runUpdateStep(void* obj, sf::Time delta, ::loki::system::UpdateStep step) const override { \
    (static_cast<MyUpdatable*>(obj)->*(updateSteps.at(step)))(delta);                             \
  }                                                                                               \
  }                                                                                               \
  ;
