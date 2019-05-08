add_executable(shacl.optional.Type.test
  assignment.test.cpp
  copy.test.cpp
  copyAssign.test.cpp
  dereference.test.cpp
  dtor.test.cpp
  equality.test.cpp
  inequality.test.cpp
  has_value.test.cpp
  move.test.cpp
  moveAssign.test.cpp
  reset.test.cpp
  swap.test.cpp
  Type.test.cpp
  value.test.cpp
  value_or.test.cpp)

target_link_libraries(shacl.optional.Type.test PUBLIC shacl::optional::testing)
add_test(NAME shacl.optional.Type.test COMMAND shacl.optional.Type.test)
