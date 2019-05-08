add_executable(shacl.optional.map.test map.test.cpp)
target_link_libraries(shacl.optional.map.test PUBLIC shacl::optional::testing)
add_test(NAME shacl.optional.map.test COMMAND shacl.optional.map.test)
