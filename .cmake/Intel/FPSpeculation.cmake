include(Backports/IncludeGuard)
include_guard(GLOBAL)

define_property(TARGET PROPERTY Intel_FLOATING_POINT_SPECULATION
BRIEF_DOCS
"Intel Fortran floating point speculation model"
FULL_DOCS
"This property specifies the Intel floating-point speculation approach.
Options are: fast, safe, strict, off"
)

add_library(Intel_FPSpeculation_C INTERFACE)
add_library(Intel::FPSpeculation_C ALIAS Intel_FPSpeculation_C)

string(CONCAT generator
  "$<$<BOOL:$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>:"
    "$<$<STREQUAL:Intel,${CMAKE_C_COMPILER_ID}>:"
      "$<$<NOT:$<PLATFORM_ID:Windows>>:-fp-speculation=$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>"
      "$<$<PLATFORM_ID:Windows>:/Qfp-speculation:$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>"
    ">"
  ">"
)

target_compile_options(Intel_FPSpeculation_C INTERFACE ${generator})

add_library(Intel_FPSpeculation_CXX INTERFACE)
add_library(Intel::FPSpeculation_CXX ALIAS Intel_FPSpeculation_CXX)

string(CONCAT generator
  "$<$<BOOL:$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>:"
    "$<$<STREQUAL:Intel,${CMAKE_CXX_COMPILER_ID}>:"
      "$<$<NOT:$<PLATFORM_ID:Windows>>:-fp-speculation=$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>"
      "$<$<PLATFORM_ID:Windows>:/Qfp-speculation:$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>"
    ">"
  ">"
)

target_compile_options(Intel_FPSpeculation_CXX INTERFACE ${generator})

add_library(Intel_FPSpeculation_Fortran INTERFACE)
add_library(Intel::FPSpeculation_Fortran ALIAS Intel_FPSpeculation_Fortran)

string(CONCAT generator
  "$<$<BOOL:$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>:"
    "$<$<STREQUAL:Intel,${CMAKE_Fortran_COMPILER_ID}>:"
      "$<$<NOT:$<PLATFORM_ID:Windows>>:-fp-speculation=$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>"
      "$<$<PLATFORM_ID:Windows>:/Qfp-speculation:$<TARGET_PROPERTY:Intel_FLOATING_POINT_SPECULATION>>"
    ">"
  ">"
)

target_compile_options(Intel_FPSpeculation_Fortran INTERFACE ${generator})
