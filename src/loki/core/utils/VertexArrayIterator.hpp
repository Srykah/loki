#pragma once

#include <SFML/Graphics/VertexArray.hpp>

namespace loki::core {

class VertexArrayIterator {
 public:
  VertexArrayIterator(sf::VertexArray& va, std::size_t index);

  VertexArrayIterator& operator++();
  const VertexArrayIterator operator++(int);
  VertexArrayIterator& operator--();
  const VertexArrayIterator operator--(int);
  VertexArrayIterator& operator+=(long long int x);
  VertexArrayIterator& operator-=(long long int x);
  [[nodiscard]] VertexArrayIterator operator+(long long int x) const;
  [[nodiscard]] VertexArrayIterator operator-(long long int x) const;

  const sf::Vertex& operator*() const;
  sf::Vertex& operator*();
  sf::Vertex* operator->() const;

  bool operator==(const VertexArrayIterator& other);
  bool operator!=(const VertexArrayIterator& other);

 private:
  sf::VertexArray& va;
  long long int index;
};

class VertexArrayConstIterator {
 public:
  VertexArrayConstIterator(const sf::VertexArray& va, std::size_t index);

  VertexArrayConstIterator& operator++();
  const VertexArrayConstIterator operator++(int);
  VertexArrayConstIterator& operator--();
  const VertexArrayConstIterator operator--(int);
  VertexArrayConstIterator& operator+=(long long int x);
  VertexArrayConstIterator& operator-=(long long int x);

  bool operator==(const VertexArrayConstIterator& other);
  bool operator!=(const VertexArrayConstIterator& other);

  const sf::Vertex& operator*() const;

 private:
  const sf::VertexArray& va;
  long long int index;
};

}  // namespace loki::core

namespace sf {

loki::core::VertexArrayIterator begin(sf::VertexArray& va);
loki::core::VertexArrayConstIterator begin(const sf::VertexArray& va);
loki::core::VertexArrayConstIterator cbegin(sf::VertexArray& va);
loki::core::VertexArrayConstIterator cbegin(const sf::VertexArray& va);
loki::core::VertexArrayIterator end(sf::VertexArray& va);
loki::core::VertexArrayConstIterator end(const sf::VertexArray& va);
loki::core::VertexArrayConstIterator cend(sf::VertexArray& va);
loki::core::VertexArrayConstIterator cend(const sf::VertexArray& va);

}  // namespace sf
