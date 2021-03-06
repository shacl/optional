cmake_minimum_required(VERSION 3.12.1)
string(CONCAT generator
  "$<$<OR:$<AND:$<STREQUAL:C,$<TARGET_PROPERTY:LINKER_LANGUAGE>>,"
                "$<C_COMPILER_ID:MSVC>>,"
         "$<AND:$<STREQUAL:CXX,$<TARGET_PROPERTY:LINKER_LANGUAGE>>,"
                "$<CXX_COMPILER_ID:MSVC>>>:"
    "$<$<PLATFORM_ID:Windows>:-STACK:$<TARGET_PROPERTY:LINK_STACK_SIZE>>"
  ">")

target_link_libraries(shacl::cmake::LinkOptions::StackSize INTERFACE ${generator})
