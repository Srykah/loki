#pragma once

#include "ShapeAnimationData.hpp"

namespace loki::graphics {

template <typename T>
class ShapeAnimator {
 public:
  void setAnimated(T& animated);
  void resetAnimated();

  void setData(const ShapeAnimationData& data);
  void resetData();

  void start();
  void setTime(sf::Time time);
  void update(sf::Time delta);
  [[nodiscard]] bool hasEnded() const;
  void pause();
  void unpause();
  [[nodiscard]] bool isPaused() const;
  void stop();

 private:
  void updateInternal();

  struct ShapeInitValues {
    sf::Vector2f origin;
    sf::Vector2f position;
    float rotation = 0.f;
    sf::Vector2f scale;
    sf::Color color;
  };

  T* animated = nullptr;
  ShapeInitValues initValues;
  const ShapeAnimationData* data = nullptr;
  sf::Time elapsedTime;
  bool paused = false;
};

}  // namespace loki::graphics

#include "ShapeAnimator.hxx"
