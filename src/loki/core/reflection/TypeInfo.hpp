#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include <loki/core/utils/TmpObj.hpp>

namespace loki::core {
struct TypeInfo;
using ClassId = std::string;
using Factory = std::function<TmpObj(void* ctx, TmpObj::Ownership)>;

struct NullInfo {};
struct BooleanInfo {};
struct IntegerInfo {
  bool isUnsigned;
  unsigned int size;
};
struct FloatingPointInfo {
  unsigned int size;
};
struct EnumeratorInfo {
  std::string_view name;
  std::int64_t value;
};
struct EnumInfo {
  const IntegerInfo& backingType;
  std::vector<EnumeratorInfo> enumerators;
};
struct CharacterInfo {
  bool isUnicode;
  unsigned int size;
};
struct StringInfo {
  const CharacterInfo& charType;
  std::function<ConstTmpObj(const void* obj)> asUtf8StrGetter;
  std::function<void(void* obj, const char* data, std::size_t size)> setter;
};
struct ListInfo {
  const TypeInfo& valueType;
  bool isSortable;
  std::function<TmpObj(void* obj, std::size_t index)> elemGetter;
  std::function<ConstTmpObj(const void* obj, std::size_t index)> elemGetterConst;
  std::function<std::size_t(const void* obj)> sizeGetter;
  std::function<void(void* obj, std::size_t index, void* data)> elemSetter;
  std::function<void(void* obj, std::size_t indexA, std::size_t indexB)> elemSwapper;
  std::function<TmpObj(void* obj, std::size_t index)> elemAdder;
  std::function<void(void* obj, std::size_t index, void* data)> elemEmplacer;
  std::function<void(void* obj, std::size_t index)> elemDeleter;
  std::function<void(void* obj)> clear;
};
struct KeyValuePair {
  const void* key = nullptr;
  void* value = nullptr;
};
struct ConstKeyValuePair {
  const void* key = nullptr;
  const void* value = nullptr;
};
struct DictInfo {
  const TypeInfo& keyType;
  const TypeInfo& valueType;
  std::function<TmpObj(void* obj, const void* key)> elemGetter;
  std::function<ConstTmpObj(const void* obj, const void* key)> elemGetterConst;
  std::function<KeyValuePair(void* obj, std::size_t index)> kvpGetter;
  std::function<ConstKeyValuePair(const void* obj, std::size_t index)> kvpGetterConst;
  std::function<std::size_t(const void* obj)> sizeGetter;
  std::function<void(void* obj, const void* key, void* data)> elemSetter;
  std::function<TmpObj(void* obj, void* key)> elemAdder;
  std::function<std::size_t(void* obj, void* key, void* data)> elemEmplacer;
  std::function<std::size_t(void* obj, const void* key)> elemDeleter;
  std::function<std::size_t(void* obj, std::size_t index)> kvpDeleter;
  std::function<void(void* obj)> clear;
};
struct FieldInfo {
  const TypeInfo& type;
  std::string_view name;
  bool isInPlace = true;
  std::function<TmpObj(void* parent)> getter;
  std::function<ConstTmpObj(const void* parent)> getterConst;
  std::function<void(void* parent, void* data)> setter;
};
struct ClassInfo {
  ClassId id;
  const TypeInfo* parentType = nullptr;
  std::function<void*(void* obj)> toParentType;
  std::vector<FieldInfo> fields;
};
struct PtrInfo {
  const TypeInfo& innerType;
  std::function<TmpObj(void* obj)> getter;
  std::function<ConstTmpObj(const void* obj)> getterConst;
  std::function<void(void* obj, void* data)> setter;
  std::function<TmpObj(void* obj)> emplacer;
  std::function<void(void* obj)> clear;
};

struct TypeInfo {
  Factory factory;
  std::variant<NullInfo,
               BooleanInfo,
               IntegerInfo,
               FloatingPointInfo,
               EnumInfo,
               CharacterInfo,
               StringInfo,
               ListInfo,
               DictInfo,
               ClassInfo,
               PtrInfo>
      info;
};

template <class T>
struct TypeInfoHolder;

template <class T>
concept Reflected = requires { TypeInfoHolder<T>::getTypeInfo_internal(); };

template <Reflected T>
const TypeInfo& getTypeInfo() {
  return TypeInfoHolder<T>::getTypeInfo_internal();
}
}  // namespace loki::core