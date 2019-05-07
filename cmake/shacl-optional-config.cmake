include(CMakeFindDependencyMacro)
find_dependency(shacl COMPONENTS trait ebo)

if(shacl-optional_FIND_QUIETLY)
  set(shacl-optional_FIND_QUIETLY_ARG QUIET)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/shacl-optional-targets.cmake")

find_package(mpark_variant ${shacl-optional_FIND_QUIETLY_ARG})
if(mpark_variant_FOUND)
  target_link_libraries(optional INTERFACE
    optional-14
    mpark_variant)
elseif(NOT "${shacl-optional_FIND_QUIETLY_ARG}")
  message(WARNING "shacl::optional C++-14 support requires mpark_variant")
endif()
