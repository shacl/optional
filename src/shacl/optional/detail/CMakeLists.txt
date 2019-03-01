target_sources(optional INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/all.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Copy.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/CopyAssign.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Enabled.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Move.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/MoveAssign.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Operations.hpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Storage.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/all.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/Copy.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/CopyAssign.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/Enabled.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/Move.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/MoveAssign.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/Operations.hpp>
  $<INSTALL_INTERFACE:include/shacl/optional/detail/Storage.hpp>)
