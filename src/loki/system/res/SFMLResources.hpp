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
  void loadImpl(const std::filesystem::path& path) override { data.loadFromFile(path.string()); }

 private:
  T data;
};

class FontResource final : public SFMLResource<sf::Font> {};
class TextureResource final : public SFMLResource<sf::Texture> {};
class SoundBufferResource final : public SFMLResource<sf::SoundBuffer> {};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN(loki::system::FontResource)
LOKI_REFLECTION_CLASS_END()
LOKI_REFLECTION_CLASS_BEGIN(loki::system::TextureResource)
LOKI_REFLECTION_CLASS_END()
LOKI_REFLECTION_CLASS_BEGIN(loki::system::SoundBufferResource)
LOKI_REFLECTION_CLASS_END()