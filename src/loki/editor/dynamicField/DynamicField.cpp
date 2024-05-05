#include "DynamicField.h"

#define __STDC_WANT_LIB_EXT1__ 1
#include <cstring>
#include "core/utils.h"
#include "serial/toString.h"
#include "typeRegistry/BaseObject.h"

void DynamicField(void*, const NullInfo&) {
  ImGui::TextUnformatted("null");
}

void DynamicField(void* obj, const BooleanInfo&) {
  ImGui::Checkbox("", &to<bool>(obj));
}

void DynamicField(void* obj, const IntegerInfo& integerInfo) {
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
    }
  }
}

void DynamicField(void* obj, const FloatingPointInfo& floatingPointInfo) {
  if (floatingPointInfo.size == sizeof(float)) {
    ImGui::InputScalar("", ImGuiDataType_Float, obj);
  } else if (floatingPointInfo.size == sizeof(double)) {
    ImGui::InputScalar("", ImGuiDataType_Float, obj);
  } else if (floatingPointInfo.size == sizeof(long double)) {
    assert(false && "Long double is not supported by ImGui!");
  } else {
    assert(false && "Unknown floating point size!");
  }
}

void DynamicField(void* obj, const CharacterInfo& characterInfo) {
  constexpr std::size_t BUF_SIZE = 2;
  assert(characterInfo.size == sizeof(char) && !characterInfo.isUnicode && "Only char is supported!");  // todo others
  char buf[BUF_SIZE];
  buf[0] = to<char>(obj);
  if (ImGui::InputText("", buf, BUF_SIZE))
    to<char>(obj) = buf[0];
}

void DynamicField(void* obj, const StringInfo& stringInfo) {
  // todo others
  constexpr std::size_t BUF_SIZE = 1024;
  assert(stringInfo.charType.size == sizeof(char) && !stringInfo.charType.isUnicode && "Only char is supported!");
  assert(stringInfo.sizeGetter(obj) <= BUF_SIZE && "Size is too big for our buffer");
  char buf[BUF_SIZE];
  strcpy_s(buf, stringInfo.sizeGetter(obj) + 1, stringInfo.dataGetter(obj));
  if (ImGui::InputText("", buf, BUF_SIZE)) {
    std::size_t newSize = strnlen_s(buf, BUF_SIZE);
    stringInfo.setter(obj, buf, newSize);
  }
}

void DynamicField(void* obj, const ListInfo& listInfo) {
  ImGui::NewLine();
  ImGui::Indent();
  const std::size_t listSize = listInfo.sizeGetter(obj);
  for (int index = 0; index < listSize; ++index) {
    std::string itemLabel = '[' + std::to_string(index) + ']';
    TmpObj elem = listInfo.elemGetter(obj, index);
    DynamicField(itemLabel.c_str(), elem.obj, listInfo.valueType);
  }
  ImGui::Unindent();
}

void DynamicField(void* obj, const DictInfo& dictInfo) {
  ImGui::NewLine();
  ImGui::Indent();
  const std::size_t dictSize = dictInfo.sizeGetter(obj);
  for (int index = 0; index < dictSize; ++index) {
    KeyValuePair kvp = dictInfo.kvpGetter(obj, index);
    std::string keyStr;
    toString(keyStr, kvp.key, dictInfo.keyType);
    DynamicField(keyStr.c_str(), kvp.value, dictInfo.valueType);
  }
  ImGui::Unindent();
}

void DynamicField(void* obj, const ClassInfo& classInfo) {
  ImGui::NewLine();
  ImGui::Indent();
  for (const auto& field : classInfo.fields) {
    TmpObj fieldObj = field.getter(obj);
    DynamicField(field.name.data(), fieldObj.obj, field.type);
    if (!field.isInPlace)
      field.setter(obj, fieldObj.obj);
  }
  ImGui::Unindent();
}

void DynamicField(void* obj, const PtrInfo& ptrInfo) {
  TmpObj inner = ptrInfo.getter(obj);
  auto* baseObj = static_cast<BaseObject*>(inner.obj);
  if (baseObj != nullptr)
    DynamicField("", baseObj, baseObj->getTypeInfo());
  else
    DynamicField("", nullptr, ::getTypeInfo<nullptr_t>());
}

void DynamicField(const char* label, void* obj, const TypeInfo& typeInfo) {
  ImGui::PushID(label);
  ImGui::TextUnformatted(label);
  ImGui::SameLine();
  std::visit([&](const auto& actualTypeInfo) { DynamicField(obj, actualTypeInfo); }, typeInfo.info);
  ImGui::PopID();
}
