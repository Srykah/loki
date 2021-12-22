loki_create_lib(
  NAME common
  HEADERS IterAdapters.hpp Matrix.hpp Random.hpp TemplateHelpers.hpp Vector4.hpp VertexArrayIterator.hpp
  INTERNAL_HEADERS impl/is_detected.hxx impl/Matrix.hxx impl/Vector4.hxx
  SOURCES Random.cpp VertexArrayIterator.cpp
  PUBLIC_DEPS sfml-graphics nlohmann_json::nlohmann_json)
