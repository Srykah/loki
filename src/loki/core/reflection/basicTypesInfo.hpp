#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/reflectionUtils.hpp>

namespace loki::core {

template <>
struct TypeInfoHolder<std::nullptr_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = [](void*, TmpObj::Ownership) -> TmpObj { return TmpObj{}; }, .info = NullInfo{}};
  }
};

template <>
struct TypeInfoHolder<bool> {
  static TypeInfo getTypeInfo() { return {.factory = details::getBasicFactory<bool>(), .info = BooleanInfo{}}; }
};

template <>
struct TypeInfoHolder<uint8_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<uint8_t>(),
            .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint8_t)}};
  }
};

template <>
struct TypeInfoHolder<uint16_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<uint16_t>(),
            .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint16_t)}};
  }
};

template <>
struct TypeInfoHolder<uint32_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<uint32_t>(),
            .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint32_t)}};
  }
};

template <>
struct TypeInfoHolder<uint64_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<uint64_t>(),
            .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint64_t)}};
  }
};

template <>
struct TypeInfoHolder<int8_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<int8_t>(),
            .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int8_t)}};
  }
};

template <>
struct TypeInfoHolder<int16_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<int16_t>(),
            .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int16_t)}};
  }
};

template <>
struct TypeInfoHolder<int32_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<int32_t>(),
            .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int32_t)}};
  }
};

template <>
struct TypeInfoHolder<int64_t> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<int64_t>(),
            .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int64_t)}};
  }
};

template <>
struct TypeInfoHolder<float> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<float>(), .info = FloatingPointInfo{.size = sizeof(float)}};
  }
};

template <>
struct TypeInfoHolder<double> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<double>(), .info = FloatingPointInfo{.size = sizeof(double)}};
  }
};

template <>
struct TypeInfoHolder<long double> {
  static TypeInfo getTypeInfo() {
    return {.factory = details::getBasicFactory<long double>(), .info = FloatingPointInfo{.size = sizeof(long double)}};
  }
};

template <>
struct TypeInfoHolder<char> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<char>(),
        .info = CharacterInfo{.size = sizeof(char), .isUnicode = false},
    };
  }
};

template <>
struct TypeInfoHolder<std::string> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<std::string>(),
        .info = StringInfo{.charType = getFullyQualifiedNameOf<^^char>(),
                           .asUtf8StrGetter = [](const void* obj) -> ConstTmpObj {
                             return ConstTmpObj::fromPtrNonOwned(&details::to<std::string>(obj));
                           },
                           .fromUtf8StrSetter =
                               [](void* obj, const char* data, std::size_t size) {
                                 details::to<std::string>(obj) = std::string_view(data, size);
                               }},
    };
  }
};

#if 0
template <class CharT>
  requires(!std::is_same_v<std::decay_t<CharT>, char>)
struct TypeInfoHolder<std::basic_string<CharT>> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<std::basic_string<CharT>>(),
        .info = StringInfo{.charType = getFullyQualifiedNameOf<^^CharT>(),
                           .asUtf8StrGetter = [](const void* obj) -> ConstTmpObj {
                             // todo
                           },
                           .fromUtf8StrSetter =
                               [](void* obj, const char* data, std::size_t size) {
                                 //todo
                               }},
    };
  }
};
#endif

template <>
struct TypeInfoHolder<std::filesystem::path> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<std::filesystem::path>(),
        .info = StringInfo{.asUtf8StrGetter = [](const void* obj) -> ConstTmpObj {
                             return ConstTmpObj::makeOwned<std::u8string>(
                                 details::to<std::filesystem::path>(obj).generic_u8string());
                           },
                           .fromUtf8StrSetter =
                               [](void* obj, const char* data, std::size_t size) {
                                 details::to<std::filesystem::path>(obj) = std::string_view(data, size);
                               }},
    };
  }
};

template <class T>
  requires(!std::is_same_v<std::decay_t<T>, bool>)
