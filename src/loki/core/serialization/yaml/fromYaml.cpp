#include "fromYaml.hpp"

#include <cassert>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/runtimeObject/RuntimeObjectRegistry.hpp>
#include <loki/core/serialization/string/toString.hpp>
#include <loki/core/services/ServiceRegistry.hpp>

namespace loki::core {

using details::to;

void fromYaml(const YAML::Node&, void* obj, const NullInfo&) {
  to<std::nullptr_t>(obj) = nullptr;
}

void fromYaml(const YAML::Node& node, void* obj, const BooleanInfo&) {
  to<bool>(obj) = node.as<bool>();
}

void fromYaml(const YAML::Node& node, void* obj, const IntegerInfo& integerInfo) {
  unsigned int size = integerInfo.size;
  if (integerInfo.isUnsigned) {
    if (size == sizeof(uint8_t)) {
      to<uint8_t>(obj) = node.as<uint8_t>();
    } else if (size == sizeof(uint16_t)) {
      to<uint16_t>(obj) = node.as<uint16_t>();
    } else if (size == sizeof(uint32_t)) {
      to<uint32_t>(obj) = node.as<uint32_t>();
    } else if (size == sizeof(uint64_t)) {
      to<uint64_t>(obj) = node.as<uint64_t>();
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (size == sizeof(int8_t)) {
      to<int8_t>(obj) = node.as<int8_t>();
    } else if (size == sizeof(int16_t)) {
      to<int16_t>(obj) = node.as<int16_t>();
    } else if (size == sizeof(int32_t)) {
      to<int32_t>(obj) = node.as<int32_t>();
    } else if (size == sizeof(int64_t)) {
      to<int64_t>(obj) = node.as<int64_t>();
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
}

void fromYaml(const YAML::Node& node, void* obj, const FloatingPointInfo& floatingPointInfo) {
  unsigned int size = floatingPointInfo.size;
  if (size == sizeof(float)) {
    to<float>(obj) = node.as<float>();
  } else if (size == sizeof(double)) {
    to<double>(obj) = node.as<double>();
  } else if (size == sizeof(long double)) {
    to<long double>(obj) = node.as<long double>();
  } else {
    assert(false && "Unknown floating point size!");
  }
}

void fromYaml(const YAML::Node& node, void* obj, const EnumInfo& enumInfo) {
  // find the value corresponding to the enumerator
  std::int64_t value = 0;
  auto str = node.as<std::string>();
  auto it = std::ranges::find_if(enumInfo.enumerators,
                                 [&str](const EnumeratorInfo& enumeratorInfo) { return enumeratorInfo.name == str; });
  if (it != enumInfo.enumerators.end())
    value = it->value;
  // assign it to the obj
  unsigned int size = enumInfo.backingType.size;
  if (enumInfo.backingType.isUnsigned) {
    if (size == sizeof(uint8_t)) {
      to<uint8_t>(obj) = static_cast<uint8_t>(value);
    } else if (size == sizeof(uint16_t)) {
      to<uint16_t>(obj) = static_cast<uint16_t>(value);
    } else if (size == sizeof(uint32_t)) {
      to<uint32_t>(obj) = static_cast<uint32_t>(value);
    } else if (size == sizeof(uint64_t)) {
      to<uint64_t>(obj) = static_cast<uint64_t>(value);
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (size == sizeof(int8_t)) {
      to<int8_t>(obj) = static_cast<int8_t>(value);
    } else if (size == sizeof(int16_t)) {
      to<int16_t>(obj) = static_cast<int16_t>(value);
    } else if (size == sizeof(int32_t)) {
      to<int32_t>(obj) = static_cast<int32_t>(value);
    } else if (size == sizeof(int64_t)) {
      to<int64_t>(obj) = value;
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
}

void fromYaml(const YAML::Node& node, void* obj, const CharacterInfo& characterInfo) {
  // todo others
  assert(!characterInfo.isUnicode && characterInfo.size == sizeof(char) && "Only char is supported for now!");
  to<char>(obj) = node.as<char>();
}

void fromYaml(const YAML::Node& node, void* obj, const StringInfo& stringInfo) {
  // todo others
  assert(!stringInfo.charType.isUnicode && stringInfo.charType.size == sizeof(char) &&
         "Only char is supported for now!");
  auto str = node.as<std::string>();
  stringInfo.setter(obj, str.data(), str.size());
}

void fromYaml(const YAML::Node& node, void* obj, const ListInfo& listInfo) {
  std::size_t nodeListSize = node.size();
  std::size_t objListSize = listInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < nodeListSize; ++index) {
    auto child = node[index];
    TmpObj tmpObj;
    if (index >= objListSize) {
      tmpObj = listInfo.elemAdder(obj, index);
      ++objListSize;
    } else {
      tmpObj = listInfo.elemGetter(obj, index);
    }
    fromYaml(child, tmpObj.obj, listInfo.valueType);
  }
}

void fromYaml(const YAML::Node& node, void* obj, const DictInfo& dictInfo) {
  for (const auto& child : node) {
    const auto& key = child.first;
    const auto& value = child.second;
    TmpObj tmpObj;
    {
      TmpObj keyInstance = dictInfo.keyType.factory(obj, TmpObj::Ownership::Default);
      fromYaml(key, keyInstance.obj, dictInfo.keyType);
      tmpObj = dictInfo.elemAdder(obj, keyInstance.obj);
    }
    fromYaml(value, tmpObj.obj, dictInfo.valueType);
  }
}

void fromYaml(const YAML::Node& node, void* obj, const ClassInfo& classInfo) {
  for (const auto& field : classInfo.fields) {
    auto child = node[field.name];
    if (!child)
      continue;  // ignore absent values
    if (field.isInPlace) {
      TmpObj fieldObj = field.getter(obj);
      fromYaml(child, fieldObj.obj, field.type);
    } else {
      TmpObj fieldObj = field.type.factory(obj, TmpObj::Ownership::Owned);
      fromYaml(child, fieldObj.obj, field.type);
      field.setter(obj, fieldObj.obj);
    }
  }
}

void fromYaml(const YAML::Node& node, void* obj, const PtrInfo& ptrInfo) {
  if (std::holds_alternative<ClassInfo>(ptrInfo.innerType.info)) {
    const TypeInfo* actualTypeInfo =
        getService<RuntimeObjectRegistry>().getRuntimeTypeInfo(node["__type__"].as<ClassId>());
    assert(actualTypeInfo);
    TmpObj data = actualTypeInfo->factory(obj, TmpObj::Ownership::NonOwned);
    fromYaml(node, data.obj, *actualTypeInfo);
    ptrInfo.setter(obj, asAncestor(data.obj, actualTypeInfo, std::get<ClassInfo>(ptrInfo.innerType.info).id));
  } else {
    TmpObj inner = ptrInfo.emplacer(obj);
    fromYaml(node, inner.obj, ptrInfo.innerType);
  }
}

void fromYaml(const YAML::Node& node, void* obj, const TypeInfo& typeInfo) {
  std::visit([&](const auto& actualTypeInfo) { fromYaml(node, obj, actualTypeInfo); }, typeInfo.info);
}
}  // namespace loki::core