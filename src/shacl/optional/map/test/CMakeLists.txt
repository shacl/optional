add_executable(optional.map.test map.test.cpp)
target_link_libraries(optional.map.test PUBLIC shacl::optional::testing)
add_test(NAME optional.map.test COMMAND optional.map.test)
