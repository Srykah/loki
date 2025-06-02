#pragma once

namespace loki::system {

enum class LifeCycleStep { Created, LoadingDependencies, DependenciesLoaded, Ready, Active, Deinit };

class WithLifeCycle {
 public:
  virtual ~WithLifeCycle() = default;
  virtual void onBeginInit() {}
  virtual void onDependenciesLoaded() {}
  virtual void onEndInit() {}
  virtual void onActivate() {}
  virtual void onDeactivate() {}
  virtual void onBeginDeinit() {}
  virtual void onEndDeinit() {}

  void setLifeCycleStep(LifeCycleStep step) { lifeCycleStep = step; }
  [[nodiscard]] LifeCycleStep getLifeCycleStep() const { return lifeCycleStep; }

 protected:
  LifeCycleStep lifeCycleStep = LifeCycleStep::Created;
};

}  // namespace loki::system