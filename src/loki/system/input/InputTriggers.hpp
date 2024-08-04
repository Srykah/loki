#pragma once

#include <loki/core/reflection/enumMacros.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/system/input/InputMethod.hpp>

namespace loki::system {

struct InputTriggerStatus {
  bool isActive = false;
  float value = 0.f;

  InputTriggerStatus() = default;
  InputTriggerStatus(bool isActive) : isActive(isActive), value(static_cast<float>(isActive)) {}
  InputTriggerStatus(bool isActive, float value) : isActive(isActive), value(value) {}
};

enum class JoystickAxisDirection { NEGATIVE = -1, BOTH = 0, POSITIVE = +1 };

class InputTrigger : public core::BaseObject {
 public:
  virtual InputTriggerStatus getStatus(InputMethod inputMethod) const = 0;

  LOKI_RTTI_CLASS_DECLARE(InputTrigger)
};

class KeyTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  sf::Keyboard::Scancode key = sf::Keyboard::Scancode::Unknown;

  LOKI_RTTI_CLASS_DECLARE(KeyTrigger)
};

class MouseButtonTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  sf::Mouse::Button button = sf::Mouse::ButtonCount;

  LOKI_RTTI_CLASS_DECLARE(MouseButtonTrigger)
};

class JoystickAxisTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  sf::Joystick::Axis axis = sf::Joystick::X;
  JoystickAxisDirection direction = JoystickAxisDirection::BOTH;

  LOKI_RTTI_CLASS_DECLARE(JoystickAxisTrigger)
};

class JoystickButtonTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  unsigned int button = -1;

  LOKI_RTTI_CLASS_DECLARE(JoystickButtonTrigger)
};

}  // namespace loki::system

LOKI_REFLECTION_ENUM_BEGIN(loki::system::JoystickAxisDirection)
LOKI_REFLECTION_ENUMERATOR(NEGATIVE)
LOKI_REFLECTION_ENUMERATOR(BOTH)
LOKI_REFLECTION_ENUMERATOR(POSITIVE)
LOKI_REFLECTION_ENUM_END()

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::InputTrigger)
LOKI_REFLECTION_CLASS_PARENT(loki::system::InputTrigger, loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::InputTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::KeyTrigger)
LOKI_REFLECTION_CLASS_FIELD(key)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::KeyTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::MouseButtonTrigger)
LOKI_REFLECTION_CLASS_FIELD(button)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::MouseButtonTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::JoystickAxisTrigger)
LOKI_REFLECTION_CLASS_FIELD(axis)
LOKI_REFLECTION_CLASS_FIELD(direction)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::JoystickAxisTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::JoystickButtonTrigger)
LOKI_REFLECTION_CLASS_FIELD(button)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::JoystickButtonTrigger)