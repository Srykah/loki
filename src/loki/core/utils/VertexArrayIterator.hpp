/*!
 * \file VertexArrayIterator.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/VertexArray.hpp>

namespace loki {
inline namespace utils {

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

}  // namespace utils
}  // namespace loki

namespace sf {

loki::VertexArrayIterator begin(sf::VertexArray& va);
loki::VertexArrayConstIterator begin(const sf::VertexArray& va);
loki::VertexArrayConstIterator cbegin(sf::VertexArray& va);
loki::VertexArrayConstIterator cbegin(const sf::VertexArray& va);
loki::VertexArrayIterator end(sf::VertexArray& va);
loki::VertexArrayConstIterator end(const sf::VertexArray& va);
loki::VertexArrayConstIterator cend(sf::VertexArray& va);
loki::VertexArrayConstIterator cend(const sf::VertexArray& va);

}  // namespace sf
