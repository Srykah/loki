/*!
 * \file Memory.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki {
inline namespace utils {

/// OwnerPtr

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
OwnerPtr<T>::OwnerPtr(U* t) : t(t), refCount(new impl::RefCount()) {}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
OwnerPtr<T>::OwnerPtr(OwnerPtr<U>&& other) noexcept
    : t(other.t), refCount(other.refCount) {
  other.t = nullptr;
  other.refCount = nullptr;
}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
OwnerPtr<T>& OwnerPtr<T>::operator=(OwnerPtr<U>&& other) noexcept {
  reset();
  t = other.t;
  refCount = other.refCount;
  other.t = nullptr;
  other.refCount = nullptr;
  return *this;
}

template <class T>
OwnerPtr<T>::~OwnerPtr() {
  reset();
}

template <class T>
void OwnerPtr<T>::reset() {
  delete t;
  t = nullptr;
  if (refCount) {
    refCount->valid = false;
    --refCount->count;
    if (refCount->count <= 0)
      delete refCount;
    refCount = nullptr;
  }
}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
void OwnerPtr<T>::reset(U* u) {
  *this = OwnerPtr(u);
}

template <class T>
BorrowerPtr<T> OwnerPtr<T>::borrow() const {
  return BorrowerPtr<T>(*this);
}

template <class T>
T* OwnerPtr<T>::operator*() const {
  return t;
}

template <class T>
T* OwnerPtr<T>::operator->() const {
  return t;
}

template <class T, class U>
OwnerPtr<U> static_pointer_cast(OwnerPtr<T>&& ptrToBase) {
  OwnerPtr<U> result;
  result.t = static_cast<U*>(ptrToBase.t);
  result.refCount = ptrToBase.refCount;
  ptrToBase.t = nullptr;
  ptrToBase.refCount = nullptr;
  return result;
}

/// BorrowerPtr

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
BorrowerPtr<T>::BorrowerPtr(const OwnerPtr<U>& owner)
    : t(owner.t), refCount(owner.refCount) {
  incrRefCount();
}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
BorrowerPtr<T>::BorrowerPtr(const BorrowerPtr<U>& other)
    : t(other.t), refCount(other.refCount) {
  incrRefCount();
}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
BorrowerPtr<T>& BorrowerPtr<T>::operator=(const OwnerPtr<U>& owner) {
  deleteRefCount();
  t = owner.t;
  refCount = owner.refCount;
  incrRefCount();
}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
BorrowerPtr<T>& BorrowerPtr<T>::operator=(const BorrowerPtr<U>& other) {
  if (&other == this) {
    return *this;
  }
  deleteRefCount();
  t = other.t;
  refCount = other.refCount;
  incrRefCount();
  return *this;
}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
BorrowerPtr<T>::BorrowerPtr(BorrowerPtr<U>&& other) noexcept
    : t(other.t), refCount(other.refCount) {
  other.t = nullptr;
  other.refCount = nullptr;
}

template <class T>
template <
    class U,
    std::enable_if_t<std::is_same_v<T, U> || std::is_base_of_v<T, U>, int>>
BorrowerPtr<T>& BorrowerPtr<T>::operator=(BorrowerPtr<U>&& other) noexcept {
  deleteRefCount();
  t = other.t;
  refCount = other.refCount;
  other.t = nullptr;
  other.refCount = nullptr;
  return *this;
}

template <class T>
BorrowerPtr<T>::~BorrowerPtr() {
  deleteRefCount();
}

template <class T>
bool BorrowerPtr<T>::isValid() const {
  return refCount && refCount->valid;
}

template <class T>
BorrowerPtr<T>::operator bool() const {
  return isValid();
}

template <class T>
T* BorrowerPtr<T>::operator*() const {
  return isValid() ? t : nullptr;
}

template <class T>
T* BorrowerPtr<T>::operator->() const {
  if (!isValid()) {
    throw std::logic_error("Dereferencing null pointer");
  }
  return t;
}

template <class T>
void BorrowerPtr<T>::incrRefCount() {
  if (refCount) {
    ++refCount->count;
  }
}

template <class T>
void BorrowerPtr<T>::deleteRefCount() {
  if (refCount) {
    --refCount->count;
    if (refCount->count <= 0) {
      delete refCount;
    }
  }
}

template <class Out, class In>
BorrowerPtr<Out> static_pointer_cast(const BorrowerPtr<In>& ptrToBase) {
  BorrowerPtr<Out> result;
  result.t = static_cast<Out*>(ptrToBase.t);
  result.refCount = ptrToBase.refCount;
  if (result.refCount) {
    ++result.refCount->count;
  }
  return result;
}

template <class Out, class In>
BorrowerPtr<Out> static_pointer_cast(BorrowerPtr<In>&& ptrToBase) {
  BorrowerPtr<Out> result;
  result.t = static_cast<Out*>(ptrToBase.t);
  result.refCount = ptrToBase.refCount;
  ptrToBase.t = nullptr;
  ptrToBase.refCount = nullptr;
  return result;
}

}  // namespace utils
}  // namespace loki
