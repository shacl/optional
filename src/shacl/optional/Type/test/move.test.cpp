#include "catch2/catch.hpp"
#include "shacl/optional.hpp"

SCENARIO("Type move"){
  GIVEN("A trivially move constructible type, T"){
    struct T {};

    THEN("a Type<T> is also trivially move constructible"){
      REQUIRE(std::is_trivially_move_constructible<shacl::Optional<T>>::value);
    }
  }

  GIVEN("A non-trivially move constructible type, T"){
    struct T { T(T&&){} };

    THEN("a Type<T> is also non-trivially move constructible"){
      REQUIRE_FALSE(std::is_trivially_move_constructible
                    <shacl::Optional<T>>::value);
    }
  }

    GIVEN("A noexcept(true) move constructible type, T"){
    struct T { T(T&&) noexcept(true) {} };

    THEN("a Type<T> is also noexcept(true) move constructible"){
      REQUIRE(std::is_nothrow_move_constructible<shacl::Optional<T>>::value);
    }
  }

  GIVEN("A noexcept(false) move constructible type, T"){
    struct T { T(T&&) noexcept(false) {} };

    THEN("a Type<T> is also noexcept(false) move constructible"){
      REQUIRE_FALSE(std::is_nothrow_move_constructible
                    <shacl::Optional<T>>::value);
    }
  }

  GIVEN("A deleted move constructible type, T"){
    struct T { T(T&&) = delete; };

    THEN("a Type<T> is not move constructible"){
      REQUIRE_FALSE(std::is_move_constructible<shacl::Optional<T>>::value);
    }
  }
}
