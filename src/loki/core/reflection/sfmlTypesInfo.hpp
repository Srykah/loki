#pragma once

#include <cassert>

#include <SFML/Graphics.hpp>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/enumMacros.hpp>

#define LOKI_REFLECTION_CLASS_FIELD_SF_TYPE(Class, Field) \
  std::remove_cvref_t<decltype(std::declval<Class>().get##Field())>
#define LOKI_REFLECTION_CLASS_FIELD_SF_GETTER_SETTER(Class, Field)                            \
  LOKI_REFLECTION_CLASS_FIELD_CUSTOM(                                                         \
      getTypeInfo<LOKI_REFLECTION_CLASS_FIELD_SF_TYPE(Class, Field)>(), #Field, false,        \
      [](void* obj) -> TmpObj {                                                               \
        return TmpObj::makeOwned<LOKI_REFLECTION_CLASS_FIELD_SF_TYPE(Class, Field)>(          \
            details::to<Class>(obj).get##Field());                                            \
      },                                                                                      \
      [](const void* obj) -> ConstTmpObj {                                                    \
        return ConstTmpObj::makeOwned<LOKI_REFLECTION_CLASS_FIELD_SF_TYPE(Class, Field)>(     \
            details::to<Class>(obj).get##Field());                                            \
      },                                                                                      \
      [](void* obj, void* data) {                                                             \
        details::to<Class>(obj).set##Field(                                                   \
            std::move(details::to<LOKI_REFLECTION_CLASS_FIELD_SF_TYPE(Class, Field)>(data))); \
      })
#define REFLECTION_CLASS_SF_TRANSFORMABLE(Class)                                                                    \
  LOKI_REFLECTION_CLASS_FIELD_CUSTOM(                                                                               \
      getTypeInfo<sf::Transformable>(), "transform", false,                                                         \
      [](void* obj) -> TmpObj {                                                                                     \
        return TmpObj::fromPtrNonOwned(details::from(static_cast<sf::Transformable&>(details::to<Class>(obj))));    \
      },                                                                                                            \
      [](const void* obj) -> ConstTmpObj {                                                                          \
        return ConstTmpObj::fromPtrNonOwned(                                                                        \
            details::from(static_cast<const sf::Transformable&>(details::to<Class>(obj))));                         \
      },                                                                                                            \
      [](void* obj, void* data) {                                                                                   \
        static_cast<sf::Transformable&>(details::to<Class>(obj)) = std::move(details::to<sf::Transformable>(data)); \
      })

LOKI_REFLECTION_CLASS_BEGIN(sf::Vector2f)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector2f, x)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector2f, y)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::Vector2i)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector2i, x)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector2i, y)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::Vector2u)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector2u, x)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector2u, y)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::Vector3f)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector3f, x)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector3f, y)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector3f, z)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::Vector3i)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector3i, x)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector3i, y)
LOKI_REFLECTION_CLASS_FIELD(sf::Vector3i, z)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::Transformable)
LOKI_REFLECTION_CLASS_FIELD_SF_GETTER_SETTER(sf::Transformable, Origin)
LOKI_REFLECTION_CLASS_FIELD_SF_GETTER_SETTER(sf::Transformable, Position)
LOKI_REFLECTION_CLASS_FIELD_SF_GETTER_SETTER(sf::Transformable, Rotation)
LOKI_REFLECTION_CLASS_FIELD_SF_GETTER_SETTER(sf::Transformable, Scale)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::Color)
LOKI_REFLECTION_CLASS_FIELD(sf::Color, r)
LOKI_REFLECTION_CLASS_FIELD(sf::Color, g)
LOKI_REFLECTION_CLASS_FIELD(sf::Color, b)
LOKI_REFLECTION_CLASS_FIELD(sf::Color, a)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::CircleShape)
REFLECTION_CLASS_SF_TRANSFORMABLE(sf::CircleShape)
LOKI_REFLECTION_CLASS_FIELD_SF_GETTER_SETTER(sf::CircleShape, Radius)
LOKI_REFLECTION_CLASS_FIELD_SF_GETTER_SETTER(sf::CircleShape, FillColor)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(sf::Time)
LOKI_REFLECTION_CLASS_FIELD_CUSTOM(
    getTypeInfo<float>(),
    "seconds",
    false,
    [](void* obj) -> TmpObj { return TmpObj::makeOwned<float>(details::to<sf::Time>(obj).asSeconds()); },
    [](const void* obj) -> ConstTmpObj {
      return ConstTmpObj::makeOwned<float>(details::to<const sf::Time>(obj).asSeconds());
    },
    [](void* obj, void* data) { details::to<sf::Time>(obj) = sf::seconds(details::to<float>(data)); })
