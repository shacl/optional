#include "catch2/catch.hpp"
#include "shacl/optional.hpp"

SCENARIO("Type move assignment"){
  GIVEN("A trivially move assignable type, T"){
    struct T {};
    THEN("a Type<T> is also trivially move assignable"){
      REQUIRE(std::is_trivially_move_assignable<shacl::Optional<T>>::value);
    }
  }

  GIVEN("A non-trivially move assignable type, T"){
    struct T {
      T(T&&) = default;
      T& operator=(T&&){ return *this; }
    };

    THEN("a Type<T> is also non-trivially move assignable"){
      REQUIRE_FALSE(std::is_trivially_move_assignable
                    <shacl::Optional<T>>::value);
    }
  }

  GIVEN("A noexcept(true) move assignable and move constructible type, T"){
    struct T {
      T(T&&) noexcept(true) {}
      T& operator=(T&&) noexcept(true);
    };

    THEN("a Type<T> is also noexcept(true) move assignable"){
      REQUIRE(std::is_nothrow_move_assignable<shacl::Optional<T>>::value);
    }
  }

  GIVEN("A noexcept(false) move assignable type, T"){
    struct T {
      T(T&&) noexcept(true) {}
      T& operator=(T&&) noexcept(false);
    };

    REQUIRE(std::is_nothrow_move_constructible<T>::value);
    REQUIRE_FALSE(std::is_nothrow_move_assignable<T>::value);

    THEN("a Type<T> is also noexcept(false) move assignable"){
      REQUIRE_FALSE(std::is_nothrow_move_assignable
                    <shacl::Optional<T>>::value);
    }
  }

  GIVEN("A noexcept(false) move constructible type, T"){
    struct T {
      T(T&&) noexcept(false) {}
      T& operator=(T&&) noexcept(true);
    };

    REQUIRE_FALSE(std::is_nothrow_move_constructible<T>::value);
    REQUIRE(std::is_nothrow_move_assignable<T>::value);

    THEN("a Type<T> is also noexcept(false) move assignable"){
      REQUIRE_FALSE(std::is_nothrow_move_assignable
                    <shacl::Optional<T>>::value);
    }
  }

}
