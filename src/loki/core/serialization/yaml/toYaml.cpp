#include "toYaml.hpp"

#include <cassert>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/rtti/BaseObject.hpp>

namespace loki::core {

using details::to;

void toYaml(ryml::NodeRef destNode, const void*, const TypeId&, const NullInfo&) {
  destNode << nullptr;
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const BooleanInfo&) {
  destNode << to<bool>(obj);
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const IntegerInfo& integerInfo) {
  if (integerInfo.isUnsigned) {
    if (integerInfo.size == sizeof(uint8_t)) {
      destNode << to<uint8_t>(obj);
    } else if (integerInfo.size == sizeof(uint16_t)) {
      destNode << to<uint16_t>(obj);
    } else if (integerInfo.size == sizeof(uint32_t)) {
      destNode << to<uint32_t>(obj);
    } else if (integerInfo.size == sizeof(uint64_t)) {
      destNode << to<uint64_t>(obj);
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (integerInfo.size == sizeof(int8_t)) {
      destNode << to<int8_t>(obj);
    } else if (integerInfo.size == sizeof(int16_t)) {
      destNode << to<int16_t>(obj);
    } else if (integerInfo.size == sizeof(int32_t)) {
      destNode << to<int32_t>(obj);
    } else if (integerInfo.size == sizeof(int64_t)) {
      destNode << to<int64_t>(obj);
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const FloatingPointInfo& floatingPointInfo) {
  if (floatingPointInfo.size == sizeof(float)) {
    destNode << to<float>(obj);
  } else if (floatingPointInfo.size == sizeof(double)) {
    destNode << to<double>(obj);
  } else if (floatingPointInfo.size == sizeof(long double)) {
    assert(false && "Can't emit a long double!");
  } else {
    assert(false && "Unknown floating point size!");
  }
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const EnumInfo& enumInfo) {
  const auto& underlyingTypeInfo = getTypeInfoFromId(enumInfo.underlyingType).as<IntegerInfo>();
  // first, get the value as a int64_t
  std::int64_t value = 0;
  unsigned int size = underlyingTypeInfo.size;
  if (underlyingTypeInfo.isUnsigned) {
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
    destNode << it->name.data();
  else
    destNode << value;
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const CharacterInfo& characterInfo) {
  destNode << to<char>(obj);
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const StringInfo& stringInfo) {
  destNode << to<std::string>(stringInfo.asUtf8StrGetter(obj).obj);
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const ListInfo& listInfo) {
  const auto& valueTypeInfo = getTypeInfoFromId(listInfo.valueType);
  destNode |= ryml::SEQ;
  const std::size_t listSize = listInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < listSize; ++index) {
    ConstTmpObj tmpObj = listInfo.elemGetterConst(obj, index);
    toYaml(destNode[index], tmpObj.obj, valueTypeInfo);
  }
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const DictInfo& dictInfo) {
  const auto& keyTypeInfo = getTypeInfoFromId(dictInfo.keyType);
  const auto& valueTypeInfo = getTypeInfoFromId(dictInfo.valueType);
  destNode |= ryml::MAP;
  const std::size_t dictSize = dictInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < dictSize; ++index) {
    auto [key, value] = dictInfo.kvpGetterConst(obj, index);
    auto child = destNode.append_child();
    ryml::Tree keyTree;
    toYaml(keyTree, key, keyTypeInfo);
    std::string keyStr;
    keyTree.rootref() >> keyStr;
    child << ryml::key(keyStr);
    toYaml(child, value, valueTypeInfo);
  }
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId& id, const ClassInfo& classInfo) {
  // todo implement ReflectAsMember
  const bool asFlow = std::any_of(classInfo.annotations.begin(), classInfo.annotations.end(), [](const auto& attr) {
    return attr->getTypeId() == getTypeId<^^SerializeFlowStyle>();
  });
  if (asFlow) {
    destNode |= ryml::FLOW_SL;
  }
  destNode |= ryml::MAP;
  if (BaseObject::isAncestorOf(classInfo)) {
    destNode.append_child() << ryml::key("__type__") << id;  // only write type for polymorphic types
  }
  for (const auto& field : classInfo.fields) {
    const auto& fieldTypeInfo = getTypeInfoFromId(field.type);
    auto fieldNode = destNode.append_child();
    ryml::csubstr fieldName{field.name.data(), field.name.size()};
    fieldNode << ryml::key(fieldName);
    ConstTmpObj tmpObj = field.getterConst(obj);
    toYaml(fieldNode, tmpObj.obj, fieldTypeInfo);
  }
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeId&, const PtrInfo& ptrInfo) {
  ConstTmpObj tmpObj = ptrInfo.getterConst(obj);
  auto* baseObj = static_cast<const BaseObject*>(tmpObj.obj);
  toYaml(destNode, baseObj, baseObj->getTypeInfo());
}

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeInfo& typeInfo) {
  std::visit([&](const auto& actualTypeInfo) { toYaml(destNode, obj, typeInfo.id, actualTypeInfo); }, typeInfo.info);
}
}  // namespace loki::core