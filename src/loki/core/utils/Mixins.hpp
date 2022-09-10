#pragma once

namespace loki::core {

template <class T>
struct IncrMixin {
  T& operator++() {
    ++static_cast<T&>(*this).t;
    return static_cast<T&>(*this);
  }
  T operator++(int) {
    T copy(static_cast<T&>(*this));
    operator++();
    return copy;
  }
};

template <class T>
struct DecrMixin {
  T& operator--() {
    --static_cast<T&>(*this).t;
    return static_cast<T&>(*this);
  }
  T operator--(int) {
    T copy(static_cast<T&>(*this));
    operator--();
    return copy;
  }
};

template <class T>
struct AddSameMixin {
  T& operator+=(const T& other) {
    static_cast<T&>(*this).t += other.t;
    return static_cast<T&>(*this);
  }
  T operator+(const T& other) {
    T copy(static_cast<T&>(*this));
    copy += other;
    return copy;
  }
};

template <class Base, template <class T> class... Mixins>
class MixinCombine : public Mixins<Base>... {};

}  // namespace loki::core