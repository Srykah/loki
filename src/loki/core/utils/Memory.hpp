/*!
 * \file Memory.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <stdexcept>

namespace loki {
inline namespace utils {

namespace impl {

struct RefCount {
  bool valid = true;
  int count = 1;
};

}  // namespace impl

template <class T>
class BorrowerPtr;

/// OwnerPtr
template <class T>
class OwnerPtr {
 public:
  OwnerPtr() = default;

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  explicit OwnerPtr(U* t);

  OwnerPtr(OwnerPtr&) = delete;
  void operator=(OwnerPtr&) = delete;

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  explicit OwnerPtr(OwnerPtr<U>&& other) noexcept;

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  OwnerPtr& operator=(OwnerPtr<U>&& other) noexcept;

  ~OwnerPtr();

  void reset();

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  void reset(U* u);

  [[nodiscard]] BorrowerPtr<T> borrow() const;

  T* operator*() const;
  T* operator->() const;

 private:
  T* t = nullptr;
  impl::RefCount* refCount = nullptr;

  friend BorrowerPtr<T>;

  template <class U>
  friend OwnerPtr<U> static_pointer_cast(OwnerPtr&& other);
};

/// BorrowerPtr
template <class T>
class BorrowerPtr {
 public:
  BorrowerPtr() = default;

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  explicit BorrowerPtr(const OwnerPtr<U>& owner);

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  explicit BorrowerPtr(const BorrowerPtr<U>& other);

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  BorrowerPtr& operator=(const OwnerPtr<U>& owner);

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  BorrowerPtr& operator=(const BorrowerPtr<U>& other);

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  explicit BorrowerPtr(BorrowerPtr<U>&& other) noexcept;

  template <class U,
            std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>,
                             int> = 0>
  BorrowerPtr& operator=(BorrowerPtr<U>&& other) noexcept;

  ~BorrowerPtr();

  [[nodiscard]] bool isValid() const;
  [[nodiscard]] explicit operator bool() const;

  T* operator*() const;
  T* operator->() const;

 private:
  void incrRefCount();
  void deleteRefCount();

 private:
  T* t = nullptr;
  impl::RefCount* refCount = nullptr;

  template <class Out, class In>
  friend BorrowerPtr<Out> static_pointer_cast(const BorrowerPtr<In>& ptrToBase);

  template <class Out, class In>
  friend BorrowerPtr<Out> static_pointer_cast(BorrowerPtr<In>&& ptrToBase);
};

}  // namespace utils
}  // namespace loki

#include "impl/Memory.hxx"
