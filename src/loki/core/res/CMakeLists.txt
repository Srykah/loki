loki_create_lib(
  NAME res
  HEADERS
  JsonResources.hpp
  Resource.hpp
  ResourceHolder.hpp
  SFMLResources.hpp
  INTERNAL_HEADERS
  impl/ResourceHolder.hxx
  PUBLIC_DEPS
  sfml-graphics
  loki::json
  loki::utils
)
