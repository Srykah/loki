add_executable(loki_app)
target_link_libraries(loki_app loki::loki)
target_sources(loki_app PRIVATE
  main.cpp
  Application.cpp
  Application.hpp
  registerLokiTypes.cpp
  registerLokiTypes.hpp)