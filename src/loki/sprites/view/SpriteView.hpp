/*!
 * \file SpriteView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include "AnimationView.hpp"
#include "loki/sprites/model/SpriteData.hpp"
#include "loki/anim/Animated.hpp"

namespace loki::sprites {

class SpriteView : public anim::Animated, public sf::Drawable, public sf::Transformable {
 public:
  SpriteView() = default;
  explicit SpriteView(const SpriteData& data);

  void setData(const SpriteData& _data);

  void setAnim(const std::string& anim);

  void update(sf::Time delta) override;

  void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const override;

 private:
  const SpriteData* data = nullptr;
  std::unique_ptr<AnimationView> view;
};

}
