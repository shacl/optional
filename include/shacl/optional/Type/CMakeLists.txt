target_sources(optional-14 INTERFACE
  "${prefix}/shacl/optional/Type/assignment.hpp"
  "${prefix}/shacl/optional/Type/ctor.hpp"
  "${prefix}/shacl/optional/Type/emplace.hpp"
  "${prefix}/shacl/optional/Type/swap.hpp"
  "${prefix}/shacl/optional/Type/value.hpp"
  "${prefix}/shacl/optional/Type/value_or.hpp")

if(shacl.optional.tests AND mpark_variant_FOUND)
  add_subdirectory(test)
endif()
