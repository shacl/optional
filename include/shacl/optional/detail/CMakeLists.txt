target_sources(optional INTERFACE
  "${prefix}/shacl/optional/detail/all.hpp"
  "${prefix}/shacl/optional/detail/Curry.hpp")

target_sources(optional-14 INTERFACE
  "${prefix}/shacl/optional/detail/Copy.hpp"
  "${prefix}/shacl/optional/detail/CopyAssign.hpp"
  "${prefix}/shacl/optional/detail/Enabled.hpp"
  "${prefix}/shacl/optional/detail/Move.hpp"
  "${prefix}/shacl/optional/detail/MoveAssign.hpp"
  "${prefix}/shacl/optional/detail/Operations.hpp"
  "${prefix}/shacl/optional/detail/Storage.hpp")
