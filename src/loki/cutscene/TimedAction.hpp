/*!
 * \file TimedAction.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::cutscene {

template <typename Animated>
TimedAction<Animated> {
 public:
  using TimedFuctions = std::function<void(Animated&, double)>;

 public:
  explicit TimedAction(sf::Time duration = sf::Time::Zero);
  virtual ~TimedAction() = default;

  void update(sf::Time delta);
  virtual void apply(Animated & animated);
  bool hasEnded() const;

 protected:
  sf::Time currentTime;
  sf::Time duration;
}

}  // namespace loki::cutscene

#include "TimedAction.inl"
