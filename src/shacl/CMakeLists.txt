target_sources(optional INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/optional.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional.hpp>)

add_subdirectory(optional)
