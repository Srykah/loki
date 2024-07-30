#include "toString.hpp"

#include <cassert>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/runtimeObject/BaseObject.hpp>

namespace loki::core {

using details::to;

void toString(std::string& str, const void*, const NullInfo&) {
  str += "null";
}

void toString(std::string& str, const void* obj, const BooleanInfo&) {
  str += to<bool>(obj) ? "true" : "false";
}

void toString(std::string& str, const void* obj, const IntegerInfo& integerInfo) {
  unsigned int size = integerInfo.size;
  if (integerInfo.isUnsigned) {
    if (size == sizeof(uint8_t)) {
      str += std::to_string(to<uint8_t>(obj));
    } else if (size == sizeof(uint16_t)) {
      str += std::to_string(to<uint16_t>(obj));
    } else if (size == sizeof(uint32_t)) {
      str += std::to_string(to<uint32_t>(obj));
    } else if (size == sizeof(uint64_t)) {
      str += std::to_string(to<uint64_t>(obj));
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (size == sizeof(int8_t)) {
      str += std::to_string(to<int8_t>(obj));
    } else if (size == sizeof(int16_t)) {
      str += std::to_string(to<int16_t>(obj));
    } else if (size == sizeof(int32_t)) {
      str += std::to_string(to<int32_t>(obj));
    } else if (size == sizeof(int64_t)) {
      str += std::to_string(to<int64_t>(obj));
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
}

void toString(std::string& str, const void* obj, const FloatingPointInfo& floatingPointInfo) {
  unsigned int size = floatingPointInfo.size;
  if (size == sizeof(float)) {
    str += std::to_string(to<float>(obj));
  } else if (size == sizeof(double)) {
    str += std::to_string(to<double>(obj));
  } else if (size == sizeof(long double)) {
    str += std::to_string(to<long double>(obj));
  } else {
    assert(false && "Unknown floating point size!");
  }
}

void toString(std::string& str, const void* obj, const EnumInfo& enumInfo) {
  // first, get the value as a int64_t
  std::int64_t value = 0;
  unsigned int size = enumInfo.backingType.size;
  if (enumInfo.backingType.isUnsigned) {
    if (size == sizeof(uint8_t)) {
      value = static_cast<std::int64_t>(to<uint8_t>(obj));
    } else if (size == sizeof(uint16_t)) {
      value = static_cast<std::int64_t>(to<uint16_t>(obj));
    } else if (size == sizeof(uint32_t)) {
      value = static_cast<std::int64_t>(to<uint32_t>(obj));
    } else if (size == sizeof(uint64_t)) {
      value = static_cast<std::int64_t>(to<uint64_t>(obj));
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (size == sizeof(int8_t)) {
      value = static_cast<std::int64_t>(to<int8_t>(obj));
    } else if (size == sizeof(int16_t)) {
      value = static_cast<std::int64_t>(to<int16_t>(obj));
    } else if (size == sizeof(int32_t)) {
      value = static_cast<std::int64_t>(to<int32_t>(obj));
    } else if (size == sizeof(int64_t)) {
      value = to<int64_t>(obj);
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
  // then, find the name of the enumerator with that value
  auto it = std::find_if(enumInfo.enumerators.begin(), enumInfo.enumerators.end(),
                         [value](const EnumeratorInfo& enumeratorInfo) { return enumeratorInfo.value == value; });
  if (it != enumInfo.enumerators.end())
    str += it->name;
  else
    str += "<unnamed>";
}

void toString(std::string& str, const void* obj, const CharacterInfo& characterInfo) {
  str += '\'';
  unsigned int size = characterInfo.size;
  if (characterInfo.isUnicode) {
    if (size == sizeof(char8_t)) {
      str += std::to_string(to<char8_t>(obj));
    } else if (size == sizeof(char16_t)) {
      str += std::to_string(to<char16_t>(obj));
    } else if (size == sizeof(char32_t)) {
      str += std::to_string(to<char32_t>(obj));
    } else {
      assert(false && "Unknown unicode character size!");
    }
  } else {
    if (size == sizeof(char)) {
      str += to<char>(obj);
    } else {
      assert(false && "Unknown non-unicode character size!");
    }
  }
  str += '\'';
}

void toString(std::string& str, const void* obj, const StringInfo& stringInfo) {
  // todo others
  assert(!stringInfo.charType.isUnicode && stringInfo.charType.size == sizeof(char) &&
         "Only char is supported for now!");
  str += '"';
  str += details::to<std::string>(stringInfo.asUtf8StrGetter(obj).obj);
  str += '"';
}

void toString(std::string& str, const void* obj, const ListInfo& listInfo) {
  str += '[';
  const std::size_t listSize = listInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < listSize; ++index) {
    TmpObj elem = listInfo.elemGetter(const_cast<void*>(obj), index);
    toString(str, elem.obj, listInfo.valueType);
    str += ", ";
  }
  if (listSize > 0)
    str.resize(str.size() - 2);  // remove trailing comma and space
  str += ']';
}

void toString(std::string& str, const void* obj, const DictInfo& dictInfo) {
  str += "{ ";
  const std::size_t dictSize = dictInfo.sizeGetter(obj);
  const bool isKeyNotAString = !std::holds_alternative<StringInfo>(dictInfo.keyType.info);
  for (std::size_t index = 0; index < dictSize; ++index) {
    auto [key, value] = dictInfo.kvpGetter(const_cast<void*>(obj), index);
    if (isKeyNotAString)
      str += '"';
    toString(str, key, dictInfo.keyType);
    if (isKeyNotAString)
      str += '"';
    str += ": ";
    toString(str, value, dictInfo.valueType);
    str += ", ";
  }
  if (dictSize > 0)
    str.resize(str.size() - 2);  // remove trailing comma and space
  str += " }";
}

void toString(std::string& str, const void* obj, const ClassInfo& classInfo) {
  str += R"({ "__type__": ")";
  str += classInfo.id;
  str += R"(", )";
  for (const auto& field : classInfo.fields) {
    str += '"';
    str += field.name;
    str += R"(": )";
    TmpObj fieldObj = field.getter(const_cast<void*>(obj));
    toString(str, fieldObj.obj, field.type);
    str += ", ";
  }
  if (!classInfo.fields.empty())
    str.resize(str.size() - 2);  // remove trailing comma and space
  str += " }";
}

void toString(std::string& str, const void* obj, const PtrInfo& ptrInfo) {
  TmpObj inner = ptrInfo.getter(const_cast<void*>(obj));
  auto* baseObj = static_cast<BaseObject*>(inner.obj);
  toString(str, baseObj, baseObj->getClassTypeInfo());
}

void toString(std::string& str, const void* obj, const TypeInfo& typeInfo) {
  std::visit([&](const auto& actualTypeInfo) { toString(str, obj, actualTypeInfo); }, typeInfo.info);
}
}  // namespace loki::core