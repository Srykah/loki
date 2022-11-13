#pragma once

#include <stdexcept>

namespace loki::core {

template <class T, class U>
concept IsSameOrBase = std::is_same_v<T, U> || std::is_base_of_v<T, U>;

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

  template <class U>
    requires IsSameOrBase<T, U>
  explicit OwnerPtr(U* t);

  OwnerPtr(OwnerPtr&) = delete;
  void operator=(OwnerPtr&) = delete;

  template <class U>
    requires IsSameOrBase<T, U>
  explicit OwnerPtr(OwnerPtr<U>&& other) noexcept;

  template <class U>
    requires IsSameOrBase<T, U>
  OwnerPtr& operator=(OwnerPtr<U>&& other) noexcept;

  ~OwnerPtr();

  template <class U>
    requires IsSameOrBase<T, U>
  void reset(U* u);
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
    requires IsSameOrBase<T, U>
  friend OwnerPtr<U> static_pointer_cast(OwnerPtr&& other);
};

/// BorrowerPtr
template <class T>
class BorrowerPtr {
 private:
 public:
  BorrowerPtr() = default;

  template <class U>
    requires IsSameOrBase<T, U>
  explicit BorrowerPtr(const OwnerPtr<U>& owner);

  template <class U>
    requires IsSameOrBase<T, U>
  explicit BorrowerPtr(const BorrowerPtr<U>& other);

  template <class U>
    requires IsSameOrBase<T, U>
  BorrowerPtr& operator=(const OwnerPtr<U>& owner);

  template <class U>
    requires IsSameOrBase<T, U>
  BorrowerPtr& operator=(const BorrowerPtr<U>& other);

  template <class U>
    requires IsSameOrBase<T, U>
  explicit BorrowerPtr(BorrowerPtr<U>&& other) noexcept;

  template <class U>
    requires IsSameOrBase<T, U>
  BorrowerPtr& operator=(BorrowerPtr<U>&& other) noexcept;

  ~BorrowerPtr();

  [[nodiscard]] bool isValid() const;
  [[nodiscard]] explicit operator bool() const;

  T* get() const;

  T& operator*() const;
  T* operator->() const;

  template <class U>
    requires IsSameOrBase<T, U> bool
  operator<=>(const BorrowerPtr<U>& other) const;

  template <class U>
    requires IsSameOrBase<T, U> bool
  operator<=>(const U* other) const;

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
