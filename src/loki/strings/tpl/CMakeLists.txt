loki_create_lib(
  NAME tpl
  HEADERS TemplateEngine.hpp
  INTERNAL_HEADERS impl/TemplateEngine.hxx
  SOURCES TemplateEngine.cpp
  PUBLIC_DEPS fmt::fmt)
