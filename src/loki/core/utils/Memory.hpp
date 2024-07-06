#pragma once

#include <concepts>
#include <iostream>
#include <stdexcept>

namespace loki::core {

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

  explicit OwnerPtr(std::derived_from<T> auto* u);

  OwnerPtr(OwnerPtr&) = delete;
  void operator=(OwnerPtr&) = delete;

  template <std::derived_from<T> U>
  explicit OwnerPtr(OwnerPtr<U>&& other) noexcept;

  template <std::derived_from<T> U>
  OwnerPtr& operator=(OwnerPtr<U>&& other) noexcept;

  ~OwnerPtr();

  void reset(std::derived_from<T> auto* u);
  void reset();

  T* get() const;

  [[nodiscard]] BorrowerPtr<T> borrow() const;

  T& operator*() const;
  T* operator->() const;

 private:
  T* t = nullptr;
  impl::RefCount* refCount = nullptr;

  friend BorrowerPtr<T>;

  template <class U>
  friend OwnerPtr<U> static_pointer_cast(OwnerPtr&& ptrToBase);
};

/// BorrowerPtr
template <class T>
class BorrowerPtr {
 private:
 public:
  BorrowerPtr() = default;

  template <std::derived_from<T> U>
  explicit BorrowerPtr(const OwnerPtr<U>& owner);

  template <std::derived_from<T> U>
  explicit BorrowerPtr(const BorrowerPtr<U>& other);

  template <std::derived_from<T> U>
  BorrowerPtr& operator=(const OwnerPtr<U>& owner);

  template <std::derived_from<T> U>
  BorrowerPtr& operator=(const BorrowerPtr<U>& other);

  template <std::derived_from<T> U>
  explicit BorrowerPtr(BorrowerPtr<U>&& other) noexcept;

  template <std::derived_from<T> U>
  BorrowerPtr& operator=(BorrowerPtr<U>&& other) noexcept;

  ~BorrowerPtr();

  [[nodiscard]] bool isValid() const;
  [[nodiscard]] explicit operator bool() const;

  T* get() const;

  T& operator*() const;
  T* operator->() const;

  template <std::derived_from<T> U>
  auto operator<=>(const BorrowerPtr<U>& other) const;

  auto operator<=>(const std::derived_from<T> auto* other) const;

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

}  // namespace loki::core

#include "Memory.hxx"
