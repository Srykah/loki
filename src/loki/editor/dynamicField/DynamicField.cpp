#include "DynamicField.hpp"

#include <cstring>

#include <imgui.h>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/serialization/string/toString.hpp>

namespace loki::editor {

using core::details::to;

bool DynamicField(void*, const core::NullInfo&) {
  ImGui::TextUnformatted("null");
  return false;
}

bool DynamicField(void* obj, const core::BooleanInfo&) {
  return ImGui::Checkbox("", &to<bool>(obj));
}

bool DynamicField(void* obj, const core::IntegerInfo& integerInfo) {
  if (integerInfo.isUnsigned) {
    if (integerInfo.size == sizeof(uint8_t)) {
      ImGui::InputScalar("", ImGuiDataType_U8, obj);
    } else if (integerInfo.size == sizeof(uint16_t)) {
      ImGui::InputScalar("", ImGuiDataType_U16, obj);
    } else if (integerInfo.size == sizeof(uint32_t)) {
      ImGui::InputScalar("", ImGuiDataType_U32, obj);
    } else if (integerInfo.size == sizeof(uint64_t)) {
      ImGui::InputScalar("", ImGuiDataType_U64, obj);
    } else {
      assert(false && "Unknown unsigned integer size!");
      return false;
    }
  } else {
    if (integerInfo.size == sizeof(int8_t)) {
      ImGui::InputScalar("", ImGuiDataType_S8, obj);
    } else if (integerInfo.size == sizeof(int16_t)) {
      ImGui::InputScalar("", ImGuiDataType_S16, obj);
    } else if (integerInfo.size == sizeof(int32_t)) {
      ImGui::InputScalar("", ImGuiDataType_S32, obj);
    } else if (integerInfo.size == sizeof(int64_t)) {
      ImGui::InputScalar("", ImGuiDataType_S64, obj);
    } else {
      assert(false && "Unknown signed integer size!");
      return false;
    }
  }
  return ImGui::IsItemDeactivatedAfterEdit();
}

bool DynamicField(void* obj, const core::FloatingPointInfo& floatingPointInfo) {
  if (floatingPointInfo.size == sizeof(float)) {
    ImGui::InputScalar("", ImGuiDataType_Float, obj);
  } else if (floatingPointInfo.size == sizeof(double)) {
    ImGui::InputScalar("", ImGuiDataType_Float, obj);
  } else if (floatingPointInfo.size == sizeof(long double)) {
    assert(false && "Long double is not supported by ImGui!");
    return false;
  } else {
    assert(false && "Unknown floating point size!");
    return false;
  }
  return ImGui::IsItemDeactivatedAfterEdit();
}

bool DynamicField(void* obj, const core::EnumInfo& enumInfo) {
  // todo
  return false;
}

bool DynamicField(void* obj, const core::CharacterInfo& characterInfo) {
  constexpr std::size_t BUF_SIZE = 2;
  assert(characterInfo.size == sizeof(char) && !characterInfo.isUnicode && "Only char is supported!");  // todo others
  char buf[BUF_SIZE];
  buf[0] = to<char>(obj);
  if (ImGui::InputText("", buf, BUF_SIZE, ImGuiInputTextFlags_EnterReturnsTrue)) {
    to<char>(obj) = buf[0];
    return true;
  }
  return false;
}

bool DynamicField(void* obj, const core::StringInfo& stringInfo) {
  // todo others
  constexpr std::size_t BUF_SIZE = 1024;
  assert(stringInfo.charType.size == sizeof(char) && !stringInfo.charType.isUnicode && "Only char is supported!");
  assert(stringInfo.sizeGetter(obj) <= BUF_SIZE && "Size is too big for our buffer");
  char buf[BUF_SIZE];
  strcpy_s(buf, stringInfo.sizeGetter(obj) + 1, stringInfo.dataGetter(obj));
  if (ImGui::InputText("", buf, BUF_SIZE, ImGuiInputTextFlags_EnterReturnsTrue)) {
    std::size_t newSize = strnlen_s(buf, BUF_SIZE);
    stringInfo.setter(obj, buf, newSize);
    return true;
  }
  return false;
}

bool DynamicField(void* obj, const core::ListInfo& listInfo) {
  ImGui::NewLine();
  ImGui::Indent();
  const std::size_t listSize = listInfo.sizeGetter(obj);
  bool hasAnyChanged = false;
  for (int index = 0; index < listSize; ++index) {
    std::string itemLabel = '[' + std::to_string(index) + ']';
    core::TmpObj elem = listInfo.elemGetter(obj, index);
    hasAnyChanged =
        DynamicField(itemLabel.c_str(), elem.obj, listInfo.valueType) || hasAnyChanged;  // no short-circuit!!!
  }
  ImGui::Unindent();
  return hasAnyChanged;
}

bool DynamicField(void* obj, const core::DictInfo& dictInfo) {
  ImGui::NewLine();
  ImGui::Indent();
  const std::size_t dictSize = dictInfo.sizeGetter(obj);
  bool hasAnyChanged = false;
  for (int index = 0; index < dictSize; ++index) {
    core::KeyValuePair kvp = dictInfo.kvpGetter(obj, index);
    std::string keyStr;
    toString(keyStr, kvp.key, dictInfo.keyType);
    hasAnyChanged =
        DynamicField(keyStr.c_str(), kvp.value, dictInfo.valueType) || hasAnyChanged;  // no short-circuit!!!
  }
  ImGui::Unindent();
  return hasAnyChanged;
}

bool DynamicField(void* obj, const core::ClassInfo& classInfo) {
  ImGui::NewLine();
  ImGui::Indent();
  bool hasAnyChanged = false;
  for (const auto& field : classInfo.fields) {
    core::TmpObj fieldObj = field.getter(obj);
    bool hasChanged = DynamicField(field.name.data(), fieldObj.obj, field.type);
    if (hasChanged && !field.isInPlace)
      field.setter(obj, fieldObj.obj);
    hasAnyChanged |= hasChanged;
  }
  ImGui::Unindent();
  return hasAnyChanged;
}

bool DynamicField(void* obj, const core::PtrInfo& ptrInfo) {
  core::TmpObj inner = ptrInfo.getter(obj);
  auto* baseObj = static_cast<core::BaseObject*>(inner.obj);
  if (baseObj != nullptr)
    return DynamicField("", baseObj, baseObj->getClassTypeInfo());
  else
    return DynamicField("", nullptr, core::getTypeInfo<nullptr_t>());
}

bool DynamicField(const char* label, void* obj, const core::TypeInfo& typeInfo) {
  ImGui::PushID(label);
  ImGui::TextUnformatted(label);
  ImGui::SameLine();
  bool hasChanged =
      std::visit([&](const auto& actualTypeInfo) -> bool { return DynamicField(obj, actualTypeInfo); }, typeInfo.info);
  ImGui::PopID();
  return hasChanged;
}

}  // namespace loki::editor