struct TypeInfoHolder<std::vector<T>> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<std::vector<T>>(),
        .info = ListInfo{
            .valueType = getFullyQualifiedNameOf<^^T>(),
            .isSortable = true,
            .elemGetter = [](void* obj, std::size_t index) -> TmpObj {
              return TmpObj::fromPtrNonOwned(&details::to<std::vector<T>>(obj)[index]);
            },
            .elemGetterConst = [](const void* obj, std::size_t index) -> ConstTmpObj {
              return ConstTmpObj::fromPtrNonOwned(&details::to<std::vector<T>>(obj)[index]);
            },
            .sizeGetter = [](const void* obj) -> std::size_t { return details::to<std::vector<T>>(obj).size(); },
            .elemSetter = [](void* obj, std::size_t index,
                             void* data) { details::to<std::vector<T>>(obj)[index] = std::move(details::to<T>(data)); },
            .elemSwapper =
                [](void* obj, std::size_t indexA, std::size_t indexB) {
                  auto& list = details::to<std::vector<T>>(obj);
                  std::swap(list[indexA], list[indexB]);
                },
            .elemAdder = [](void* obj, std::size_t index) -> TmpObj {
              TmpObj newElem = getTypeInfo<T>().factory(obj, TmpObj::Ownership::Default);
              auto& list = details::to<std::vector<T>>(obj);
              return TmpObj::fromPtrNonOwned(
                  &*list.emplace(list.begin() + index, std::move(details::to<T>(newElem.obj))));
            },
            .elemEmplacer =
                [](void* obj, std::size_t index, void* data) {
                  auto& list = details::to<std::vector<T>>(obj);
                  list.emplace(list.begin() + index, std::move(details::to<T>(data)));
                },
            .elemDeleter =
                [](void* obj, std::size_t index) {
                  auto& list = details::to<std::vector<T>>(obj);
                  list.erase(list.begin() + index);
                },
            .clear = [](void* obj) { details::to<std::vector<T>>(obj).clear(); }},
    };
  }
};

template <class Key, class Value>
struct TypeInfoHolder<std::map<Key, Value>> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<std::map<Key, Value>>(),
        .info = DictInfo{
            .keyType = getFullyQualifiedNameOf<^^Key>(),
            .valueType = getFullyQualifiedNameOf<^^Value>(),
            .elemGetter = [](void* obj, const void* key) -> TmpObj {
              auto& dict = details::to<std::map<Key, Value>>(obj);
              auto it = dict.find(details::to<Key>(key));
              return it != dict.end() ? TmpObj::fromPtrNonOwned(details::from(it->second)) : TmpObj{};
            },
            .elemGetterConst = [](const void* obj, const void* key) -> ConstTmpObj {
              const auto& dict = details::to<std::map<Key, Value>>(obj);
              auto it = dict.find(details::to<Key>(key));
              return it != dict.end() ? ConstTmpObj::fromPtrNonOwned(details::from(it->second)) : ConstTmpObj{};
            },
            .kvpGetter = [](void* obj, std::size_t index) -> KeyValuePair {
              auto it = details::to<std::map<Key, Value>>(obj).begin();
              std::advance(it, index);
              return {details::from(it->first), details::from(it->second)};
            },
            .kvpGetterConst = [](const void* obj, std::size_t index) -> ConstKeyValuePair {
              auto it = details::to<std::map<Key, Value>>(obj).begin();
              std::advance(it, index);
              return {details::from(it->first), details::from(it->second)};
            },
            .sizeGetter = [](const void* obj) -> std::size_t { return details::to<std::map<Key, Value>>(obj).size(); },
            .elemSetter =
                [](void* obj, const void* key, void* data) {
                  details::to<std::map<Key, Value>>(obj).at(details::to<Key>(key)) =
                      std::move(details::to<Value>(data));
                },
            .elemAdder = [](void* obj, void* key) -> TmpObj {
              TmpObj newElem = getTypeInfo<Value>().factory(obj, TmpObj::Ownership::Default);
              auto& dict = details::to<std::map<Key, Value>>(obj);
              return TmpObj::fromPtrNonOwned(
                  &dict.emplace(std::move(details::to<Key>(key)), std::move(details::to<Value>(newElem.obj)))
                       .first->second);
            },
            .elemEmplacer = [](void* obj, void* key, void* data) -> std::size_t {
              auto& dict = details::to<std::map<Key, Value>>(obj);
              auto it = dict.emplace(std::move(details::to<Key>(key)), std::move(details::to<Value>(data))).first;
              return std::distance(dict.begin(), it);
            },
            .elemDeleter = [](void* obj, const void* key) -> std::size_t {
              auto& dict = details::to<std::map<Key, Value>>(obj);
              auto it = dict.find(details::to<Key>(key));
              auto newIt = dict.erase(it);
              return std::distance(dict.begin(), newIt);
            },
            .kvpDeleter = [](void* obj, std::size_t index) -> std::size_t {
              auto& dict = details::to<std::map<Key, Value>>(obj);
              auto it = dict.begin();
              std::advance(it, index);
              auto newIt = dict.erase(it);
              return std::distance(dict.begin(), newIt);
            },
            .clear = [](void* obj) { details::to<std::map<Key, Value>>(obj).clear(); }},
    };
  }
};

