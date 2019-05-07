target_sources(optional-14 INTERFACE
  "${prefix}/shacl/optional/bad_access.hpp"
  "${prefix}/shacl/optional/comparison.hpp"
  "${prefix}/shacl/optional/Type.hpp")

target_sources(optional INTERFACE
  "${prefix}/shacl/optional/bind.hpp"
  "${prefix}/shacl/optional/detail.hpp"
  "${prefix}/shacl/optional/IsInstance.hpp"
  "${prefix}/shacl/optional/make.hpp"
  "${prefix}/shacl/optional/map.hpp")

add_subdirectory(detail)
add_subdirectory(Type)

if(shacl.optional.tests)
  add_subdirectory(map/test)
  add_subdirectory(bind/test)
endif()
