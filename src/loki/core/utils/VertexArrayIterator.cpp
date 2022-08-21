/*!
 * \file VertexArrayIterator.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "VertexArrayIterator.hpp"

namespace loki::core {

VertexArrayIterator::VertexArrayIterator(sf::VertexArray& va,
                                         std::size_t _index)
    : va(va), index(_index) {
  if (index > va.getVertexCount()) {
    index = va.getVertexCount();
  }
}

VertexArrayIterator& VertexArrayIterator::operator++() {
  if (index < va.getVertexCount()) {
    ++index;
  }
  return *this;
}

const VertexArrayIterator VertexArrayIterator::operator++(int) {
  auto copy = *this;
  ++*this;
  return copy;
}

VertexArrayIterator& VertexArrayIterator::operator--() {
  if (index > 0ll) {
    --index;
  }
  return *this;
}

const VertexArrayIterator VertexArrayIterator::operator--(int) {
  auto copy = *this;
  --*this;
  return copy;
}

VertexArrayIterator& VertexArrayIterator::operator+=(long long int x) {
  if (index + x < 0) {
    index = 0;
  } else if (index + x > va.getVertexCount()) {
    index = va.getVertexCount();
  } else {
    index += x;
  }
  return *this;
}

VertexArrayIterator& VertexArrayIterator::operator-=(long long int x) {
  return *this += -x;
}

VertexArrayIterator VertexArrayIterator::operator+(long long int x) const {
  return VertexArrayIterator(*this) += x;
}

VertexArrayIterator VertexArrayIterator::operator-(long long int x) const {
  return VertexArrayIterator(*this) -= x;
}

const sf::Vertex& VertexArrayIterator::operator*() const {
  return va[index];
}

sf::Vertex& VertexArrayIterator::operator*() {
  return va[index];
}

sf::Vertex* VertexArrayIterator::operator->() const {
  return &va[index];
}

bool VertexArrayIterator::operator==(const VertexArrayIterator& other) {
  return &va == &other.va && index == other.index;
}
bool VertexArrayIterator::operator!=(const VertexArrayIterator& other) {
  return !(*this == other);
}

VertexArrayConstIterator::VertexArrayConstIterator(const sf::VertexArray& va,
                                                   std::size_t _index)
    : va(va), index(_index) {
  if (index > va.getVertexCount()) {
    index = va.getVertexCount();
  }
}

VertexArrayConstIterator& VertexArrayConstIterator::operator++() {
  if (index < va.getVertexCount()) {
    ++index;
  }
  return *this;
}

const VertexArrayConstIterator VertexArrayConstIterator::operator++(int) {
  auto copy = *this;
  ++*this;
  return copy;
}

VertexArrayConstIterator& VertexArrayConstIterator::operator--() {
  if (index > 0ll) {
    --index;
  }
  return *this;
}

const VertexArrayConstIterator VertexArrayConstIterator::operator--(int) {
  auto copy = *this;
  --*this;
  return copy;
}

VertexArrayConstIterator& VertexArrayConstIterator::operator+=(
    long long int x) {
  if (index + x < 0) {
    index = 0;
  } else if (index + x > va.getVertexCount()) {
    index = va.getVertexCount();
  } else {
    index += x;
  }
  return *this;
}

VertexArrayConstIterator& VertexArrayConstIterator::operator-=(
    long long int x) {
  return *this += -x;
}
const sf::Vertex& VertexArrayConstIterator::operator*() const {
  return va[index];
}

bool VertexArrayConstIterator::operator==(
    const VertexArrayConstIterator& other) {
  return &va == &other.va && index == other.index;
}

bool VertexArrayConstIterator::operator!=(
    const VertexArrayConstIterator& other) {
  return !(*this == other);
}

}  // namespace loki::core

namespace sf {

loki::core::VertexArrayIterator begin(sf::VertexArray& va) {
  return loki::core::VertexArrayIterator(va, 0);
}

loki::core::VertexArrayConstIterator begin(const VertexArray& va) {
  return loki::core::VertexArrayConstIterator(va, 0);
}

loki::core::VertexArrayConstIterator cbegin(sf::VertexArray& va) {
  return loki::core::VertexArrayConstIterator(va, 0);
}

loki::core::VertexArrayConstIterator cbegin(const VertexArray& va) {
  return loki::core::VertexArrayConstIterator(va, 0);
}

loki::core::VertexArrayIterator end(sf::VertexArray& va) {
  return loki::core::VertexArrayIterator(va, va.getVertexCount());
}

loki::core::VertexArrayConstIterator end(const VertexArray& va) {
  return loki::core::VertexArrayConstIterator(va, va.getVertexCount());
}

loki::core::VertexArrayConstIterator cend(sf::VertexArray& va) {
  return loki::core::VertexArrayConstIterator(va, va.getVertexCount());
}

loki::core::VertexArrayConstIterator cend(const VertexArray& va) {
  return loki::core::VertexArrayConstIterator(va, va.getVertexCount());
}

}  // namespace sf
