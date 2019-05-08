add_executable(shacl.optional.bind.test bind.test.cpp)
target_link_libraries(shacl.optional.bind.test PUBLIC shacl::optional::testing)
add_test(NAME shacl.optional.bind.test COMMAND shacl.optional.bind.test)
