loki_create_lib(
  NAME math INTERFACE
  HEADERS
    Interpolate.hpp
    LinAlg2D.hpp
  INTERNAL_HEADERS
    impl/Interpolate.hxx
  PUBLIC_DEPS
    sfml-graphics
    nlohmann_json::nlohmann_json
)
