loki_create_module(editor
  HEADERS
  dynamicField/DynamicField.hpp
  modules/DebugDrawModule.hpp
  modules/EditorModule.hpp
  modules/ImGuiModule.hpp

  SOURCES
  dynamicField/DynamicField.cpp
  modules/DebugDrawModule.cpp
  modules/EditorModule.cpp
  modules/ImGuiModule.cpp

  PUBLIC_DEPS
  loki::graphics
)