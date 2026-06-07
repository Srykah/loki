#pragma once

#include <meta>
#include <type_traits>

#include <loki/core/reflection/Annotation.hpp>
#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/reflection/reflectionUtils.hpp>

namespace loki::core::details {

template <std::meta::info stuffMeta, Annotation::AppliesTo appliesTo>
auto getAnnotations() {
  std::vector<std::unique_ptr<Annotation>> result;
  static constexpr auto annotations = std::define_static_array(std::meta::annotations_of(stuffMeta));
  template for (constexpr auto annot : annotations) {
    static constexpr auto value = std::meta::constant_of(annot);
    static constexpr auto valueType = std::meta::type_of(value);
    if (!std::meta::has_parent(valueType)) {
      continue;
    }
    static constexpr auto parentType = std::meta::parent_of(valueType);
    if (!std::meta::extract<bool>(std::meta::substitute(^^std::is_base_of_v, {
                                                                                 ^^Annotation, parentType}))) {
      continue;
    }
    static_assert(([:parentType:] ::appliesTo & appliesTo) == appliesTo);
    result.push_back(std::make_unique<typename[:parentType:]>([:value:]));
  }
  return result;
}

template <std::meta::info fieldMeta>
loki::core::FieldInfo getFieldInfo() {
  return {.type = getTypeId<std::meta::type_of(fieldMeta)>(),
          .name = std::meta::identifier_of(fieldMeta),
          .offset = std::meta::offset_of(fieldMeta).bytes,
          .annotations = getAnnotations<fieldMeta, Annotation::Field>()};
}

template <class T>
  requires std::is_class_v<T>
loki::core::TypeInfo computeTypeInfo() {
  constexpr auto ctx = std::meta::access_context::current();

  loki::core::ClassInfo info;

  // Get parent type
  static constexpr auto basesMeta = std::define_static_array(std::meta::bases_of(^^T, ctx));
  template for (constexpr auto baseMeta : basesMeta) {
    info.parentType = getTypeId<baseMeta>();
    info.toParentType = [](void* obj) { return static_cast<void*>(static_cast<[:baseMeta:]*>(obj)); };
    break;  // Assuming single inheritance for simplicity, break after the first base class
  }

  // Get fields
  static constexpr auto membersMeta = std::define_static_array(std::meta::nonstatic_data_members_of(^^T, ctx));
  template for (constexpr auto memberMeta : membersMeta) {
    info.fields.push_back(std::move(getFieldInfo<memberMeta>()));
  }

  // Get annotations
  info.annotations = getAnnotations<^^T, Annotation::Class>();

  static constexpr auto id = getTypeId<^^T>();
  return loki::core::TypeInfo{
      .id = id,
      .factory = details::getBasicFactory<T>(),
      .info = std::move(info),
  };
}

template <std::meta::info enumeratorMeta>
loki::core::EnumeratorInfo getEnumeratorInfo() {
  return {.name = std::meta::identifier_of(enumeratorMeta),
          .value = static_cast<std::int64_t>(
              std::meta::extract<([:std::meta::type_of(enumeratorMeta):])>(std::meta::constant_of(enumeratorMeta))),
          .annotations = getAnnotations<enumeratorMeta, Annotation::EnumValue>()};
}

template <class T>
  requires std::is_enum_v<T>
loki::core::TypeInfo computeTypeInfo() {
  constexpr auto ctx = std::meta::access_context::current();

  loki::core::EnumInfo info;

  // Get underlying type
  static constexpr auto underlyingTypeMeta = std::meta::substitute(^^std::underlying_type_t, {
                                                                                                 ^^T});
  info.underlyingType = getTypeId<underlyingTypeMeta>();

  // Get enumerators
  static constexpr auto enumeratorsMeta = std::define_static_array(std::meta::enumerators_of(^^T));
  template for (constexpr auto enumeratorMeta : enumeratorsMeta) {
    info.enumerators.push_back(getEnumeratorInfo<enumeratorMeta>());
  }

  // Get annotations
  info.annotations = getAnnotations<^^T, Annotation::Enum>();

  static constexpr auto id = getTypeId<^^T>();
  return loki::core::TypeInfo{
      .id = id,
      .factory = details::getBasicFactory<T>(),
      .info = std::move(info),
  };
}

}  // namespace loki::core::details
