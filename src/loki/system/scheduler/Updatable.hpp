#pragma once

#include <type_traits>

#include <SFML/System/Time.hpp>

#include <loki/system/scheduler/UpdateTraits.hpp>

namespace loki::system {

struct Updatable {
  virtual ~Updatable() = default;

#define LOKI_UPDATABLE_METHODS(Step) \
  virtual void on##Step(sf::Time delta) {}
  LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_UPDATABLE_METHODS)
#undef LOKI_UPDATABLE_METHODS
};

template <class T>
concept IsUpdatable = std::is_base_of_v<Updatable, T>;

template <IsUpdatable T>
class UpdateTraits<T> : public BaseUpdateTraits {
 public:
  ~UpdateTraits() override = default;
  [[nodiscard]] bool hasUpdateStep(UpdateStep step) const override {
#define LOKI_UPDATE_TRAITS_UPDATABLE_HAS_STEP(Step) \
  if (step == UpdateStep::Step)                     \
    return !std::is_same_v<decltype(T::on##Step), decltype(Updatable::on##Step)>;
    LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_UPDATE_TRAITS_UPDATABLE_HAS_STEP)
#undef LOKI_UPDATE_TRAITS_UPDATABLE
    return false;
  }
  void runUpdateStep(void* obj, sf::Time delta, UpdateStep step) const override {
#define LOKI_UPDATE_TRAITS_UPDATABLE_RUN_STEP(Step) \
  if (step == UpdateStep::Step)                     \
    static_cast<T*>(obj)->on##Step(delta);
    LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_UPDATE_TRAITS_UPDATABLE_RUN_STEP)
#undef LOKI_UPDATE_TRAITS_UPDATABLE
  }
};

}  // namespace loki::system