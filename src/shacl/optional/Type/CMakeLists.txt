target_sources(optional INTERFACE
  $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/assignment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ctor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/emplace.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/swap.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/value.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/value_or.hpp>
  $<INSTALL_INTERFACE:
    include/shacl/optional/Type/assignment.hpp
    include/shacl/optional/Type/ctor.hpp
    include/shacl/optional/Type/emplace.hpp
    include/shacl/optional/Type/swap.hpp
    include/shacl/optional/Type/value.hpp
    include/shacl/optional/Type/value_or.hpp>)

if(optional.tests)
  add_subdirectory(test)
endif()
