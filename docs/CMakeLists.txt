# FIND PACKAGES

# Doxygen
find_package(Doxygen)
if(NOT Doxygen_FOUND)
  message(WARNING "Doxygen not found; make sure Doxygen is installed and added to the PATH.")
endif()
loki_print_variables_with_pattern(DOXYGEN)

# Sphinx
find_package(Sphinx)
if(NOT Sphinx_FOUND)
  message(WARNING "Sphinx not found; make sure Sphinx is installed and added to the PATH.")
endif()
loki_print_variables_with_pattern(SPHINX)

if(NOT Doxygen_FOUND OR NOT Sphinx_FOUND)
  message(WARNING "Skipping docs...")
else()
  # DOXYGEN

  # Config
  set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/src/loki)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
  set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
  set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
  set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile)

  # Generate Doxyfile
  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

  # Collect input (for dependencies) foreach(LOKI_MODULE ${LOKI_MODULES})
  # get_target_property(LOKI_${LOKI_MODULE}_HEADER_DIR ${LOKI_MODULE} INTERFACE_INCLUDE_DIRECTORIES) file(GLOB_RECURSE
  # LOKI_${LOKI_MODULE}_HEADERS ${LOKI_${LOKI_MODULE}_HEADER_DIR}/*.hpp) list(APPEND LOKI_ALL_HEADERS
  # LOKI_${LOKI_MODULE}_HEADERS) endforeach()

  # Create target

  # Doxygen won't create this for us
  file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

  add_custom_command(
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    MAIN_DEPENDENCY ${DOXYFILE_OUT}
    ${DOXYFILE_IN}
    DEPENDS "" # ${LOKI_ALL_HEADERS}
    OUTPUT ${DOXYGEN_INDEX_FILE}
    COMMENT "Generating docs")

  add_custom_target(doxygen DEPENDS ${DOXYGEN_INDEX_FILE})

  # SPHINX

  # Config
  set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/sphinx)
  set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/html)
  set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

  # Create target

  # Sphinx won't create this for us
  file(MAKE_DIRECTORY ${SPHINX_BUILD})

  # Only regenerate Sphinx when: - Doxygen has rerun - Our doc files have been updated - The Sphinx config has been
  # updated
  add_custom_command(
    COMMAND
      ${SPHINX_EXECUTABLE} -b html
      # Tell Breathe where to find the Doxygen output
      -Dbreathe_projects.loki=${DOXYGEN_OUTPUT_DIR}/xml ${SPHINX_SOURCE} ${SPHINX_BUILD}
    OUTPUT ${SPHINX_INDEX_FILE}
    MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
    DEPENDS ${SPHINX_SOURCE}/index.rst ${DOXYGEN_INDEX_FILE}
    COMMENT "Generating documentation with Sphinx")

  add_custom_target(docs DEPENDS ${SPHINX_INDEX_FILE})

  # Add an install target to install the docs
  install(DIRECTORY ${SPHINX_BUILD} DESTINATION ${CMAKE_INSTALL_DOCDIR})

endif()
