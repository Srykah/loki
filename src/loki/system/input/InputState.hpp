#pragma once

namespace loki::system {

struct InputState {
 public:
  void update(InputTriggerStatus inputTriggerStatus) {
    // order is important!
    hasChanged = (inputTriggerStatus.isActive != isActive);
    isActive = inputTriggerStatus.isActive;
    value = inputTriggerStatus.value;
  }

  [[nodiscard]] explicit operator bool() const { return isActive; }

  bool hasChanged = false;
  bool isActive = false;
  float value = 0.f;  // [-1; 1]
};

}  // namespace loki::system