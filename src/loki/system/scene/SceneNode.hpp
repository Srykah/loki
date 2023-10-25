#pragma once

#include <SFML/Graphics/Transformable.hpp>

#include <loki/core/reflection/BaseObject.hpp>

namespace loki::system {
class SceneNode;
}

namespace loki::core {
template <>
const TypeInfo* getTypeInfo<::loki::system::SceneNode>();
}

namespace loki::system {

class SceneNode : public core::BaseObject, public sf::Transformable {
 public:
  explicit SceneNode(SceneNode* parent = nullptr,
                     const sf::Transformable& trs = sf::Transformable{},
                     const sf::FloatRect& bounds = sf::FloatRect{});
  ~SceneNode() override = default;

  [[nodiscard]] const core::TypeInfo* getTypeInfo() const override { return ::loki::core::getTypeInfo<SceneNode>(); }

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

namespace loki::core {

template <>
const TypeInfo* getTypeInfo<::loki::system::SceneNode>() {
  static TypeInfo typeInfo{.index = typeid(::loki::system::SceneNode),
                           .name = "loki::system::SceneNode",
                           .description = "A node in the scene's transform graph",
                           .parents =
                               {
                                   getTypeInfo<core::BaseObject>(),
                                   getTypeInfo<sf::Transformable>(),
                               },
                           .fields = {FieldInfo{.type = getTypeInfo<sf::FloatRect>(), .name = "bounds"}}};
  return &typeInfo;
}

}  // namespace loki::core