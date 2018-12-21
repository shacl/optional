#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

namespace {

struct U {
  mutable bool copiedFrom = false;
  bool movedFrom = false;
};

struct T {
  static int copy;
  static int move;
  static int copyAssign;
  static int moveAssign;
  static int dtor;

  T(){}
  T(const T&){ ++copy; }
  T(T&&){ ++move; }

  T(const U& u){ ++copy; u.copiedFrom = true; }
  T(U&& u){ ++move; u.movedFrom = true; }

  ~T(){ ++dtor; }

  T& operator=(U&& u){ u.movedFrom = true; return *this; }
  T& operator=(const U& u){ u.copiedFrom = true; return *this; }

  T& operator=(T&&){ ++moveAssign; return *this; }
  T& operator=(const T&){ ++copyAssign; return *this; }
};

int T::copy;
int T::move;
int T::copyAssign;
int T::moveAssign;
int T::dtor;

}

SCENARIO("assignment"){
  shacl::Optional<T> o;

  GIVEN("an engaged optional"){
    T t{};
    o = t;

    WHEN("move assigning"){
      T::moveAssign = 0;
      o = std::move(t);

      THEN("the underlying data is moved"){
        REQUIRE(1 == T::moveAssign);
      }
    }

    WHEN("copy assigning"){
      T::copyAssign = 0;
      o = t;

      THEN("the underlying data is copied"){
        REQUIRE(1 == T::moveAssign);
      }
    }

    WHEN("assigning from a nullopt"){
      T::dtor = 0;
      o = shacl::optional::nullopt;

      THEN("the underlying data is destructed"){
        REQUIRE(1 == T::dtor);
      }
    }

    WHEN("assigning from a convertible type"){
      U u{};

      WHEN("passed as an lvalue"){
        o = u;

        THEN("the argument is copied"){
          REQUIRE(true == u.copiedFrom);
        }
      }

      WHEN("passed as an rvalue"){
        o = std::move(u);

        THEN("the argument is copied"){
          REQUIRE(true == u.movedFrom);
        }
      }
    }

    WHEN("assigning from an optional of a convertible type"){
      shacl::Optional<U> ou;

      GIVEN("the optional is disengaged"){
        WHEN("passed as an lvalue"){
          o = ou;

          THEN("the lefthand optional will be disengaged"){
            REQUIRE(not o);
          }
        }

        WHEN("passed as an rvalue"){
          o = std::move(ou);

          THEN("the lefthand optional will be disengaged"){
            REQUIRE(not o);
          }
        }
      }

      GIVEN("the optional is engaged"){
        ou = U{};

        WHEN("passed as an lvalue"){
          o = ou;

          THEN("the righthand optional will be copied from"){
            REQUIRE(ou->copiedFrom);
            REQUIRE_FALSE(ou->movedFrom);
          }
        }

        WHEN("passed as an rvalue"){
          o = std::move(ou);

          THEN("the righthand optional will be moved from"){
            REQUIRE_FALSE(ou->copiedFrom);
            REQUIRE(ou->movedFrom);
          }
        }
      }
    }
  }

  GIVEN("an disengaged optional"){
    WHEN("assigning from a nullopt"){
      T::dtor = 0;
      o = shacl::optional::nullopt;

      THEN("no work is done"){
        REQUIRE(0 == T::dtor);
      }
    }

    WHEN("assigning from a convertible type"){
      U u{};

      WHEN("passed as an lvalue"){
        T::copy = 0;
        o = u;

        THEN("a data is copy constructed from the argument"){
          REQUIRE(1 == T::copy);
          REQUIRE(u.copiedFrom);
          REQUIRE_FALSE(u.movedFrom);
        }
      }

      WHEN("passed as an rvalue"){
        T::move = 0;
        o = std::move(u);
        THEN("a data is move constructed from the argument"){
          REQUIRE(1 == T::move);
          REQUIRE_FALSE(u.copiedFrom);
          REQUIRE(u.movedFrom);
        }
      }
    }

    WHEN("assigning from an optional of a convertible type"){
      shacl::Optional<U> ou;

      GIVEN("the optional is disengaged"){
        T::dtor = 0;

        WHEN("passed as an lvalue"){
          o = ou;

          THEN("no work is done"){
            REQUIRE(0 == T::dtor);
          }
        }

        WHEN("passed as an rvalue"){
          o = std::move(ou);

          THEN("no work is done"){
            REQUIRE(0 == T::dtor);
          }
        }
      }

      GIVEN("the optional is engaged"){
        shacl::Optional<U> ou = U{};

        WHEN("passed as an lvalue"){
          T::copy = 0;
          o = ou;

          THEN("a data is copy constructed from the argument"){
            REQUIRE(1 == T::copy);
            REQUIRE(ou->copiedFrom);
            REQUIRE_FALSE(ou->movedFrom);
          }
        }

        WHEN("passed as an rvalue"){
          T::move = 0;
          o = std::move(ou);

          THEN("a data is move constructed from the argument"){
            REQUIRE(1 == T::move);
            REQUIRE(ou->movedFrom);
            REQUIRE_FALSE(ou->copiedFrom);
          }
        }
      }
    }
  }
}
