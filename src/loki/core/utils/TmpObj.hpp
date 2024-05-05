#pragma once

#include <functional>
#include <utility>

namespace loki::core {

struct TmpObj {
  enum class Ownership { Owned, NonOwned, Default };

  void* obj = nullptr;
  std::function<void(void*)> deleter;
  Ownership ownership = Ownership::Default;

  TmpObj() = default;
  TmpObj(void* obj, std::function<void(void*)> deleter, Ownership ownership)
      : obj(obj), deleter(std::move(deleter)), ownership(ownership) {}
  TmpObj(const TmpObj&) = delete;
  TmpObj& operator=(const TmpObj&) = delete;
  TmpObj(TmpObj&& other) noexcept : obj(other.obj), deleter(std::move(other.deleter)), ownership(other.ownership) {
    other.obj = nullptr;
    other.deleter = nullptr;
    other.ownership = Ownership::NonOwned;
  }
  TmpObj& operator=(TmpObj&& other) noexcept {
    if (deleter)
      deleter(obj);

    obj = other.obj;
    other.obj = nullptr;
    deleter = other.deleter;
    other.deleter = nullptr;
    ownership = other.ownership;
    other.ownership = Ownership::NonOwned;

    return *this;
  }
  ~TmpObj() {
    if (deleter)
      deleter(obj);
  }

  template <class T, class... Args>
    requires(!std::is_array_v<T>)
  static TmpObj makeNonOwned(Args&&... args) {
    return TmpObj{new T{std::forward<Args>(args)...}, nullptr, Ownership::NonOwned};
  }

  template <class T, class... Args>
    requires(!std::is_array_v<T>)
  static TmpObj makeOwned(Args&&... args) {
    return TmpObj{new T{std::forward<Args>(args)...}, [](void* obj) { delete static_cast<T*>(obj); }, Ownership::Owned};
  }

  static TmpObj fromPtrNonOwned(void* ptr) { return TmpObj{ptr, nullptr, Ownership::NonOwned}; }

  template <class T>
    requires(!std::is_array_v<T>)
  static TmpObj fromPtrOwned(void* ptr) {
    return TmpObj{ptr, [](void* obj) { delete static_cast<T*>(obj); }, Ownership::Owned};
  }
};

struct ConstTmpObj {
  const void* obj = nullptr;
  std::function<void(const void*)> deleter;
  TmpObj::Ownership ownership = TmpObj::Ownership::Default;

  ConstTmpObj() = default;
  ConstTmpObj(const void* obj, std::function<void(const void*)> deleter, TmpObj::Ownership ownership)
      : obj(obj), deleter(std::move(deleter)), ownership(ownership) {}
  ConstTmpObj(const ConstTmpObj&) = delete;
  ConstTmpObj& operator=(const ConstTmpObj&) = delete;
  ConstTmpObj(ConstTmpObj&& other) noexcept
      : obj(other.obj), deleter(std::move(other.deleter)), ownership(other.ownership) {
    other.obj = nullptr;
    other.deleter = nullptr;
    other.ownership = TmpObj::Ownership::NonOwned;
  }
  ConstTmpObj& operator=(ConstTmpObj&& other) noexcept {
    if (deleter)
      deleter(obj);

    obj = other.obj;
    other.obj = nullptr;
    deleter = other.deleter;
    other.deleter = nullptr;
    ownership = other.ownership;
    other.ownership = TmpObj::Ownership::NonOwned;

    return *this;
  }
  ~ConstTmpObj() {
    if (deleter)
      deleter(obj);
  }

  template <class T, class... Args>
    requires(!std::is_array_v<T>)
  static ConstTmpObj makeNonOwned(Args&&... args) {
    return ConstTmpObj{new T{std::forward<Args>(args)...}, nullptr, TmpObj::Ownership::NonOwned};
  }

  template <class T, class... Args>
    requires(!std::is_array_v<T>)
  static ConstTmpObj makeOwned(Args&&... args) {
    return ConstTmpObj{new T{std::forward<Args>(args)...}, [](const void* obj) { delete static_cast<const T*>(obj); },
                       TmpObj::Ownership::Owned};
  }

  static ConstTmpObj fromPtrNonOwned(const void* ptr) { return ConstTmpObj{ptr, nullptr, TmpObj::Ownership::NonOwned}; }

  template <class T>
    requires(!std::is_array_v<T>)
  static ConstTmpObj fromPtrOwned(const void* ptr) {
    return ConstTmpObj{ptr, [](const void* obj) { delete static_cast<const T*>(obj); }, TmpObj::Ownership::Owned};
  }
};
}