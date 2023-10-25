loki_create_module(core
  HEADERS
  # hash
  hash/CombineHash.hpp
  hash/IterHash.hpp
  hash/PairHash.hpp
  hash/TupleHash.hpp
  # i18n
  i18n/I18nData.hpp
  i18n/I18nData.hxx
  # json
  json/Color.hpp
  json/Joystick.hpp
  json/Keyboard.hpp
  json/Macros.hpp
  json/Mouse.hpp
  json/Optional.hpp
  json/Path.hpp
  json/Rect.hpp
  json/Time.hpp
  json/Variant.hpp
  json/Vector2.hpp
  # math
  math/Interpolate.hpp
  math/Interpolate.hxx
  math/Misc.hpp
  math/Rect.hpp
  math/Vector2Ops.hpp
  math/Vector4.hpp
  math/Vector4.hxx
  # reflection
  reflection/BaseObject.hpp
  reflection/ReflectionFactory.hpp
  reflection/ReflectionFactory.hxx
  reflection/SFMLTypesInfo.hpp
  reflection/TypeInfo.hpp
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
  utils/TemplateHelpers.hpp
  utils/VertexArrayIterator.hpp
  utils/Wrappers.hpp

  SOURCES
  # i18n
  i18n/I18nData.cpp
  # core
  states/StateMachine.cpp
  # core
  tpl/TemplateEngine.cpp
  # utils
  utils/Random.cpp
  utils/VertexArrayIterator.cpp

  PUBLIC_DEPS
  sfml-graphics
  nlohmann_json::nlohmann_json
  fmt::fmt
  )