loki_create_module(editor
  HEADERS
  registerTypes.hpp
  dynamicField/DynamicField.hpp
  modules/DebugDrawModule.hpp
  modules/EditorModule.hpp
  modules/ImGuiModule.hpp

  SOURCES
  registerTypes.cpp
  dynamicField/DynamicField.cpp
  modules/DebugDrawModule.cpp
  modules/EditorModule.cpp
  modules/ImGuiModule.cpp

  PUBLIC_DEPS
  loki::graphics
)