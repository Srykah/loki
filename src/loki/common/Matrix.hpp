/*!
 * \file Matrix.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::common {
template <typename T>
class Matrix {
 public:
  Matrix() = default;

  Matrix(std::size_t width, std::size_t height, const T& defaultValue = T());

  template<typename Iterator>
  Matrix(std::size_t width, std::size_t height, Iterator iterator);

  T& operator[](std::pair<std::size_t, std::size_t> coords) { return const_cast<T&>(static_cast<const Matrix<T>&>(*this)[coords]); }
  const T& operator[](std::pair<std::size_t, std::size_t> coords) const { return data[coords.first + width * coords.second]; }

  typename std::vector<T>::iterator begin() { return data.begin(); }
  typename std::vector<T>::const_iterator begin() const { return data.cbegin(); }
  typename std::vector<T>::const_iterator cbegin() const { return data.cbegin(); }
  typename std::vector<T>::iterator end() { return data.end(); }
  typename std::vector<T>::const_iterator end() const { return data.cend(); }
  typename std::vector<T>::const_iterator cend() const { return data.cend(); }

 private:
  std::vector<T> data;
  std::size_t height = 0, width = 0;
};

}

#include "Matrix.inl"
