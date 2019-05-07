cmake_minimum_required(VERSION 3.12)

set(subproject OFF)
if(DEFINED PROJECT_NAME)
  set(subproject ON)
endif()

project(shacl-optional
  VERSION 0.2.0
  DESCRIPTION "Utilities for (and optional C++14 backport of) std::optional"
  HOMEPAGE_URL "https://xcp-stash.lanl.gov/projects/SCL/repos/optional"
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.cmake")
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(CTest)
include(Git/Submodule/Packages)

if(EXISTS "${PROJECT_SOURCE_DIR}/cmake/specification.cmake")
  set(git.submodule.packages.specification
    "${PROJECT_SOURCE_DIR}/cmake/specification.cmake" CACHE FILEPATH
    "(READ ONLY) Path to consumed git submodule packages specification file" FORCE)
  include("${PROJECT_SOURCE_DIR}/cmake/specification.cmake")
endif()

CMAKE_DEPENDENT_OPTION(shacl.optional.tests
  "Build the optional tests and integrate with ctest"
  ON "BUILD_TESTING; NOT subproject" OFF)

add_library(optional INTERFACE)
add_library(shacl::optional ALIAS optional)

if(shacl.optional.tests)
  include(Warnings)
  include(Sanitizers)

  configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/CTestCustom.cmake"
    "${PROJECT_BINARY_DIR}/CTestCustom.cmake"
    COPYONLY)

  set(CMAKE_CXX_EXTENSIONS OFF)

  add_library(shacl::optional::testing IMPORTED INTERFACE)

  set_target_properties(shacl::optional::testing PROPERTIES
    INTERFACE_WARN_ALL ON
    INTERFACE_WARN_ERROR ON)

  set_property(TARGET shacl::optional::testing APPEND PROPERTY
    COMPATIBLE_INTERFACE_BOOL
    WARN_ALL WARN_ERROR)

  find_package(Catch2 REQUIRED)
  target_link_libraries(shacl::optional::testing INTERFACE
    shacl::cmake::Warnings_CXX
    shacl::cmake::Sanitizers_CXX
    Catch2::Catch2
    shacl::optional)
endif()

add_library(optional-14 INTERFACE)
add_library(shacl::optional-14 ALIAS optional-14)

target_compile_features(optional INTERFACE cxx_std_14)

find_package(shacl REQUIRED COMPONENTS trait ebo)
find_package(mpark_variant)

if(mpark_FOUND)
  target_link_libraries(optional-14 INTERFACE $<BUILD_INTERFACE:mpark_variant>)

  string(CONCAT generator
    "$<BUILD_INTERFACE:"
      "$<$<VERSION_LESS:"
          "$<TARGET_PROPERTY:CXX_STANDARD>,17"
        ">:shacl::optional-14"
      ">"
    ">")

  target_link_libraries(optional INTERFACE ${generator})
  unset(generator)
endif()

target_link_libraries(optional INTERFACE
  shacl::trait
  shacl::ebo)

include(GNUInstallDirs)

string(CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_include_directories(optional optional-14 INTERFACE "${prefix}")

add_subdirectory(include/shacl)

install(DIRECTORY include/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING PATTERN "*.hpp"
  PATTERN "*test*" EXCLUDE)

install(FILES
  "${PROJECT_SOURCE_DIR}/.cmake/shacl-config.cmake"
  DESTINATION share/cmake/shacl)

install(TARGETS optional EXPORT optionalTargets)

install(EXPORT optionalTargets
  FILE "shacl-optional-targets.cmake"
  NAMESPACE shacl::
  DESTINATION share/cmake/shacl-optional)

write_basic_package_version_file("shacl-optional-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES
  "${PROJECT_SOURCE_DIR}/cmake/shacl-optional-config.cmake"
  "${PROJECT_BINARY_DIR}/shacl-optional-config-version.cmake"
  DESTINATION share/cmake/shacl-optional)

if(NOT subproject)
  set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set(CPACK_PACKAGE_CONTACT "amccartney@lanl.gov")
  include(CPack)
endif()
