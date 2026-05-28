#include "fromYaml.hpp"

#include <cassert>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/core/services/ServiceRegistry.hpp>

namespace loki::core {

using details::to;

void fromYaml(const ryml::ConstNodeRef&, void* obj, const NullInfo&) {
  to<std::nullptr_t>(obj) = nullptr;
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const BooleanInfo&) {
  node >> to<bool>(obj);
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const IntegerInfo& integerInfo) {
  unsigned int size = integerInfo.size;
  if (integerInfo.isUnsigned) {
    if (size == sizeof(uint8_t)) {
      node >> to<uint8_t>(obj);
    } else if (size == sizeof(uint16_t)) {
      node >> to<uint16_t>(obj);
    } else if (size == sizeof(uint32_t)) {
      node >> to<uint32_t>(obj);
    } else if (size == sizeof(uint64_t)) {
      node >> to<uint64_t>(obj);
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (size == sizeof(int8_t)) {
      node >> to<int8_t>(obj);
    } else if (size == sizeof(int16_t)) {
      node >> to<int16_t>(obj);
    } else if (size == sizeof(int32_t)) {
      node >> to<int32_t>(obj);
    } else if (size == sizeof(int64_t)) {
      node >> to<int64_t>(obj);
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const FloatingPointInfo& floatingPointInfo) {
  unsigned int size = floatingPointInfo.size;
  if (size == sizeof(float)) {
    node >> to<float>(obj);
  } else if (size == sizeof(double)) {
    node >> to<double>(obj);
  } else if (size == sizeof(long double)) {
    // todo?
    double value;
    node >> value;
    to<long double>(obj) = value;
  } else {
    assert(false && "Unknown floating point size!");
  }
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const EnumInfo& enumInfo) {
  // find the value corresponding to the enumerator
  std::int64_t value = 0;
  std::string enumName;
  node >> enumName;
  auto it = std::ranges::find_if(enumInfo.enumerators, [&enumName](const EnumeratorInfo& enumeratorInfo) {
    return enumeratorInfo.name == enumName;
  });
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

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const CharacterInfo& characterInfo) {
  node >> to<char>(obj);
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const StringInfo& stringInfo) {
  std::string str;
  node >> str;
  stringInfo.setter(obj, str.data(), str.size());
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const ListInfo& listInfo) {
  std::size_t nodeListSize = node.num_children();
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

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const DictInfo& dictInfo) {
  for (const auto& child : node) {
    auto key = child.key();
    TmpObj tmpObj;
    {
      TmpObj keyInstance = dictInfo.keyType.factory(obj, TmpObj::Ownership::Default);
      ryml::Tree keyTree = ryml::parse_in_arena(key);
      fromYaml(keyTree, keyInstance.obj, dictInfo.keyType);
      tmpObj = dictInfo.elemAdder(obj, keyInstance.obj);
    }
    fromYaml(child, tmpObj.obj, dictInfo.valueType);
  }
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const ClassInfo& classInfo) {
  bool asValue = std::ranges::find_if(classInfo.attributes, [](const auto& attr) {
                   return attr->getType() == ClassAttribute::Type::SerializeAsValue;
                 }) != classInfo.attributes.end();
  if (asValue) {
    const auto& field = classInfo.fields.at(0);
    if (field.isInPlace) {
      TmpObj fieldObj = field.getter(obj);
      fromYaml(node, fieldObj.obj, field.type);
    } else {
      TmpObj fieldObj = field.type.factory(obj, TmpObj::Ownership::Owned);
      fromYaml(node, fieldObj.obj, field.type);
      field.setter(obj, fieldObj.obj);
    }
  } else {
    for (const auto& field : classInfo.fields) {
      auto childNode = node.find_child(field.name.data());
      if (childNode.invalid()) {
        continue;  // ignore absent values
      }
      if (field.isInPlace) {
        TmpObj fieldObj = field.getter(obj);
        fromYaml(childNode, fieldObj.obj, field.type);
      } else {
        TmpObj fieldObj = field.type.factory(obj, TmpObj::Ownership::Owned);
        fromYaml(childNode, fieldObj.obj, field.type);
        field.setter(obj, fieldObj.obj);
      }
    }
  }
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const PtrInfo& ptrInfo) {
  if (std::holds_alternative<ClassInfo>(ptrInfo.innerType.info)) {
    ClassId classId;
    node["__type__"] >> classId;
    const TypeInfo* actualTypeInfo = getService<RuntimeObjectRegistry>().getRuntimeTypeInfo(classId);
    assert(actualTypeInfo);
    TmpObj data = actualTypeInfo->factory(obj, TmpObj::Ownership::NonOwned);
    fromYaml(node, data.obj, *actualTypeInfo);
    ptrInfo.setter(obj, details::asAncestor(data.obj, actualTypeInfo, std::get<ClassInfo>(ptrInfo.innerType.info).id));
  } else {
    TmpObj inner = ptrInfo.emplacer(obj);
    fromYaml(node, inner.obj, ptrInfo.innerType);
  }
}

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const TypeInfo& typeInfo) {
  std::visit([&](const auto& actualTypeInfo) { fromYaml(node, obj, actualTypeInfo); }, typeInfo.info);
}
}  // namespace loki::core