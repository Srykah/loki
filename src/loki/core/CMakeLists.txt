loki_create_module(core
  HEADERS
  # hash
  hash/CombineHash.hpp
  hash/IterHash.hpp
  hash/PairHash.hpp
  hash/TupleHash.hpp
  #[[
  # i18n
  i18n/I18nData.hpp
  i18n/I18nData.hxx
  #]]
  # math
  math/Interpolate.hpp
  math/Interpolate.hxx
  math/Misc.hpp
  math/Rect.hpp
  math/Vector2Ops.hpp
  math/Vector4.hpp
  math/Vector4.hxx
  # reflection
  reflection/basicTypesInfo.hpp
  reflection/classMacros.hpp
  reflection/enumMacros.hpp
  reflection/reflectionUtils.hpp
  reflection/sfmlTypesInfo.hpp
  reflection/TypeInfo.hpp
  # rtti
  rtti/BaseObject.hpp
  rtti/rttiConcepts.hpp
  rtti/rttiMacros.hpp
  rtti/RuntimeObjectRegistry.hpp
  # serialization
  serialization/string/toString.hpp
  serialization/yaml/fromYaml.hpp
  serialization/yaml/toYaml.hpp
  # services
  services/ServiceRegistry.hpp
  services/ServiceRegistry.hxx
  # states
  states/State.hpp
  states/StateIndex.hpp
  states/StateMachine.hpp
  states/Transition.hpp
  # tpl
  tpl/TemplateEngine.hpp
  tpl/TemplateEngine.hxx
  # utils
  utils/IterAdapters.hpp
  utils/Literals.hpp
  utils/Macros.hpp
  utils/Matrix.hpp
  utils/Matrix.hxx
  utils/Memory.hpp
  utils/Memory.hxx
  utils/Mixins.hpp
  utils/Random.hpp
  utils/VertexArrayIterator.hpp
  utils/Wrappers.hpp

  SOURCES
  #[[
  # i18n
  i18n/I18nData.cpp
  #]]
  # rtti
  rtti/RuntimeObjectRegistry.cpp
  # serialization
  serialization/string/toString.cpp
  serialization/yaml/fromYaml.cpp
  serialization/yaml/toYaml.cpp
  # services
  services/ServiceRegistry.cpp
  # states
  states/StateMachine.cpp
  # tpl
  tpl/TemplateEngine.cpp
  # utils
  utils/Random.cpp
  utils/VertexArrayIterator.cpp

  PUBLIC_DEPS
  sfml-graphics
  yaml-cpp::yaml-cpp
  fmt::fmt
)