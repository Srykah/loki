#include "toYaml.hpp"

#include <cassert>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/rtti/BaseObject.hpp>

namespace loki::core {

using details::to;

void toYaml(YAML::Emitter& emitter, const void*, const NullInfo&) {
  emitter << YAML::Null;
}

void toYaml(YAML::Emitter& emitter, const void* obj, const BooleanInfo&) {
  emitter << to<bool>(obj);
}

void toYaml(YAML::Emitter& emitter, const void* obj, const IntegerInfo& integerInfo) {
  if (integerInfo.isUnsigned) {
    if (integerInfo.size == sizeof(uint8_t)) {
      emitter << to<uint8_t>(obj);
    } else if (integerInfo.size == sizeof(uint16_t)) {
      emitter << to<uint16_t>(obj);
    } else if (integerInfo.size == sizeof(uint32_t)) {
      emitter << to<uint32_t>(obj);
    } else if (integerInfo.size == sizeof(uint64_t)) {
      emitter << to<uint64_t>(obj);
    } else {
      assert(false && "Unknown unsigned integer size!");
    }
  } else {
    if (integerInfo.size == sizeof(int8_t)) {
      emitter << to<int8_t>(obj);
    } else if (integerInfo.size == sizeof(int16_t)) {
      emitter << to<int16_t>(obj);
    } else if (integerInfo.size == sizeof(int32_t)) {
      emitter << to<int32_t>(obj);
    } else if (integerInfo.size == sizeof(int64_t)) {
      emitter << to<int64_t>(obj);
    } else {
      assert(false && "Unknown signed integer size!");
    }
  }
}

void toYaml(YAML::Emitter& emitter, const void* obj, const FloatingPointInfo& floatingPointInfo) {
  if (floatingPointInfo.size == sizeof(float)) {
    emitter << to<float>(obj);
  } else if (floatingPointInfo.size == sizeof(double)) {
    emitter << to<double>(obj);
  } else if (floatingPointInfo.size == sizeof(long double)) {
    assert(false && "Can't emit a long double!");
  } else {
    assert(false && "Unknown floating point size!");
  }
}

void toYaml(YAML::Emitter& emitter, const void* obj, const EnumInfo& enumInfo) {
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
    emitter << it->name.data();
  else
    emitter << value;
}

void toYaml(YAML::Emitter& emitter, const void* obj, const CharacterInfo& characterInfo) {
  emitter << to<char>(obj);
}

void toYaml(YAML::Emitter& emitter, const void* obj, const StringInfo& stringInfo) {
  emitter << to<std::string>(stringInfo.asUtf8StrGetter(obj).obj);
}

void toYaml(YAML::Emitter& emitter, const void* obj, const ListInfo& listInfo) {
  emitter << YAML::BeginSeq;
  const std::size_t listSize = listInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < listSize; ++index) {
    ConstTmpObj tmpObj = listInfo.elemGetterConst(obj, index);
    toYaml(emitter, tmpObj.obj, listInfo.valueType);
  }
  emitter << YAML::EndSeq;
}

void toYaml(YAML::Emitter& emitter, const void* obj, const DictInfo& dictInfo) {
  emitter << YAML::BeginMap;
  const std::size_t dictSize = dictInfo.sizeGetter(obj);
  for (std::size_t index = 0; index < dictSize; ++index) {
    auto [key, value] = dictInfo.kvpGetterConst(obj, index);
    emitter << YAML::Key;
    toYaml(emitter, key, dictInfo.keyType);
    emitter << YAML::Value;
    toYaml(emitter, value, dictInfo.valueType);
  }
  emitter << YAML::EndMap;
}

void toYaml(YAML::Emitter& emitter, const void* obj, const ClassInfo& classInfo) {
  bool asValue = std::ranges::find_if(classInfo.attributes, [](const auto& attr) {
                   return attr->getType() == ClassAttribute::Type::SerializeAsValue;
                 }) != classInfo.attributes.end();
  if (asValue) {
    const auto& field = classInfo.fields.at(0);
    ConstTmpObj tmpObj = field.getterConst(obj);
    toYaml(emitter, tmpObj.obj, field.type);
  } else {
    bool asFlow = std::ranges::find_if(classInfo.attributes, [](const auto& attr) {
                    return attr->getType() == ClassAttribute::Type::SerializeAsFlow;
                  }) != classInfo.attributes.end();
    if (asFlow)
      emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    if (classInfo.parentType) {
      auto rootTypeInfo = classInfo.parentType;
      while (std::get<ClassInfo>(rootTypeInfo->info).parentType != nullptr)
        rootTypeInfo = std::get<ClassInfo>(rootTypeInfo->info).parentType;
      if (std::get<ClassInfo>(rootTypeInfo->info).id == std::get<ClassInfo>(getTypeInfo<BaseObject>().info).id)
        emitter << YAML::Key << "__type__" << YAML::Value << classInfo.id;  // only write type for polymorphic types
    }
    for (const auto& field : classInfo.fields) {
      emitter << YAML::Key << field.name.data();
      ConstTmpObj tmpObj = field.getterConst(obj);
      emitter << YAML::Value;
      toYaml(emitter, tmpObj.obj, field.type);
    }
    emitter << YAML::EndMap;
    if (asFlow)
      emitter << YAML::Block;
  }
}

void toYaml(YAML::Emitter& emitter, const void* obj, const PtrInfo& ptrInfo) {
  ConstTmpObj tmpObj = ptrInfo.getterConst(obj);
  auto* baseObj = static_cast<const BaseObject*>(tmpObj.obj);
  toYaml(emitter, baseObj, baseObj->getClassTypeInfo());
}

void toYaml(YAML::Emitter& emitter, const void* obj, const TypeInfo& typeInfo) {
  std::visit([&](const auto& actualTypeInfo) { toYaml(emitter, obj, actualTypeInfo); }, typeInfo.info);
}
}  // namespace loki::core