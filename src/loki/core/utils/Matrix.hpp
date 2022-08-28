#pragma once

#include <array>
#include <functional>
#include <vector>

namespace loki::core {

template <typename T>
class Matrix {
 public:
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

 public:
  Matrix() = default;
  explicit Matrix(std::size_t width, std::size_t height);
  explicit Matrix(std::size_t width, std::size_t height, const T& defaultValue);

  template <
      typename Iterator,
      std::enable_if_t<std::is_lvalue_reference_v<
                           typename std::iterator_traits<Iterator>::reference>,
                       int> = 0>
  explicit Matrix(std::size_t width, std::size_t height, Iterator iterator);

  template <
      typename Iterator,
      std::enable_if_t<std::is_rvalue_reference_v<
                           typename std::iterator_traits<Iterator>::reference>,
                       int> = 0>
  explicit Matrix(std::size_t width, std::size_t height, Iterator iterator);

  explicit Matrix(std::size_t width,
                  std::size_t height,
                  const std::function<T()>& gen);

  T& operator[](std::pair<std::size_t, std::size_t> coords);
  const T& operator[](std::pair<std::size_t, std::size_t> coords) const;

  [[nodiscard]] constexpr std::size_t getWidth() const;
  [[nodiscard]] constexpr std::size_t getHeight() const;

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

 private:
  std::vector<T> data;
  std::size_t W = 0, H = 0;
};

template <typename T, std::size_t W, std::size_t H>
class StaticMatrix {
 public:
  using iterator = typename std::array<T, W * H>::iterator;
  using const_iterator = typename std::array<T, W * H>::const_iterator;

 public:
  StaticMatrix() = default;
  explicit StaticMatrix(const T& defaultValue);

  template <typename Iterator>
  explicit StaticMatrix(Iterator iterator);

  T& operator[](std::pair<std::size_t, std::size_t> coords);
  const T& operator[](std::pair<std::size_t, std::size_t> coords) const;

  [[nodiscard]] constexpr std::size_t getWidth() const;
  [[nodiscard]] constexpr std::size_t getHeight() const;

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

 private:
  std::array<T, W * H> data;
};

}  // namespace loki::core

#include "Matrix.hxx"
