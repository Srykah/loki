namespace loki::core {

template <typename T>
template <typename A, typename B, typename C, typename D>
Vector4<T>::Vector4(A&& a, B&& b, C&& c, D&& d)
    : a(std::forward<A>(a)), b(std::forward<B>(b)), c(std::forward<C>(c)), d(std::forward<D>(d)) {}

template <typename A, typename B, typename C, typename D>
Vector4(A a, B b, C c, D d) -> Vector4<std::common_type<A, B, C, D>>;

template <typename T>
template <typename U>
Vector4<T>::Vector4(const Vector4<U>& v) : a(v.a), b(v.b), c(v.c), d(v.d) {}

template <typename T>
Vector4<T> Vector4<T>::operator-() const {
  return Vector4<T>{-a, -b, -c, -d};
}

template <typename T>
Vector4<T>& Vector4<T>::operator+=(const Vector4& v) {
  a += v.a;
  b += v.b;
  c += v.c;
  d += v.d;
  return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& v) {
  return *this += -v;
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& v) const {
  return Vector4<T>(*this) += v;
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& v) const {
  return *this + -v;
}

template <typename T>
Vector4<T>& Vector4<T>::operator*=(const T& t) {
  a *= t;
  b *= t;
  c *= t;
  d *= t;
  return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator/=(const T& t) {
  a /= t;
  b /= t;
  c /= t;
  d /= t;
  return *this;
}

template <typename T>
Vector4<T> Vector4<T>::operator*(const T& t) const {
  return Vector4<T>(*this) *= t;
}

template <typename T>
Vector4<T> operator*(const T& t, const Vector4<T>& v) {
  return v * t;
}

template <typename T>
Vector4<T> Vector4<T>::operator/(const T& t) const {
  return Vector4<T>(*this) /= t;
}

template <typename T>
bool Vector4<T>::operator==(const Vector4<T>& v) const {
  return std::tie(a, b, c, d) == std::tie(v.a, v.b, v.c, v.d);
}

template <typename T>
bool Vector4<T>::operator!=(const Vector4<T>& v) const {
  return !(*this == v);
}

template <typename T, typename U>
Vector4<T> fromRect(const sf::Rect<U>& rect) {
  return Vector4<T>(rect.left, rect.top, rect.width, rect.height);
}

template <typename U, typename T>
sf::Rect<U> toRect(const Vector4<T>& v) {
  return sf::Rect<U>(v.a, v.b, v.c, v.d);
}

template <typename T>
Vector4<T> fromColor(const sf::Color& color) {
  return Vector4<T>(color.r, color.g, color.b, color.a);
}

template <typename T>
sf::Color toColor(const Vector4<T>& v) {
  return sf::Color(std::clamp<sf::Uint8>(v.a, 0, 255), std::clamp<sf::Uint8>(v.b, 0, 255),
                   std::clamp<sf::Uint8>(v.c, 0, 255), std::clamp<sf::Uint8>(v.d, 0, 255));
}

#if 0
template <typename T>
void to_json(nlohmann::json& j, const Vector4<T>& vec4) {
  j["a"] = vec4.a;
  j["b"] = vec4.b;
  j["c"] = vec4.c;
  j["d"] = vec4.d;
}

template <typename T>
void from_json(const nlohmann::json& j, Vector4<T>& vec4) {
  j.at("a").get_to(vec4.a);
  j.at("b").get_to(vec4.b);
  j.at("c").get_to(vec4.c);
  j.at("d").get_to(vec4.d);
}
#endif

}  // namespace loki::core
