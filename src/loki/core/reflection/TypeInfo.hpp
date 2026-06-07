#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include <loki/core/reflection/Annotation.hpp>
#include <loki/core/utils/TmpObj.hpp>

namespace loki::core {
using TypeId = std::string;
using NameId = std::string;

struct NullInfo {};
struct BooleanInfo {};
struct IntegerInfo {
  bool isUnsigned;
  std::uint8_t size;
};
struct FloatingPointInfo {
  std::uint8_t size;
};
struct EnumeratorInfo {
  NameId name;
  std::int64_t value;
  std::vector<std::unique_ptr<Annotation>> annotations;
};
struct EnumInfo {
  TypeId underlyingType;
  std::vector<EnumeratorInfo> enumerators;
  std::vector<std::unique_ptr<Annotation>> annotations;
};
struct CharacterInfo {
  std::uint8_t size;
  bool isUnicode;
};
struct StringInfo {
  TypeId charType;
  std::function<ConstTmpObj(const void* obj)> asUtf8StrGetter;
  std::function<void(void* obj, const char* data, std::size_t size)> fromUtf8StrSetter;
};
struct ListInfo {
  TypeId valueType;
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
  TypeId keyType;
  TypeId valueType;
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
  TypeId type;
  NameId name;
  std::ptrdiff_t offset = -1z;
  std::function<TmpObj(void* parent)> getter;
  std::function<ConstTmpObj(const void* parent)> getterConst;
  std::function<void(void* parent, void* data)> setter;
  std::vector<std::unique_ptr<Annotation>> annotations;
};
struct ClassInfo {
  TypeId parentType;
  std::function<void*(void* obj)> toParentType;
  std::vector<FieldInfo> fields;
  std::vector<std::unique_ptr<Annotation>> annotations;
};
struct PtrInfo {
  TypeId innerType;
  std::function<TmpObj(void* obj)> getter;
  std::function<ConstTmpObj(const void* obj)> getterConst;
  std::function<void(void* obj, void* data)> setter;
  std::function<TmpObj(void* obj)> emplacer;
  std::function<void(void* obj)> clear;
};

struct TypeInfo {
  TypeId id;
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

  template <class T>
  const T& as() const {
    return std::get<T>(info);
  }
};

}  // namespace loki::core