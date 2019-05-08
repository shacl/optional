#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

SCENARIO("value"){
  struct T{
    std::integral_constant<int, 0> method() & { return {}; }
    std::integral_constant<int, 1> method() && { return {}; }
    std::integral_constant<int, 2> method() const& { return {}; }
    std::integral_constant<int, 3> method() const&& { return {}; }
  };

  shacl::Optional<T> o;

  GIVEN("an optional mutable lvalue"){
    GIVEN("the optional is engaged"){
      o = T{};

      THEN("the value method should return a mutable lvalue reference"){
        REQUIRE(0 == o.value().method().value);
      }
    }

    GIVEN("the optional is disengaged"){
      THEN("the value method should throw an exception"){
        REQUIRE_THROWS(o.value());
      }
    }
  }

  GIVEN("an optional mutable rvalue"){
    GIVEN("the optional is engaged"){
      o = T{};
      THEN("the value method should return a mutable rvalue reference"){
        REQUIRE(1 == std::move(o).value().method().value);
      }
    }

    GIVEN("the optional is disengaged"){
      THEN("the value method should throw an exception"){
        REQUIRE_THROWS(std::move(o).value());
      }
    }
  }

  const auto& co = o;

  GIVEN("an optional constant lvalue"){
    GIVEN("the optional is engaged"){
      o = T{};

      THEN("the value method should return a const lvalue reference"){
         REQUIRE(2 == co.value().method().value);
      }
    }

    GIVEN("the optional is disengaged"){
      THEN("the value method should throw an exception"){
        REQUIRE_THROWS(co.value());
      }
    }
  }

  GIVEN("an optional constant rvalue"){
    GIVEN("the optional is engaged"){
      o = T{};
      THEN("the value method should return a const rvalue reference"){
        REQUIRE(3 == std::move(co).value().method().value);
      }
    }

    GIVEN("the optional is disengaged"){
      THEN("the value method should throw an exception"){
        REQUIRE_THROWS(std::move(co).value());
      }
    }
  }
}
