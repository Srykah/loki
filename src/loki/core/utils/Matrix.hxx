#include <algorithm>
#include <iterator>
#include <loki/core/utils/Matrix.hpp>

namespace loki::core {

// Matrix

template <typename T>
Matrix<T>::Matrix(std::size_t width, std::size_t height)
    : Matrix(width, height, []() { return T{}; }) {}

template <typename T>
Matrix<T>::Matrix(std::size_t width, std::size_t height, const T& defaultValue)
    : data(width * height, defaultValue), W(width), H(height) {}

template <typename T>
template <
    typename Iterator,
    std::enable_if_t<std::is_lvalue_reference_v<
                         typename std::iterator_traits<Iterator>::reference>,
                     int>>
Matrix<T>::Matrix(std::size_t width, std::size_t height, Iterator iterator)
    : Matrix(width, height, [iterator]() mutable { return *iterator++; }) {}

template <typename T>
template <
    typename Iterator,
    std::enable_if_t<std::is_rvalue_reference_v<
                         typename std::iterator_traits<Iterator>::reference>,
                     int>>
Matrix<T>::Matrix(std::size_t width, std::size_t height, Iterator iterator)
    : Matrix(width, height, [iterator]() mutable {
        return std::move(*iterator++);
      }) {}

template <typename T>
Matrix<T>::Matrix(std::size_t width,
                  std::size_t height,
                  const std::function<T()>& gen)
    : W(width), H(height) {
  data.reserve(W * H);
  std::generate_n(std::back_inserter(data), W * H, gen);
}

template <typename T>
T& Matrix<T>::operator[](std::pair<std::size_t, std::size_t> coords) {
  return const_cast<T&>(static_cast<const Matrix&>(*this)[coords]);
}

template <typename T>
const T& Matrix<T>::operator[](
    std::pair<std::size_t, std::size_t> coords) const {
  return data[coords.first + W * coords.second];
}

template <typename T>
constexpr std::size_t Matrix<T>::getWidth() const {
  return W;
}

template <typename T>
constexpr std::size_t Matrix<T>::getHeight() const {
  return H;
}

template <typename T>
auto Matrix<T>::begin() -> iterator {
  return data.begin();
}

template <typename T>
auto Matrix<T>::begin() const -> const_iterator {
  return data.cbegin();
}

template <typename T>
auto Matrix<T>::cbegin() const -> const_iterator {
  return data.cbegin();
}

template <typename T>
auto Matrix<T>::end() -> iterator {
  return data.end();
}

template <typename T>
auto Matrix<T>::end() const -> const_iterator {
  return data.cend();
}

template <typename T>
auto Matrix<T>::cend() const -> const_iterator {
  return data.cend();
}

// StaticMatrix

template <typename T, std::size_t W, std::size_t H>
StaticMatrix<T, W, H>::StaticMatrix(const T& defaultValue) {
  std::fill(data.begin(), data.end(), defaultValue);
}

template <typename T, std::size_t W, std::size_t H>
template <typename Iterator>
StaticMatrix<T, W, H>::StaticMatrix(Iterator iterator) {
  std::copy_n(iterator, W * H, data.begin());
}

template <typename T, std::size_t W, std::size_t H>
T& StaticMatrix<T, W, H>::operator[](
    std::pair<std::size_t, std::size_t> coords) {
  return const_cast<T&>(static_cast<const StaticMatrix&>(*this)[coords]);
}

template <typename T, std::size_t W, std::size_t H>
const T& StaticMatrix<T, W, H>::operator[](
    std::pair<std::size_t, std::size_t> coords) const {
  return data[coords.first + W * coords.second];
}

template <typename T, std::size_t W, std::size_t H>
constexpr std::size_t StaticMatrix<T, W, H>::getWidth() const {
  return W;
}

template <typename T, std::size_t W, std::size_t H>
constexpr std::size_t StaticMatrix<T, W, H>::getHeight() const {
  return H;
}

template <typename T, std::size_t W, std::size_t H>
auto StaticMatrix<T, W, H>::begin() -> iterator {
  return data.begin();
}

template <typename T, std::size_t W, std::size_t H>
auto StaticMatrix<T, W, H>::begin() const -> const_iterator {
  return data.cbegin();
}

template <typename T, std::size_t W, std::size_t H>
auto StaticMatrix<T, W, H>::cbegin() const -> const_iterator {
  return data.cbegin();
}

template <typename T, std::size_t W, std::size_t H>
auto StaticMatrix<T, W, H>::end() -> iterator {
  return data.end();
}

template <typename T, std::size_t W, std::size_t H>
auto StaticMatrix<T, W, H>::end() const -> const_iterator {
  return data.cend();
}

template <typename T, std::size_t W, std::size_t H>
auto StaticMatrix<T, W, H>::cend() const -> const_iterator {
  return data.cend();
}

}  // namespace loki::core
