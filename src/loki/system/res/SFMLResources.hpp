/*!
 * \file SFMLResources.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Resource.hpp"

namespace loki::res {

template <class T>
class SFMLResource : public Resource {
 public:
  using DataType = T;

 public:
  explicit SFMLResource(std::filesystem::path path)
      : Resource(std::move(path)) {}
  ~SFMLResource() override = default;

  void loadImpl(const std::filesystem::path& path,
                ResourceHolder& resourceHolder) override {
    data.loadFromFile(path.string());
  };

  void unloadImpl() override {
    // todo
  }

  [[nodiscard]] const T& getData() const { return data; }

 protected:
  T data;
};

class FontResource : public SFMLResource<sf::Font> {
 public:
  explicit FontResource(std::filesystem::path path)
      : SFMLResource(std::move(path)) {}
};

class TextureResource : public SFMLResource<sf::Texture> {
 public:
  explicit TextureResource(std::filesystem::path path)
      : SFMLResource(std::move(path)) {}
};

class SoundBufferResource : public SFMLResource<sf::SoundBuffer> {
 public:
  explicit SoundBufferResource(std::filesystem::path path)
      : SFMLResource(std::move(path)) {}
};

}  // namespace loki::res
