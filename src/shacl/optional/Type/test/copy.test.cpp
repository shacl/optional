#include "catch2/catch.hpp"
#include "shacl/optional.hpp"

SCENARIO("Type copy"){
  GIVEN("A trivially copy constructible type, T"){
    struct T {};

    THEN("a Type<T> is also trivially move constructible"){
      REQUIRE(std::is_trivially_copy_constructible<shacl::Optional<T>>::value);
    }
  }

  GIVEN("A non-trivially copy constructible type, T"){
    struct T {
      T(const T&){}
    };

    THEN("a Type<T> is also non-trivially move constructible"){
      REQUIRE_FALSE(std::is_trivially_copy_constructible
                    <shacl::Optional<T>>::value);
    }
  }
}
