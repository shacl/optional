#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

SCENARIO("dereference"){
  struct T {
    std::integral_constant<int, 0> method() & { return {}; }
    std::integral_constant<int, 1> method() && { return {}; }
    std::integral_constant<int, 2> method() const& { return {}; }
    std::integral_constant<int, 3> method() const&& { return {}; }
  };

  GIVEN("an optional mutable lvalue"){
    shacl::Optional<T> o;

    THEN("dereference should return a mutable lvalue reference"){
      REQUIRE(std::is_same<T&, decltype(*o)>::value);
    }

    THEN("arrow should call the mutable lvalue reference overload"){
      REQUIRE(0 == o->method().value);
    }
  }

  GIVEN("an optional constant lvalue"){
    const shacl::Optional<T> o;

    THEN("the value method should return a const lvalue reference"){
      REQUIRE(std::is_same<const T&, decltype(*o)>::value);
    }

    THEN("arrow should call the const lvalue reference overload"){
      REQUIRE(2 == o->method().value);
    }
  }

  GIVEN("an optional mutable rvalue"){
    shacl::Optional<T> o;

    THEN("the value method should return a mutable rvalue reference"){
      REQUIRE(std::is_same<T&&, decltype(*(std::move(o)))>::value);
    }

    THEN("arrow should call the mutable lvalue reference overload (yes, really)"){
      REQUIRE(0 == std::move(o)->method().value);
    }
  }

  GIVEN("an optional constant rvalue"){
    const shacl::Optional<T> o;

    THEN("the value method should return a const rvalue reference"){
      REQUIRE(std::is_same<const T&&, decltype(*(std::move(o)))>::value);
    }

    THEN("arrow should call the const lvalue reference overload (yes, really)"){
      REQUIRE(2 == std::move(o)->method().value);
    }
  }
}
