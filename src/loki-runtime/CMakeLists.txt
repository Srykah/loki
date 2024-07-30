add_executable(loki_runtime)
target_link_libraries(loki_runtime PRIVATE loki::loki dylib)
target_sources(loki_runtime PRIVATE
  main.cpp
  Application.cpp
  Application.hpp
  registerLokiTypes.cpp
  registerLokiTypes.hpp)