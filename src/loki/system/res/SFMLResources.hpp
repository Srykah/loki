#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <loki/system/res/Resource.hpp>

namespace loki::system {

template <class T>
class SFMLResource : public Resource<T> {
 public:
  [[nodiscard]] const T& getData() const override { return data; }

 protected:
  [[nodiscard]] bool load(const std::filesystem::path& path) override { return data.loadFromFile(path.string()); }

 private:
  T data;
};

class TextureResource final : public SFMLResource<sf::Texture> {};
class SoundBufferResource final : public SFMLResource<sf::SoundBuffer> {};

class FontResource final : public Resource<sf::Font> {
 public:
  [[nodiscard]] const sf::Font& getData() const override { return data; }

 protected:
  [[nodiscard]] bool load(const std::filesystem::path& path) override { return data.openFromFile(path.string()); }

 private:
  sf::Font data;
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN(loki::system::TextureResource)
LOKI_REFLECTION_CLASS_END()
LOKI_REFLECTION_CLASS_BEGIN(loki::system::SoundBufferResource)
LOKI_REFLECTION_CLASS_END()
LOKI_REFLECTION_CLASS_BEGIN(loki::system::FontResource)
LOKI_REFLECTION_CLASS_END()