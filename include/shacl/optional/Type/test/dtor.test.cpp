#include "catch2/catch.hpp"
#include "shacl/optional.hpp"

SCENARIO("Type dtor"){
  GIVEN("A trivially destructible type, T"){
    struct T {};

    THEN("a Type<T> is also trivially destructible"){
      REQUIRE(std::is_trivially_destructible<shacl::Optional<T>>::value);
    }
  }

  GIVEN("A non-trivially destructible type, T"){
    struct T { ~T(){} };

    THEN("a Type<T> is also non-trivially destructible"){
      REQUIRE_FALSE(std::is_trivially_destructible<shacl::Optional<T>>::value);
    }
  }
}
