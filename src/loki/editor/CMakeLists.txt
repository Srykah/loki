loki_create_module(editor
  HEADERS
  dynamicField/DynamicField.hpp
  modules/EditorModule.hpp
  modules/ImGuiModule.hpp

  SOURCES
  dynamicField/DynamicField.cpp
  modules/EditorModule.cpp
  modules/ImGuiModule.cpp

  PUBLIC_DEPS
  loki::system
)