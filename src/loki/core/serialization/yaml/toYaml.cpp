#include "toYaml.hpp"

#include <cassert>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/runtimeObject/BaseObject.hpp>
#include <loki/core/serialization/string/toString.hpp>

namespace loki::core {

using details::to;

void toYaml(YAML::Node& node, const void*, const NullInfo&) {
  node.reset();
}

void toYaml(YAML::Node& node, const void* obj, const BooleanInfo&) {
  node = to<bool>(obj);
}

void toYaml(YAML::Node& node, const void* obj, const IntegerInfo& integerInfo) {
  if (integerInfo.isUnsigned) {
    if (integerInfo.size == sizeof(uint8_t)) {
      node = to<uint8_t>(obj);
    } else if (integerInfo.size == sizeof(uint16_t)) {
      node = to<uint16_t>(obj);
    } else if (integerInfo.size == sizeof(uint32_t)) {
      node = to<uint32_t>(obj);
    } else if (integerInfo.size == sizeof(uint64_t)) {
      node = to<uint64_t>(obj);
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (integerInfo.size == sizeof(int8_t)) {
      node = to<int8_t>(obj);
    } else if (integerInfo.size == sizeof(int16_t)) {
      node = to<int16_t>(obj);
    } else if (integerInfo.size == sizeof(int32_t)) {
      node = to<int32_t>(obj);
    } else if (integerInfo.size == sizeof(int64_t)) {
      node = to<int64_t>(obj);
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
}

void toYaml(YAML::Node& node, const void* obj, const FloatingPointInfo& floatingPointInfo) {
  if (floatingPointInfo.size == sizeof(float)) {
    node = to<float>(obj);
  } else if (floatingPointInfo.size == sizeof(double)) {
    node = to<double>(obj);
  } else if (floatingPointInfo.size == sizeof(long double)) {
    node = to<long double>(obj);
  } else {
    assert(false && "Unknown floating point size!");
  }
}

void toYaml(YAML::Node& node, const void* obj, const EnumInfo& enumInfo) {
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
  if (it != enumInfo.enumerators.end())
    node = it->name;
  else
    node = "<unnamed>";
}

void toYaml(YAML::Node& node, const void* obj, const CharacterInfo& characterInfo) {
  // todo others
  assert(!characterInfo.isUnicode && characterInfo.size == sizeof(char) && "Only char is supported for now!");
  node = to<char>(obj);
}

void toYaml(YAML::Node& node, const void* obj, const StringInfo& stringInfo) {
  // todo others
  assert(!stringInfo.charType.isUnicode && stringInfo.charType.size == sizeof(char) &&
         "Only char is supported for now!");
  node = details::to<std::string>(stringInfo.asUtf8StrGetter(obj).obj);
}

void toYaml(YAML::Node& node, const void* obj, const ListInfo& listInfo) {
  const std::size_t listSize = listInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < listSize; ++index) {
    auto child = node[index];  // will push_back automatically
    ConstTmpObj tmpObj = listInfo.elemGetterConst(obj, index);
    toYaml(child, tmpObj.obj, listInfo.valueType);
  }
}

void toYaml(YAML::Node& node, const void* obj, const DictInfo& dictInfo) {
  const std::size_t dictSize = dictInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < dictSize; ++index) {
    auto [key, value] = dictInfo.kvpGetterConst(obj, index);
    std::string keyStr;
    toString(keyStr, key, dictInfo.keyType);
    auto child = node[keyStr];
    toYaml(child, value, dictInfo.valueType);
  }
}

void toYaml(YAML::Node& node, const void* obj, const ClassInfo& classInfo) {
  node["__type__"] = classInfo.id;
  for (const auto& field : classInfo.fields) {
    auto child = node[field.name];
    ConstTmpObj tmpObj = field.getterConst(obj);
    toYaml(child, tmpObj.obj, field.type);
  }
}

void toYaml(YAML::Node& node, const void* obj, const PtrInfo& ptrInfo) {
  ConstTmpObj tmpObj = ptrInfo.getterConst(obj);
  auto* baseObj = static_cast<const BaseObject*>(tmpObj.obj);
  toYaml(node, baseObj, baseObj->getClassTypeInfo());
}

void toYaml(YAML::Node& node, const void* obj, const TypeInfo& typeInfo) {
  std::visit([&](const auto& actualTypeInfo) { toYaml(node, obj, actualTypeInfo); }, typeInfo.info);
}
}  // namespace loki::core