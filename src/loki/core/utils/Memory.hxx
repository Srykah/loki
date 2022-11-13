namespace loki::core {

/// OwnerPtr

template <class T>
template <class U>
  requires IsSameOrBase<T, U>
OwnerPtr<T>::OwnerPtr(U* t) : t(t), refCount(new impl::RefCount()) {}

template <class T>
template <class U>
  requires IsSameOrBase<T, U>
OwnerPtr<T>::OwnerPtr(OwnerPtr<U>&& other) noexcept : t(other.t), refCount(other.refCount) {
  other.t = nullptr;
  other.refCount = nullptr;
}

template <class T>
template <class U>
  requires IsSameOrBase<T, U>
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
template <class U>
  requires IsSameOrBase<T, U>
void OwnerPtr<T>::reset(U* u) {
  *this = OwnerPtr(u);
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
T* OwnerPtr<T>::get() const {
  return t;
}

template <class T>
BorrowerPtr<T> OwnerPtr<T>::borrow() const {
  return BorrowerPtr<T>(*this);
}

template <class T>
T& OwnerPtr<T>::operator*() const {
  return *t;
}

template <class T>
T* OwnerPtr<T>::operator->() const {
  return get();
}

template <class T, class U>
  requires IsSameOrBase<T, U>
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
template <class U>
  requires IsSameOrBase<T, U>
BorrowerPtr<T>::BorrowerPtr(const OwnerPtr<U>& owner) : t(owner.t), refCount(owner.refCount) {
  incrRefCount();
}

template <class T>
template <class U>
  requires IsSameOrBase<T, U>
BorrowerPtr<T>::BorrowerPtr(const BorrowerPtr<U>& other) : t(other.t), refCount(other.refCount) {
  incrRefCount();
}

template <class T>
template <class U>
  requires IsSameOrBase<T, U>
BorrowerPtr<T>& BorrowerPtr<T>::operator=(const OwnerPtr<U>& owner) {
  deleteRefCount();
  t = owner.t;
  refCount = owner.refCount;
  incrRefCount();
}

template <class T>
template <class U>
  requires IsSameOrBase<T, U>
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
template <class U>
  requires IsSameOrBase<T, U>
BorrowerPtr<T>::BorrowerPtr(BorrowerPtr<U>&& other) noexcept : t(other.t), refCount(other.refCount) {
  other.t = nullptr;
  other.refCount = nullptr;
}

template <class T>
template <class U>
  requires IsSameOrBase<T, U>
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
T* BorrowerPtr<T>::get() const {
  return t;
}

template <class T>
T& BorrowerPtr<T>::operator*() const {
  if (!isValid())
    throw std::runtime_error("Dereferencing invalid BorrowerPtr!");
  return *t;
}

template <class T>
T* BorrowerPtr<T>::operator->() const {
  if (!isValid())
    throw std::runtime_error("Dereferencing invalid BorrowerPtr!");
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

template <class T>
template <class U>
  requires IsSameOrBase<T, U> bool
BorrowerPtr<T>::operator<=>(const BorrowerPtr<U>& other) const {
  return t <=> other.t;
}

template <class T>
template <class U>
  requires IsSameOrBase<T, U> bool
BorrowerPtr<T>::operator<=>(const U* other) const {
  return t <=> other;
}

}  // namespace loki::core
