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
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo NULL_TYPEINFO{.factory = [](void*, TmpObj::Ownership) -> TmpObj { return TmpObj{}; },
                                  .info = NullInfo{}};
    return NULL_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<bool> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo BOOLEAN_TYPEINFO{.factory = details::getBasicFactory<bool>(), .info = BooleanInfo{}};
    return BOOLEAN_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<uint8_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo UINT8_TYPEINFO{.factory = details::getBasicFactory<uint8_t>(),
                                   .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint8_t)}};
    return UINT8_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<uint16_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo UINT16_TYPEINFO{.factory = details::getBasicFactory<uint16_t>(),
                                    .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint16_t)}};
    return UINT16_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<uint32_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo UINT32_TYPEINFO{.factory = details::getBasicFactory<uint32_t>(),
                                    .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint32_t)}};
    return UINT32_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<uint64_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo UINT64_TYPEINFO{.factory = details::getBasicFactory<uint64_t>(),
                                    .info = IntegerInfo{.isUnsigned = true, .size = sizeof(uint64_t)}};
    return UINT64_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<int8_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo INT8_TYPEINFO{.factory = details::getBasicFactory<int8_t>(),
                                  .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int8_t)}};
    return INT8_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<int16_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo INT16_TYPEINFO{.factory = details::getBasicFactory<int16_t>(),
                                   .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int16_t)}};
    return INT16_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<int32_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo INT32_TYPEINFO{.factory = details::getBasicFactory<int32_t>(),
                                   .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int32_t)}};
    return INT32_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<int64_t> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo INT64_TYPEINFO{.factory = details::getBasicFactory<int64_t>(),
                                   .info = IntegerInfo{.isUnsigned = false, .size = sizeof(int64_t)}};
    return INT64_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<float> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo FLOAT_TYPEINFO{.factory = details::getBasicFactory<float>(),
                                   .info = FloatingPointInfo{.size = sizeof(float)}};
    return FLOAT_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<double> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo DOUBLE_TYPEINFO{.factory = details::getBasicFactory<double>(),
                                    .info = FloatingPointInfo{.size = sizeof(double)}};
    return DOUBLE_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<long double> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo LONGDOUBLE_TYPEINFO{.factory = details::getBasicFactory<long double>(),
                                        .info = FloatingPointInfo{.size = sizeof(long double)}};
    return LONGDOUBLE_TYPEINFO;
  }
};

template <>
struct TypeInfoHolder<char> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo CHAR_INFO{
        .factory = details::getBasicFactory<char>(),
        .info = CharacterInfo{},
    };
    return CHAR_INFO;
  }
};

template <>
struct TypeInfoHolder<std::string> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo STRING_INFO{
        .factory = details::getBasicFactory<std::string>(),
        .info = StringInfo{
            .asUtf8StrGetter = [](const void* obj) -> ConstTmpObj {
              return ConstTmpObj::fromPtrNonOwned(&details::to<std::string>(obj));
            },
            .setter = [](void* obj, const char* data,
                         std::size_t size) { details::to<std::string>(obj) = std::string_view(data, size); }},
    };
    return STRING_INFO;
  }
};

template <>
struct TypeInfoHolder<std::filesystem::path> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo STRING_INFO{
        .factory = details::getBasicFactory<std::filesystem::path>(),
        .info = StringInfo{
            .asUtf8StrGetter = [](const void* obj) -> ConstTmpObj {
              return ConstTmpObj::makeOwned<std::string>(details::to<std::filesystem::path>(obj).generic_string());
            },
            .setter = [](void* obj, const char* data,
                         std::size_t size) { details::to<std::filesystem::path>(obj) = std::string_view(data, size); }},
    };
    return STRING_INFO;
  }
};

template <Reflected T>
  requires(!std::is_same_v<std::decay_t<T>, bool>)
struct TypeInfoHolder<std::vector<T>> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo VECTOR_INFO{
        .factory = details::getBasicFactory<std::vector<T>>(),
        .info = ListInfo{
            .valueType = getTypeInfo<T>(),
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
    return VECTOR_INFO;
  }
};

template <Reflected Key, Reflected Value>
struct TypeInfoHolder<std::map<Key, Value>> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo MAP_INFO{
        .factory = details::getBasicFactory<std::map<Key, Value>>(),
        .info = DictInfo{
            .keyType = getTypeInfo<Key>(),
            .valueType = getTypeInfo<Value>(),
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
    return MAP_INFO;
  }
};

template <Reflected T>
struct TypeInfoHolder<std::unique_ptr<T>> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo PTR_INFO{
        .factory = details::getBasicFactory<std::unique_ptr<T>>(),
        .info = PtrInfo{
            .innerType = getTypeInfo<T>(),
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
              return newDataTmpObj;
            }},
    };
    return PTR_INFO;
  }
};

template <Reflected T>
struct TypeInfoHolder<std::shared_ptr<T>> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo PTR_INFO{
        .factory = details::getBasicFactory<std::shared_ptr<T>>(),
        .info = PtrInfo{
            .innerType = getTypeInfo<T>(),
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
              return newDataTmpObj;
            }},
    };
    return PTR_INFO;
  }
};
}  // namespace loki::core

LOKI_REFLECTION_TEMPLATE_2_CLASS_BEGIN(std::pair)
LOKI_REFLECTION_CLASS_FIELD(first)
LOKI_REFLECTION_CLASS_FIELD(second)
LOKI_REFLECTION_CLASS_END()
