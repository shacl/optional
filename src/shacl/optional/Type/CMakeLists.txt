target_sources(optional INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/assignment.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ctor.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/emplace.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/swap.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/value.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/value_or.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/Type/assignment.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/Type/ctor.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/Type/emplace.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/Type/swap.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/Type/value.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/Type/value_or.hpp>)

if(optional.tests)
  add_subdirectory(test)
endif()