LOKI_REFLECTION_CLASS_END()

#undef REFLECTION_CLASS_FIELD_SF_GETTER_SETTER
#undef REFLECTION_CLASS_FIELD_SF_TYPE

LOKI_REFLECTION_ENUM_BEGIN(sf::Joystick::Axis)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, X)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, Y)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, Z)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, R)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, U)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, V)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, PovX)
LOKI_REFLECTION_ENUMERATOR(sf::Joystick::Axis, PovY)
LOKI_REFLECTION_ENUM_END()

LOKI_REFLECTION_ENUM_BEGIN(sf::Mouse::Button)
LOKI_REFLECTION_ENUMERATOR(sf::Mouse::Button, Left)
LOKI_REFLECTION_ENUMERATOR(sf::Mouse::Button, Right)
LOKI_REFLECTION_ENUMERATOR(sf::Mouse::Button, Middle)
LOKI_REFLECTION_ENUMERATOR(sf::Mouse::Button, XButton1)
LOKI_REFLECTION_ENUMERATOR(sf::Mouse::Button, XButton2)
LOKI_REFLECTION_ENUMERATOR(sf::Mouse::Button, ButtonCount)
LOKI_REFLECTION_ENUM_END()

LOKI_REFLECTION_ENUM_BEGIN(sf::Keyboard::Scancode)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Unknown)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, A)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, B)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, C)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, D)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, E)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, G)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, H)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, I)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, J)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, K)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, L)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, M)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, N)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, O)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, P)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Q)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, R)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, S)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, T)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, U)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, V)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, W)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, X)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Y)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Z)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num1)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num2)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num3)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num4)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num5)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num6)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num7)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num8)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num9)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Num0)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Enter)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Escape)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Backspace)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Tab)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Space)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Hyphen)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Equal)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LBracket)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, RBracket)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Backslash)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Semicolon)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Apostrophe)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Grave)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Comma)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Period)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Slash)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F1)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F2)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F3)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F4)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F5)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F6)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F7)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F8)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F9)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F10)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F11)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F12)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F13)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F14)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F15)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F16)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F17)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F18)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F19)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F20)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F21)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F22)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F23)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, F24)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, CapsLock)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, PrintScreen)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, ScrollLock)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Pause)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Insert)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Home)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, PageUp)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Delete)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, End)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, PageDown)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Right)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Left)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Down)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Up)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumLock)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumpadDivide)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumpadMultiply)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumpadMinus)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumpadPlus)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumpadEqual)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumpadEnter)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NumpadDecimal)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad1)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad2)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad3)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad4)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad5)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad6)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad7)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad8)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad9)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Numpad0)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, NonUsBackslash)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Application)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Execute)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, ModeChange)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Help)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Menu)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Select)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Redo)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Undo)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Cut)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Copy)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Paste)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, VolumeMute)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, VolumeUp)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, VolumeDown)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, MediaPlayPause)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, MediaStop)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, MediaNextTrack)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, MediaPreviousTrack)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LControl)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LShift)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LAlt)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LSystem)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, RControl)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, RShift)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, RAlt)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, RSystem)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Back)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Forward)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Refresh)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Stop)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Search)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, Favorites)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, HomePage)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LaunchApplication1)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LaunchApplication2)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LaunchMail)
LOKI_REFLECTION_ENUMERATOR(sf::Keyboard::Scancode, LaunchMediaSelect)
LOKI_REFLECTION_ENUM_END()
