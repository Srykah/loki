namespace loki::core {

#if 0
template <>
const TypeInfo* getTypeInfo<LangMetaData>() {
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
#endif

template <class... Args>
[[nodiscard]] std::string I18nData::get(std::string_view fmt, Args&&... fmtArgs) const {
  return get(fmt::format(fmt::runtime(fmt), std::forward<Args>(fmtArgs)...));
}

}  // namespace loki::core
