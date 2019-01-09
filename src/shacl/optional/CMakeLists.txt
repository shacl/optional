target_sources(optional INTERFACE
  $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/bad_access.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bind.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/detail.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IsInstance.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/make.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/map.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Type.hpp>
  $<INSTALL_INTERFACE:
    include/shacl/optional/bad_access.hpp
    include/shacl/optional/bind.hpp
    include/shacl/optional/detail.hpp
    include/shacl/optional/IsInstance.hpp
    include/shacl/optional/make.hpp
    include/shacl/optional/map.hpp
    include/shacl/optional/Type.hpp>)

add_subdirectory(detail)
add_subdirectory(Type)

if(optional.tests)
  add_subdirectory(map/test)
  add_subdirectory(bind/test)
endif()
