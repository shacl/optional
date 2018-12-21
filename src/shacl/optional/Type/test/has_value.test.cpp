#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

SCENARIO("has_value"){
  struct T{};

  GIVEN("an optional"){
    shacl::Optional<T> o;

    WHEN("engaged"){
      o = T{};

      THEN("the has_value method returns true"){
        REQUIRE(o.has_value());
      }

      THEN("a boolean cast returns true"){
        REQUIRE(bool(o));
      }
    }

    WHEN("disengaged"){
      THEN("the has_value method returns false"){
        REQUIRE_FALSE(o.has_value());
      }

      THEN("a boolean cast returns false"){
        REQUIRE_FALSE(bool(o));
      }
    }
  }
}
