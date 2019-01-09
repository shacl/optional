add_executable(optional.bind.test bind.test.cpp)
target_link_libraries(optional.bind.test PUBLIC shacl::optional::testing)
add_test(NAME optional.bind.test COMMAND optional.bind.test)
