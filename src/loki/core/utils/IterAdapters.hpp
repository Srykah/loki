#pragma once

namespace loki::core {

////////////////////////////////////////////////////////////////////////////////
/// Enumerate
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class EnumerateWrapper {
 public:
  class iterator {
    using inner_iterator = std::conditional_t<std::is_const_v<T>,
                                              typename T::const_iterator,
                                              typename T::iterator>;
    using inner_reference =
        typename std::iterator_traits<inner_iterator>::reference;

   public:
    using reference = std::pair<size_t, inner_reference>;

    explicit iterator(inner_iterator it) : _pos(0), _it(it) {}

    reference operator*() const { return reference(_pos, *_it); }

    iterator& operator++() {
      ++_pos;
      ++_it;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      ++*this;
      return tmp;
    }

    bool operator==(iterator const& it) const { return _it == it._it; }
    bool operator!=(iterator const& it) const { return !(*this == it); }

   private:
    size_t _pos;
    inner_iterator _it;
  };

  explicit EnumerateWrapper(T& t) : container(t) {}

  iterator begin() const { return iterator(container.begin()); }
  iterator end() const { return iterator(container.end()); }

 private:
  T& container;
};  // class EnumerateWrapper

template <typename T>
auto enumerate(T& t) {
  return EnumerateWrapper<T>(t);
}

template <typename T>
auto cenumerate(const T& t) {
  return EnumerateWrapper<const T>(t);
}

////////////////////////////////////////////////////////////////////////////////
/// Reversed
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class ReversedWrapper {
 public:
  using iterator = std::conditional_t<std::is_const_v<T>,
                                      typename T::const_reverse_iterator,
                                      typename T::reverse_iterator>;

  explicit ReversedWrapper(T& t) : container(t) {}

  iterator begin() const { return container.rbegin(); }
  iterator end() const { return container.rend(); }

 private:
  T& container;
};  // class AsReversedWrapper

template <typename T>
auto reversed(T& t) {
  return ReversedWrapper(t);
}

template <typename T>
auto creversed(const T& t) {
  return ReversedWrapper(t);
}

////////////////////////////////////////////////////////////////////////////////
/// Zip
////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
class ZipWrapper {
 public:
  class iterator {
    using inner_iterator1 = std::conditional_t<std::is_const_v<T>,
                                               typename T::const_iterator,
                                               typename T::iterator>;
    using inner_reference1 =
        typename std::iterator_traits<inner_iterator1>::reference;
    using inner_iterator2 = std::conditional_t<std::is_const_v<U>,
                                               typename U::const_iterator,
                                               typename U::iterator>;
    using inner_reference2 =
        typename std::iterator_traits<inner_iterator2>::reference;

   public:
    using reference = std::pair<inner_reference1, inner_reference2>;

    explicit iterator(inner_iterator1 it1, inner_iterator2 it2)
        : _it1(it1), _it2(it2) {}

    reference operator*() const { return reference(*_it1, *_it2); }

    iterator& operator++() {
      ++_it1;
      ++_it2;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      ++*this;
      return tmp;
    }

    bool operator==(iterator const& it) const {
      // Note: the logical OR here is intentional.
      // Since we always modify both iterators at once, checking one should be
      // enough, but since we're not sure both containers are the same size,
      // this OR allows us to check for the end on the second iterator too.
      return _it1 == it._it1 || _it2 == it._it2;
    }
    bool operator!=(iterator const& it) const { return !(*this == it); }

   private:
    inner_iterator1 _it1;
    inner_iterator2 _it2;
  };

  ZipWrapper(T& t, U& u) : container1(t), container2(u) {}

  iterator begin() const {
    return iterator(container1.begin(), container2.begin());
  }
  iterator end() const { return iterator(container1.end(), container2.end()); }

 private:
  T& container1;
  U& container2;
};  // class ZipWrapper

template <typename T, typename U>
auto zip(T& t, U& u) {
  return ZipWrapper<T, U>(t, u);
}

template <typename T, typename U>
auto czip(T& t, U& u) {
  return ZipWrapper<const T, const U>(t, u);
}

////////////////////////////////////////////////////////////////////////////////
/// Drop
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class DropWrapper {
 public:
  using iterator = typename T::iterator;
  DropWrapper(T& t, std::size_t count) : container(t), dropCount(count) {}

  iterator begin() const { return std::advance(container.begin() + dropCount); }
  iterator end() const { return container.end(); }

 private:
  T& container;
  std::size_t dropCount;
};  // class DropWrapper

template <typename T>
auto drop(T& t, std::size_t count) {
  return DropWrapper<T>(t, count);
}

template <typename T>
auto cdrop(T& t, std::size_t count) {
  return DropWrapper<const T>(t, count);
}

}  // namespace loki::core
