#pragma once

namespace loki::graphics {

// Origin

namespace details {
#define LOKI_ANIMATION_CONCEPT(Stuff, Type)                                   \
  template <class T>                                                          \
  concept hasGet##Stuff = requires { Type{std::declval<T>().get##Stuff()}; }; \
  template <class T>                                                          \
  concept hasSet##Stuff = requires { std::declval<T>().set##Stuff(std::declval<Type>()); };
LOKI_ANIMATION_CONCEPT(Origin, sf::Vector2f)
LOKI_ANIMATION_CONCEPT(Position, sf::Vector2f)
LOKI_ANIMATION_CONCEPT(Rotation, float)
LOKI_ANIMATION_CONCEPT(Scale, float)
LOKI_ANIMATION_CONCEPT(Color, sf::Color)
LOKI_ANIMATION_CONCEPT(FillColor, sf::Color)
LOKI_ANIMATION_CONCEPT(TextureRect, sf::IntRect)
#undef LOKI_ANIMATION_CONCEPT
}  // namespace details

template <typename T>
sf::Vector2f getOrigin(T& animated) {
  if constexpr (details::hasGetOrigin<T>) {
    return animated.getOrigin();
  }
  return sf::Vector2f{};
}

template <typename T>
void setOrigin(T& animated, sf::Vector2f origin) {
  if constexpr (details::hasSetOrigin<T>) {
    animated.setOrigin(origin);
  }
}

// Position

template <typename T>
sf::Vector2f getPosition(T& animated) {
  if constexpr (details::hasGetPosition<T>) {
    return animated.getPosition();
  }
  return sf::Vector2f{};
}

template <typename T>
void setPosition(T& animated, sf::Vector2f position) {
  if constexpr (details::hasSetPosition<T>) {
    animated.setPosition(position);
  }
}

// Rotation

template <typename T>
float getRotation(T& animated) {
  if constexpr (details::hasGetRotation<T>) {
    return animated.getRotation();
  }
  return 0.f;
}

template <typename T>
void setRotation(T& animated, float rotation) {
  if constexpr (details::hasSetRotation<T>) {
    animated.setRotation(rotation);
  }
}

// Scale

template <typename T>
sf::Vector2f getScale(T& animated) {
  if constexpr (details::hasGetScale<T>) {
    return animated.getScale();
  }
  return sf::Vector2f{};
}

template <typename T>
void setScale(T& animated, sf::Vector2f scale) {
  if constexpr (details::hasSetScale<T>) {
    animated.setScale(scale);
  }
}

// Color

template <typename T>
sf::Color getColor(T& animated) {
  if constexpr (details::hasGetFillColor<T>) {
    return animated.getFillColor();
  } else if constexpr (details::hasGetColor<T>) {
    return animated.getColor();
  }
  return sf::Color{};
}

template <typename T>
void setColor(T& animated, sf::Color color) {
  if constexpr (details::hasSetFillColor<T>) {
    animated.setFillColor(color);
  } else if constexpr (details::hasSetColor<T>) {
    animated.setColor(color);
  }
}

// TextureRect

template <typename T>
sf::IntRect getTextureRect(T& animated) {
  if constexpr (details::hasGetTextureRect<T>) {
    return animated.getTextureRect();
  }
  return sf::IntRect{};
}

template <typename T>
void setTextureRect(T& animated, sf::IntRect textureRect) {
  if constexpr (details::hasSetTextureRect<T>) {
    animated.setTextureRect(textureRect);
  }
}

}  // namespace loki::graphics
