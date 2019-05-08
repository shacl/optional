#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

struct RightFalseInequality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator!=(const T&, RightFalseInequality){ return false; }

struct RightTrueInequality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator!=(const T&, RightTrueInequality){ return true; }

struct LeftFalseInequality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator!=(LeftFalseInequality, const T&){ return false; }

struct LeftTrueInequality {};

template<typename T,
         std::enable_if_t
         <not shacl::optional::IsInstance_v<T>, bool> = true>
bool operator!=(LeftTrueInequality, const T&){ return true; }

SCENARIO("inequality"){
  GIVEN("a type with an inequality operator which returns a boolean"){
    struct InequalityComparable {
      bool operator!=(const InequalityComparable&) const { return false; }
    };

    GIVEN("an instance of an optional instantiation of the type"){
      shacl::Optional<InequalityComparable> oe;

      GIVEN("the instance is disengaged"){
        WHEN("inequality compared to a right nullopt"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(oe != shacl::optional::nullopt);
          }
        }

        WHEN("inequality compared to a right instance of the type"){
          THEN("the operation returns true"){
            REQUIRE(oe != InequalityComparable{});
          }
        }

        WHEN("inequality compared to a right instance of"
             " a distinct (but inequality comparable) type"){
          GIVEN("the inequality would return true with an instance of the left type"){
            THEN("the operation returns true"){
              REQUIRE(oe != RightTrueInequality{});
            }
          }

          GIVEN("the inequality would return false with an instance of the left type"){
            THEN("the operation returns true"){
              REQUIRE(oe != RightFalseInequality{});
            }
          }
        }

        WHEN("inequality compared to a right optional instance of the type"){
          shacl::Optional<InequalityComparable> other;

          GIVEN("the right optional is disengaged"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(oe != other);
            }
          }

          GIVEN("the right optional is engaged"){
            other = InequalityComparable{};

            THEN("the operation returns true"){
              REQUIRE(oe != other);
            }
          }
        }

        WHEN("inequality compared to a right optional instance of"
             " a distinct (but inequality comparable) type"){
          GIVEN("the right optional is disengaged"){
            GIVEN("the inequality would return true with an instance of the left type"){
              shacl::Optional<RightTrueInequality> other;

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe != other);
              }
            }

            GIVEN("the inequality would return false with an instance of the left type"){
              shacl::Optional<RightFalseInequality> other;

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe != other);
              }
            }
          }

          GIVEN("the right optional is engaged"){
            GIVEN("the inequality would return true with an instance of the left type"){
              shacl::Optional<RightTrueInequality> other = RightTrueInequality{};

              THEN("the operation returns true"){
                REQUIRE(oe != other);
              }
            }

            GIVEN("the inequality would return false with an instance of the left type"){
              shacl::Optional<RightFalseInequality> other = RightFalseInequality{};

              THEN("the operation returns true"){
                REQUIRE(oe != other);
              }
            }
          }
        }

        WHEN("inequality compared to a left nullopt"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(shacl::optional::nullopt != oe);
          }
        }

        WHEN("inequality compared to a left instance of the type"){
          THEN("the operation returns true"){
            REQUIRE(InequalityComparable{} != oe);
          }
        }

        WHEN("inequality compared to a left instance of"
             " a distinct (but inequality comparable) type"){
          GIVEN("the inequality would return true with an instance of the right type"){
            THEN("the operation returns true"){
              REQUIRE(LeftTrueInequality{} != oe);
            }
          }

          GIVEN("the inequality would return false with an instance of the right type"){
            THEN("the operation returns true"){
              REQUIRE(LeftFalseInequality{} != oe);
            }
          }
        }
      }

      GIVEN("the instance is engaged"){
        oe = InequalityComparable{};

        WHEN("inequality compared to a right nullopt"){
          THEN("the operation returns true"){
            REQUIRE(oe != shacl::optional::nullopt);
          }
        }

        WHEN("inequality compared to a right instance of the type"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(oe != InequalityComparable{});
          }
        }

        WHEN("inequality compared to a right instance of"
             " a distinct (but inequality comparable) type"){
          GIVEN("the inequality would return true with an instance of the left type"){
            THEN("the operation returns true"){
              REQUIRE(oe != RightTrueInequality{});
            }
          }

          GIVEN("the inequality would return false with an instance of the left type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(oe != RightFalseInequality{});
            }
          }
        }

        WHEN("inequality compared to a right optional instance of the type"){
          shacl::Optional<InequalityComparable> other;

          GIVEN("the right optional is disengaged"){
            THEN("the operation returns true"){
              REQUIRE(oe != other);
            }
          }

          GIVEN("the right optional is engaged"){
            other = InequalityComparable{};

            THEN("the operation returns false"){
              REQUIRE_FALSE(oe != other);
            }
          }
        }

        WHEN("inequality compared to a right optional instance of"
             " a distinct (but inequality comparable) type"){
          GIVEN("the right optional is disengaged"){
            GIVEN("the inequality would return true with an instance of the left type"){
              shacl::Optional<RightTrueInequality> other;

              THEN("the operation returns true"){
                REQUIRE(oe != other);
              }
            }

            GIVEN("the inequality would return false with an instance of the left type"){
              shacl::Optional<RightFalseInequality> other;

              THEN("the operation returns true"){
                REQUIRE(oe != other);
              }
            }
          }

          GIVEN("the right optional is engaged"){
            GIVEN("the inequality would return true with an instance of the left type"){
              shacl::Optional<RightTrueInequality> other = RightTrueInequality{};

              THEN("the operation returns true"){
                REQUIRE(oe != other);
              }
            }

            GIVEN("the inequality would return false with an instance of the left type"){
              shacl::Optional<RightFalseInequality> other = RightFalseInequality{};

              THEN("the operation returns false"){
                REQUIRE_FALSE(oe != other);
              }
            }
          }
        }

        WHEN("inequality compared to a left nullopt"){
          THEN("the operation returns true"){
            REQUIRE(shacl::optional::nullopt != oe);
          }
        }

        WHEN("inequality compared to a left instance of the type"){
          THEN("the operation returns false"){
            REQUIRE_FALSE(InequalityComparable{} != oe);
          }
        }

        WHEN("inequality compared to a left instance of"
             " a distinct (but inequality comparable) type"){
          GIVEN("the inequality would return true with an instance of the right type"){
            THEN("the operation returns true"){
              REQUIRE(LeftTrueInequality{} != oe);
            }
          }

          GIVEN("the inequality would return false with an instance of the right type"){
            THEN("the operation returns false"){
              REQUIRE_FALSE(LeftFalseInequality{} != oe);
            }
          }
        }
      }
    }
  }
}
