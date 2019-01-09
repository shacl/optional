#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

struct RightFalseEquality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator==(const T&, RightFalseEquality){ return false; }

struct RightTrueEquality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator==(const T&, RightTrueEquality){ return true; }

struct LeftFalseEquality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator==(LeftFalseEquality, const T&){ return false; }

struct LeftTrueEquality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator==(LeftTrueEquality, const T&){ return true; }

SCENARIO("equality"){
  GIVEN("a type with an equality operator which returns a boolean"){
    struct EqualityComparable {
      bool operator==(const EqualityComparable&) const { return true; }
    };

    GIVEN("an instance of an optional instantiation of the type"){
      shacl::Optional<EqualityComparable> oe;

      GIVEN("the instance is disengaged"){
        WHEN("equality compared to a right nullopt"){
          THEN("the operation returns true"){
            REQUIRE(oe == shacl::optional::nullopt);
          }
        }

        WHEN("equality compared to a right instance of the type"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(oe == EqualityComparable{});
          }
        }

        WHEN("equality compared to a right instance of"
             " a distinct (but equality comparable) type"){
          GIVEN("the equality would return true with an instance of the left type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(oe == RightTrueEquality{});
            }
          }

          GIVEN("the equality would return false with an instance of the left type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(oe == RightFalseEquality{});
            }
          }
        }

        WHEN("equality compared to a right optional instance of the type"){
          shacl::Optional<EqualityComparable> other;

          GIVEN("the right optional is disengaged"){
            THEN("the operation returns true"){
              REQUIRE(oe == other);
            }
          }

          GIVEN("the right optional is engaged"){
            other = EqualityComparable{};

            THEN("the operation returns false"){
              REQUIRE_FALSE(oe == other);
            }
          }
        }

        WHEN("equality compared to a right optional instance of"
             " a distinct (but equality comparable) type"){
          GIVEN("the right optional is disengaged"){
            GIVEN("the equality would return true with an instance of the left type"){
              shacl::Optional<RightTrueEquality> other;

              THEN("the operation returns true"){
                REQUIRE(oe == other);
              }
            }

            GIVEN("the equality would return false with an instance of the left type"){
              shacl::Optional<RightFalseEquality> other;

              THEN("the operation returns true"){
                REQUIRE(oe == other);
              }
            }
          }

          GIVEN("the right optional is engaged"){
            GIVEN("the equality would return true with an instance of the left type"){
              shacl::Optional<RightTrueEquality> other = RightTrueEquality{};

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe == other);
              }
            }

            GIVEN("the equality would return false with an instance of the left type"){
              shacl::Optional<RightFalseEquality> other = RightFalseEquality{};

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe == other);
              }
            }
          }
        }

        WHEN("equality compared to a left nullopt"){
          THEN("the operation returns true"){
            REQUIRE(shacl::optional::nullopt == oe);
          }
        }

        WHEN("equality compared to a left instance of the type"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(EqualityComparable{} == oe);
          }
        }

        WHEN("equality compared to a left instance of"
             " a distinct (but equality comparable) type"){
          GIVEN("the equality would return true with an instance of the right type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(LeftTrueEquality{} == oe);
            }
          }

          GIVEN("the equality would return false with an instance of the right type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(LeftFalseEquality{} == oe);
            }
          }
        }
      }

      GIVEN("the instance is engaged"){
        oe = EqualityComparable{};

        WHEN("equality compared to a right nullopt"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(oe == shacl::optional::nullopt);
          }
        }

        WHEN("equality compared to a right instance of the type"){
          THEN("the operation returns true"){
            REQUIRE(oe == EqualityComparable{});
          }
        }

        WHEN("equality compared to a right instance of"
             " a distinct (but equality comparable) type"){
          GIVEN("the equality would return true with an instance of the left type"){
            THEN("the operation returns true"){
              REQUIRE(oe == RightTrueEquality{});
            }
          }

          GIVEN("the equality would return false with an instance of the left type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(oe == RightFalseEquality{});
            }
          }
        }

        WHEN("equality compared to a right optional instance of the type"){
          shacl::Optional<EqualityComparable> other;

          GIVEN("the right optional is disengaged"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(oe == other);
            }
          }

          GIVEN("the right optional is engaged"){
            other = EqualityComparable{};

            THEN("the operation returns true"){
              REQUIRE(oe == other);
            }
          }
        }

        WHEN("equality compared to a right optional instance of"
             " a distinct (but equality comparable) type"){
          GIVEN("the right optional is disengaged"){
            GIVEN("the equality would return true with an instance of the left type"){
              shacl::Optional<RightTrueEquality> other;

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe == other);
              }
            }

            GIVEN("the equality would return false with an instance of the left type"){
              shacl::Optional<RightFalseEquality> other;

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe == other);
              }
            }
          }

          GIVEN("the right optional is engaged"){
            GIVEN("the equality would return true with an instance of the left type"){
              shacl::Optional<RightTrueEquality> other = RightTrueEquality{};

              THEN("the operation returns true"){
                REQUIRE(oe == other);
              }
            }

            GIVEN("the equality would return false with an instance of the left type"){
              shacl::Optional<RightFalseEquality> other = RightFalseEquality{};

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe == other);
              }
            }
          }
        }

        WHEN("equality compared to a left nullopt"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(shacl::optional::nullopt == oe);
          }
        }

        WHEN("equality compared to a left instance of the type"){
          THEN("the operation returns true"){
            REQUIRE(EqualityComparable{} == oe);
          }
        }

        WHEN("equality compared to a left instance of"
             " a distinct (but equality comparable) type"){
          GIVEN("the equality would return true with an instance of the right type"){
            THEN("the operation returns true"){
              REQUIRE(LeftTrueEquality{} == oe);
            }
          }

          GIVEN("the equality would return false with an instance of the right type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(LeftFalseEquality{} == oe);
            }
          }
        }
      }
    }
  }
}
