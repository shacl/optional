#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

namespace {
struct T{
  static int count;
  ~T(){ ++count; }
};

int T::count = 0;
}

SCENARIO("reset"){
  GIVEN("an optional"){
    shacl::Optional<T> o;

    WHEN("engaged"){
      o = T{};

      THEN("reset destructs the stored type and disengages the optional"){
        T::count = 0;
        o.reset();
        REQUIRE_FALSE(bool(o));
        REQUIRE(1 == T::count);
      }
    }

    WHEN("disengaged"){
      THEN("nothing happens"){
        T::count = 0;
        REQUIRE_FALSE(bool(o));
        REQUIRE(0 == T::count);
        o.reset();
        REQUIRE_FALSE(bool(o));
        REQUIRE(0 == T::count);
      }
    }
  }
}
