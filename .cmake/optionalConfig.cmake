include(CMakeFindDependencyMacro)
find_dependency(shacl REQUIRED COMPONENTS trait ebo)
find_dependency(mpark_variant REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/optionalTargets.cmake")
