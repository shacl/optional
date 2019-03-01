target_sources(optional INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bad_access.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bind.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/detail.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/IsInstance.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/make.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/map.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Type.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/bad_access.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/bind.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/IsInstance.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/make.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/map.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/Type.hpp>)

add_subdirectory(detail)
add_subdirectory(Type)

if(optional.tests)
  add_subdirectory(map/test)
  add_subdirectory(bind/test)
endif()
