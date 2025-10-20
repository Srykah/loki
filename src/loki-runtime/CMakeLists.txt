add_executable(loki_runtime)
target_link_libraries(loki_runtime PRIVATE loki::loki dylib)
target_sources(loki_runtime PRIVATE
  main.cpp
  Application.cpp
  Application.hpp
  registerLokiTypes.cpp
  registerLokiTypes.hpp)
add_custom_command(TARGET loki_runtime POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:loki_runtime> $<TARGET_RUNTIME_DLLS:loki_runtime>
  COMMAND_EXPAND_LISTS
)