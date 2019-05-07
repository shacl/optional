#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

SCENARIO("value_or"){
  struct U {
    mutable bool copiedFrom = false;
    mutable bool movedFrom = false;
  };

  struct T {
    mutable bool copiedFrom = false;
    mutable bool movedFrom = false;

    T() = default;
    T(T&& that) { that.movedFrom = true; }
    T& operator=(T&&) { return *this; }

    T(const T& that) { that.copiedFrom = true; }
    T(U&& that) { that.movedFrom = true; }
    T(const U& that) { that.copiedFrom = true; }
  };

  auto ignore = [](auto&&){};

  shacl::Optional<T> o;

  GIVEN("an optional const lvalue"){
    const auto& co = o;

    GIVEN("the optional is engaged"){
      o = T{};

      GIVEN("an argument of the optional parameter type"){
        auto arg = T{};

        THEN("the value_or method should copy the stored value"){
          auto t = co.value_or(arg);
          ignore(t);
          REQUIRE_FALSE(arg.copiedFrom);
          REQUIRE_FALSE(arg.movedFrom);
          REQUIRE(co.value().copiedFrom);
          REQUIRE_FALSE(co.value().movedFrom);
        }
      }

      GIVEN("an argument convertible to the optional parameter type"){
        auto arg = U{};

        THEN("the value_or method should copy the stored value"){
          auto t = co.value_or(arg);
          ignore(t);
          REQUIRE_FALSE(arg.copiedFrom);
          REQUIRE_FALSE(arg.movedFrom);
          REQUIRE(co.value().copiedFrom);
          REQUIRE_FALSE(co.value().movedFrom);
        }
      }
    }

    GIVEN("the optional is disengaged"){
      GIVEN("an argument of the optional parameter type"){
        auto arg = T{};

        GIVEN("the argument is an lvalue"){
          THEN("the value_or method should copy the argument"){
            auto t = co.value_or(arg);
            ignore(t);
            REQUIRE(arg.copiedFrom);
            REQUIRE_FALSE(arg.movedFrom);
          }
        }

        GIVEN("the argument is an rvalue"){
          THEN("the value_or method should move the argument"){
            auto t = co.value_or(std::move(arg));
            ignore(t);
            REQUIRE_FALSE(arg.copiedFrom);
            REQUIRE(arg.movedFrom);
          }
        }
      }

      GIVEN("an argument convertible to the optional parameter type"){
        auto arg = U{};

        GIVEN("the argument is an lvalue"){
          THEN("the value_or method should copy the argument"){
            auto t = co.value_or(arg);
            ignore(t);
            REQUIRE(arg.copiedFrom);
            REQUIRE_FALSE(arg.movedFrom);
          }
        }

        GIVEN("the argument is an rvalue"){
          THEN("the value_or method should move the argument"){
            auto t = co.value_or(std::move(arg));
            ignore(t);
            REQUIRE_FALSE(arg.copiedFrom);
            REQUIRE(arg.movedFrom);
          }
        }
      }
    }
  }

  GIVEN("an optional mutable rvalue"){
    GIVEN("the optional is engaged"){
      o = T{};

      GIVEN("an argument of the optional parameter type"){
        auto arg = T{};

        THEN("the value_or method should move the stored value"){
          auto t = std::move(o).value_or(arg);
          ignore(t);
          REQUIRE_FALSE(arg.copiedFrom);
          REQUIRE_FALSE(arg.movedFrom);
          REQUIRE_FALSE(o.value().copiedFrom);
          REQUIRE(o.value().movedFrom);
        }
      }

      GIVEN("an argument convertible to the optional parameter type"){
        auto arg = U{};

        THEN("the value_or method should move the stored value"){
          auto t = std::move(o).value_or(arg);
          ignore(t);
          REQUIRE_FALSE(arg.copiedFrom);
          REQUIRE_FALSE(arg.movedFrom);
          REQUIRE_FALSE(o.value().copiedFrom);
          REQUIRE(o.value().movedFrom);
        }
      }
    }

    GIVEN("the optional is disengaged"){
      GIVEN("an argument of the optional parameter type"){
        auto arg = T{};

        GIVEN("the argument is an lvalue"){
          THEN("the value_or method should copy the argument"){
            auto t = std::move(o).value_or(arg);
            ignore(t);
            REQUIRE(arg.copiedFrom);
            REQUIRE_FALSE(arg.movedFrom);
          }
        }

        GIVEN("the argument is an rvalue"){
          THEN("the value_or method should move the argument"){
            auto t = std::move(o).value_or(std::move(arg));
            ignore(t);
            REQUIRE_FALSE(arg.copiedFrom);
            REQUIRE(arg.movedFrom);
          }
        }
      }

      GIVEN("an argument convertible to the optional parameter type"){
        auto arg = U{};

        GIVEN("the argument is an lvalue"){
          THEN("the value_or method should copy the argument"){
            auto t = std::move(o).value_or(arg);
            ignore(t);
            REQUIRE(arg.copiedFrom);
            REQUIRE_FALSE(arg.movedFrom);
          }
        }

        GIVEN("the argument is an rvalue"){
          THEN("the value_or method should move the argument"){
            auto t = std::move(o).value_or(std::move(arg));
            ignore(t);
            REQUIRE_FALSE(arg.copiedFrom);
            REQUIRE(arg.movedFrom);
          }
        }
      }
    }
  }
}
