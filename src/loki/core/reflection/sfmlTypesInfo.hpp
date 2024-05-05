#pragma once

#include <cassert>

#include <SFML/Graphics.hpp>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/classMacros.hpp>

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
