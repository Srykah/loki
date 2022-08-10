/*!
 * \file InputState.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::input {

struct InputState {
  enum Status {
    INACTIVE = 0b00,
    TRIGGERED = 0b11,
    ACTIVE = 0b01,
    ENDED = 0b10
  } status = Status::INACTIVE;

  float value = 0.f;  // [-1; 1]

  [[nodiscard]] bool isActive() const {
    return status == Status::TRIGGERED || status == Status::ACTIVE;
  }
  explicit operator bool() const { return isActive(); }
  [[nodiscard]] bool hasChanged() const {
    return status == Status::TRIGGERED || status == Status::ENDED;
  }
};

}  // namespace loki::input