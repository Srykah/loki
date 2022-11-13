#pragma once

#include <SFML/Graphics/Transformable.hpp>

#include <loki/core/reflection/BaseObject.hpp>

namespace loki::system {

class SceneNode : public core::BaseObject, public sf::Transformable {
 public:
  explicit SceneNode(SceneNode* parent = nullptr,
                     const sf::Transformable& trs = sf::Transformable{},
                     const sf::FloatRect& bounds = sf::FloatRect{});
  ~SceneNode() override = default;

  [[nodiscard]] const core::TypeInfo& getTypeInfo() const override;

  void setTrs(const sf::Transformable& trs);

  [[nodiscard]] sf::Transform getGlobalTransform() const;
  [[nodiscard]] sf::Vector2f getGlobalPosition() const;
  [[nodiscard]] float getGlobalRotation() const;
  [[nodiscard]] sf::Vector2f getGlobalScale() const;

  [[nodiscard]] const sf::FloatRect& getLocalBounds() const;
  [[nodiscard]] sf::FloatRect getGlobalBounds() const;

 protected:
  SceneNode* parent = nullptr;
  sf::FloatRect bounds;
};

}  // namespace loki::system