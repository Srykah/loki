#include "toString.hpp"

#include <cassert>

#include <fmt/format.h>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/rtti/BaseObject.hpp>

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
  auto it = std::ranges::find_if(
      enumInfo.enumerators, [value](const EnumeratorInfo& enumeratorInfo) { return enumeratorInfo.value == value; });
  if (it != enumInfo.enumerators.end()) {
    str += '"';
    str += it->name;
    str += '"';
  } else {
    str += value;
  }
}

void toString(std::string& str, const void* obj, const CharacterInfo& characterInfo) {
  str += '\'';
  str += to<char>(obj);
  str += '\'';
}

void toString(std::string& str, const void* obj, const StringInfo& stringInfo) {
  str += '"';
  str += to<std::string>(stringInfo.asUtf8StrGetter(obj).obj);
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
  bool asValue = std::ranges::find_if(classInfo.attributes, [](const auto& attr) {
                   return attr->getType() == ClassAttribute::Type::SerializeAsValue;
                 }) != classInfo.attributes.end();
  if (asValue) {
    const auto& field = classInfo.fields.at(0);
    ConstTmpObj tmpObj = field.getterConst(obj);
    toString(str, tmpObj.obj, field.type);
  } else {
    str += '{';
    if (classInfo.parentType) {
      auto rootTypeInfo = classInfo.parentType;
      while (std::get<ClassInfo>(rootTypeInfo->info).parentType != nullptr)
        rootTypeInfo = std::get<ClassInfo>(rootTypeInfo->info).parentType;
      if (std::get<ClassInfo>(rootTypeInfo->info).id == std::get<ClassInfo>(getTypeInfo<BaseObject>().info).id)
        str += fmt::format(R"("__type__": {}, )", classInfo.id);  // only write type for polymorphic types
    }
    for (const auto& field : classInfo.fields) {
      str += fmt::format(R"("{}": )", field.name);
      TmpObj fieldObj = field.getter(const_cast<void*>(obj));
      toString(str, fieldObj.obj, field.type);
      str += ", ";
    }
    if (!classInfo.fields.empty())
      str.resize(str.size() - 2);  // remove trailing comma and space
    str += " }";
  }
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