template <class T>
struct TypeInfoHolder<std::unique_ptr<T>> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<std::unique_ptr<T>>(),
        .info = PtrInfo{
            .innerType = getFullyQualifiedNameOf<^^T>(),
            .getter = [](void* obj) -> TmpObj {
              return TmpObj::fromPtrNonOwned(details::to<std::unique_ptr<T>>(obj).get());
            },
            .getterConst = [](const void* obj) -> ConstTmpObj {
              return ConstTmpObj::fromPtrNonOwned(details::to<std::unique_ptr<T>>(obj).get());
            },
            .setter = [](void* obj, void* ptr) { details::to<std::unique_ptr<T>>(obj).reset(&details::to<T>(ptr)); },
            .emplacer = [](void* obj) -> TmpObj {
              TmpObj newDataTmpObj = getTypeInfo<T>().factory(obj, TmpObj::Ownership::NonOwned);
              details::to<std::unique_ptr<T>>(obj).reset(&details::to<T>(newDataTmpObj.obj));
            }},
    };
  }
};

template <class T>
struct TypeInfoHolder<std::shared_ptr<T>> {
  static TypeInfo getTypeInfo() {
    return {
        .factory = details::getBasicFactory<std::shared_ptr<T>>(),
        .info = PtrInfo{
            .innerType = getFullyQualifiedNameOf<^^T>(),
            .getter = [](void* obj) -> TmpObj {
              return TmpObj::fromPtrNonOwned(details::to<std::shared_ptr<T>>(obj).get());
            },
            .getterConst = [](const void* obj) -> ConstTmpObj {
              return ConstTmpObj::fromPtrNonOwned(details::to<std::shared_ptr<T>>(obj).get());
            },
            .setter = [](void* obj, void* ptr) { details::to<std::shared_ptr<T>>(obj).reset(&details::to<T>(ptr)); },
            .emplacer = [](void* obj) -> TmpObj {
              TmpObj newDataTmpObj = getTypeInfo<T>().factory(obj, TmpObj::Ownership::NonOwned);
              details::to<std::shared_ptr<T>>(obj).reset(&details::to<T>(newDataTmpObj.obj));
            }},
    };
  }
};
}  // namespace loki::core

LOKI_REFLECTION_TEMPLATE_2_CLASS_BEGIN(std::pair)
LOKI_REFLECTION_CLASS_FIELD(first)
LOKI_REFLECTION_CLASS_FIELD(second)
LOKI_REFLECTION_CLASS_END()
