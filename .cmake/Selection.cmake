cmake_minimum_required(VERSION 3.12.1)
include_guard(GLOBAL)

function(selection variable docstring)
  cmake_parse_arguments(selection "" DEFAULT OPTIONS ${ARGN})
  if(NOT DEFINED selection_OPTIONS)
    message(FATAL_ERROR "selection invoked without 'OPTIONS' keyword")
  endif()

  if(DEFINED selection_DEFAULT)
    if(NOT selection_DEFAULT IN_LIST selection_OPTIONS)
      message(FATAL_ERROR
        "selection invoked with 'DEFAULT' argument not present in  'OPTIONS' list")
    endif()
  else()
    set(selection_DEFAULT "" )
    list(APPEND selection_OPTIONS "")
  endif()

  set(${variable} "${selection_DEFAULT}" CACHE STRING "${docstring}")
  set_property(CACHE ${variable} PROPERTY STRINGS ${selection_OPTIONS})
  if(NOT ${variable} IN_LIST selection_OPTIONS)
    message("${variable} set to ${${variable}}")
    message(FATAL_ERROR "${variable} must be one of ${selection_OPTIONS}")
  endif()
endfunction()

install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/Selection.cmake
  DESTINATION share/cmake/shacl/.cmake)
