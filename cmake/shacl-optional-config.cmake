include(CMakeFindDependencyMacro)
find_dependency(shacl COMPONENTS trait ebo)

if(shacl-optional_FIND_QUIETLY)
  set(shacl-optional_FIND_QUIETLY_ARG QUIET)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/shacl-optional-targets.cmake")

find_package(mpark_variant ${shacl-optional_FIND_QUIETLY_ARG})
if(mpark_variant_FOUND)
  set_target_properties(shacl::optional PROPERTIES INTERFACE_CXX_STANDARD 14)
  target_link_libraries(shacl::optional-14 INTERFACE mpark_variant)
  target_link_libraries(shacl::optional INTERFACE
    $<$<VERSION_LESS:$<TARGET_PROPERTY:CXX_STANDARD>,17>:shacl::optional-14>)

else()
  if(NOT "${shacl-optional_FIND_QUIETLY_ARG}")
    message(WARNING "shacl::optional C++-14 support requires mpark_variant")
  endif()
  set_target_properties(shacl::optional PROPERTIES INTERFACE_CXX_STANDARD 17)
endif()
