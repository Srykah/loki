namespace loki::core {

template <>
const TypeInfo* getTypeInfo<I18nData::LangMetaData>() {
  static TypeInfo typeInfo{.index = typeid(I18nData::LangMetaData),
                           .name = "loki::core::I18nData::LangMetaData",
                           .description = "Metadata for a language in the database",
                           .parents = {},
                           .fields = {
                               FieldInfo{.type = ::loki::core::getTypeInfo<std::string>(),
                                         .name = "name",
                                         .description = "ISO code of the language in lowercase (eg. en-us)"},
                               FieldInfo{.type = ::loki::core::getTypeInfo<std::filesystem::path>(),
                                         .name = "filepath",
                                         .description = "Path of the language file relative to the database file"},
                           }};
  return &typeInfo;
}

template <class... Args>
[[nodiscard]] std::string I18nData::get(const std::string& uri, Args&&... args) const {
  return get(Ptr{fmt::format(fmt::runtime(uri), std::forward<Args>(args)...)});
}

}  // namespace loki::core
