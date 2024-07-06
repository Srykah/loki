#pragma once

#include <loki/core/reflection/enumMacros.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/runtimeObject/BaseObject.hpp>
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

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(InputTrigger)
};

class KeyTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  sf::Keyboard::Scancode key = sf::Keyboard::Scancode::Unknown;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(KeyTrigger)
};

class MouseButtonTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  sf::Mouse::Button button = sf::Mouse::ButtonCount;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(MouseButtonTrigger)
};

class JoystickAxisTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  sf::Joystick::Axis axis = sf::Joystick::X;
  JoystickAxisDirection direction = JoystickAxisDirection::BOTH;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(JoystickAxisTrigger)
};

class JoystickButtonTrigger : public InputTrigger {
 public:
  InputTriggerStatus getStatus(InputMethod inputMethod) const override;

 private:
  unsigned int button = -1;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(JoystickButtonTrigger)
};

}  // namespace loki::system

LOKI_REFLECTION_ENUM_BEGIN(loki::system::JoystickAxisDirection)
LOKI_REFLECTION_ENUMERATOR(loki::system::JoystickAxisDirection, NEGATIVE)
LOKI_REFLECTION_ENUMERATOR(loki::system::JoystickAxisDirection, BOTH)
LOKI_REFLECTION_ENUMERATOR(loki::system::JoystickAxisDirection, POSITIVE)
LOKI_REFLECTION_ENUM_END()

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::InputTrigger)
LOKI_REFLECTION_CLASS_PARENT(loki::system::InputTrigger, loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::InputTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::KeyTrigger)
LOKI_REFLECTION_CLASS_FIELD(loki::system::KeyTrigger, key)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::KeyTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::MouseButtonTrigger)
LOKI_REFLECTION_CLASS_FIELD(loki::system::MouseButtonTrigger, button)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::MouseButtonTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::JoystickAxisTrigger)
LOKI_REFLECTION_CLASS_FIELD(loki::system::JoystickAxisTrigger, axis)
LOKI_REFLECTION_CLASS_FIELD(loki::system::JoystickAxisTrigger, direction)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::JoystickAxisTrigger)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::InputTrigger, loki::system::JoystickButtonTrigger)
LOKI_REFLECTION_CLASS_FIELD(loki::system::JoystickButtonTrigger, button)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::JoystickButtonTrigger)