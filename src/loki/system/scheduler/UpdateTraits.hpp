#pragma once

#include <utility>

#include <SFML/System/Time.hpp>

#include <loki/system/scheduler/UpdateSteps.hpp>

namespace loki::system {

template <class T, UpdateStep step>
concept HasUpdateStep = requires { std::declval<T>().update(sf::Time{}, UpdateStepTag<step>{}); };

template <class T>
concept HasDefaultUpdateStep = requires { std::declval<T>().update(sf::Time{}); };

struct BaseUpdateTraits {
  virtual ~BaseUpdateTraits() = default;
  virtual bool hasUpdateStep(UpdateStep step) const = 0;
  virtual void runUpdateStep(void* obj, sf::Time dt, UpdateStep step) const = 0;
  // static constexpr auto UpdateStepSequence = std::make_index_sequence<static_cast<std::size_t>(UpdateStep::Count)>();
};

template <class T>
struct UpdateTraits final : public BaseUpdateTraits {
  bool hasUpdateStep(UpdateStep step) const override {
    bool support[] = {
#define LOKI_GET_SUPPORT(StepName, ...) HasUpdateStep<T, UpdateStep::StepName>,
        LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_GET_SUPPORT)
#undef LOKI_GET_SUPPORT
    };
    support[static_cast<std::size_t>(UpdateStep::Default)] |= HasDefaultUpdateStep<T>;
    return support[static_cast<std::size_t>(step)];
  }

  void runUpdateStep(void* obj, sf::Time dt, UpdateStep step) const override {
    using Signature = void(T&, sf::Time);
    constexpr Signature* methods[] = {
#define LOKI_CREATE_METHOD(StepName, ...)                                                 \
  [](T& t, sf::Time dt) {                                                                 \
    if constexpr (HasUpdateStep<T, UpdateStep::StepName>)                                 \
      t.update(dt, UpdateSteps::StepName{});                                              \
    if constexpr (UpdateStep::StepName == UpdateStep::Default && HasDefaultUpdateStep<T>) \
      t.update(dt);                                                                       \
  },
        LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_CREATE_METHOD)
#undef LOKI_CREATE_METHOD
    };
    methods[static_cast<std::size_t>(step)](*static_cast<T*>(obj), dt);
  }

#if 0
  bool hasUpdateStep(UpdateStep step) const override { return hasUpdateStepInternal(step, UpdateStepSequence); }
  void runUpdateStep(void* obj, sf::Time dt, UpdateStep step) const override {
    runUpdateStepInternal(*static_cast<T*>(obj), dt, static_cast<std::size_t>(step), UpdateStepSequence);
  }

 private:
  template <std::size_t... Is>
  static bool hasUpdateStepInternal(UpdateStep step, std::integer_sequence<std::size_t, Is...>) {
    constexpr bool arFuncs[] = {(HasUpdateStep<T, static_cast<UpdateStep>(Is)> ||
                                 (static_cast<UpdateStep>(Is) == UpdateStep::Default && HasDefaultUpdateStep<T>))...};
    return arFuncs[std::to_underlying(step)];
  }

  template <std::size_t First, std::size_t... Is>
  static void runUpdateStepInternal(T& t,
                                    sf::Time dt,
                                    std::size_t step,
                                    std::integer_sequence<std::size_t, First, Is...>) {
    if (step == 0) {
      if constexpr (HasUpdateStep<T, static_cast<UpdateStep>(First)>) {
        t.update(dt, UpdateStepTag<static_cast<UpdateStep>(First)>{});
      }
    } else {
      runUpdateStepInternal(t, step - 1, std::integer_sequence<std::size_t, Is...>{});
    }
  }
#endif
};

}  // namespace loki::system
