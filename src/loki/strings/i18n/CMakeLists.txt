loki_create_lib(
  NAME i18n MODULE strings
  HEADERS
  I18nData.hpp
  INTERNAL_HEADERS
  impl/I18nData.hxx
  SOURCES
  I18nData.cpp
  PUBLIC_DEPS
  fmt::fmt
  nlohmann_json::nlohmann_json
  loki::json
)
