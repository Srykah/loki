#pragma once

namespace loki::system {

struct InputState {
 public:
  enum Status {
    INACTIVE = 0b00,
    ACTIVE = 0b01,
    CHANGED = 0b10,
    TRIGGERED = CHANGED | ACTIVE,
    ENDED = CHANGED | INACTIVE
  };

 public:
  void update(InputTriggerStatus inputTriggerStatus) {
    status = static_cast<Status>(((isActive() != inputTriggerStatus.isActive) << 1) | inputTriggerStatus.isActive);
    value = inputTriggerStatus.value;
  }

  [[nodiscard]] bool isActive() const { return status & Status::ACTIVE; }
  [[nodiscard]] bool hasChanged() const { return status & Status::CHANGED; }
  [[nodiscard]] explicit operator bool() const { return isActive(); }

 public:
  Status status = Status::INACTIVE;
  float value = 0.f;  // [-1; 1]
};

}  // namespace loki::system