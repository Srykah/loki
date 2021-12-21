/*!
 * \file Matrix.inl
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

namespace loki::common {

template <typename T>
template <typename Iterator>
Matrix<T>::Matrix(std::size_t width, std::size_t height, Iterator iterator)
    : width(width), height(height) {
  data.reserve(width * height);
  std::copy_n(iterator, width * height, std::back_inserter(data));
}

template <typename T>
Matrix<T>::Matrix(std::size_t width, std::size_t height, const T& defaultValue)
    : width(width), height(height), data(width * height, defaultValue) {}

}  // namespace loki::common