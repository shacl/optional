#include "catch2/catch.hpp"
#include "shacl/optional.hpp"

SCENARIO("Type copy assignment"){
  GIVEN("A trivially copy assignable type, T"){
    struct T {};
    THEN("a Type<T> is also trivially move assignable"){
      REQUIRE(std::is_trivially_copy_assignable<shacl::Optional<T>>::value);
    }
  }

  GIVEN("A non-trivially copy assignable type, T"){
    struct T {
      T& operator=(const T&){ return *this; }
    };

    THEN("a Type<T> is also non-trivially copy assignable"){
      REQUIRE_FALSE(std::is_trivially_copy_assignable
                    <shacl::Optional<T>>::value);
    }
  }
}
