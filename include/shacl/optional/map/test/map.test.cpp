#define CATCH_CONFIG_MAIN
#include "shacl/optional.hpp"

#include "catch2/catch.hpp"
#include <string>

template<typename F, typename Arg, typename = void>
constexpr const bool PipeDefined_v = false;

template<typename F, typename Arg>
constexpr const bool
PipeDefined_v<F, Arg, shacl::trait::void_t
              <decltype(std::declval<Arg>() | std::declval<F>())>> = true;

struct Argument{};
struct Nonargument{};

template<int i>
struct Result {
  static constexpr int value(){ return i; }
  bool operator==(const Result&) const { return true; }
  bool operator!=(const Result&) const { return false; }
};

struct Callable {
  Result<0> operator()(Argument) & { return {}; }
  Result<1> operator()(Argument) && { return {}; }
  Result<2> operator()(Argument) const & { return {}; }
  Result<3> operator()(Argument) const && { return {}; }
};

SCENARIO("map"){
  GIVEN("a callable"){
    Callable callable{};

    GIVEN("an optional parameterized on an appropriate argument type"){
      shacl::Optional<Argument> oa;

      THEN("the map call of the callable and the optional is defined"){
        static_assert(shacl::trait::InvokeDefined_v
                      <shacl::optional::map_fn,
                       Callable,
                       shacl::Optional<Argument>>, "");
      }

      THEN("the map call results in optional parameterized on the result type"){
        GIVEN("a mutable lvalue callable"){
          using CallResultType =
            shacl::trait::InvokeResult_t<Callable&, Argument>;

          using ExpectedResultType = shacl::Optional<CallResultType>;
          using ActualResultType =
            shacl::trait::InvokeResult_t<shacl::optional::map_fn,
                                         Callable&,
                                         shacl::Optional<Argument>>;

          static_assert(std::is_same
                        <ExpectedResultType, ActualResultType>::value, "");
        }

        GIVEN("a constant lvalue callable"){
          using CallResultType =
            shacl::trait::InvokeResult_t<const Callable&, Argument>;

          using ExpectedResultType = shacl::Optional<CallResultType>;
          using ActualResultType =
            shacl::trait::InvokeResult_t<shacl::optional::map_fn,
                                         const Callable&,
                                         shacl::Optional<Argument>>;

          static_assert(std::is_same
                        <ExpectedResultType, ActualResultType>::value, "");
        }

        GIVEN("a mutable rvalue callable"){
          using CallResultType =
            shacl::trait::InvokeResult_t<Callable&&, Argument>;

          using ExpectedResultType = shacl::Optional<CallResultType>;
          using ActualResultType =
            shacl::trait::InvokeResult_t<shacl::optional::map_fn,
                                         Callable&&,
                                         shacl::Optional<Argument>>;

          static_assert(std::is_same
                        <ExpectedResultType, ActualResultType>::value, "");
        }

        GIVEN("a constant rvalue callable"){
          using CallResultType =
            shacl::trait::InvokeResult_t<const Callable&&, Argument>;

          using ExpectedResultType = shacl::Optional<CallResultType>;
          using ActualResultType =
            shacl::trait::InvokeResult_t<shacl::optional::map_fn,
                                         const Callable&&,
                                         shacl::Optional<Argument>>;

          static_assert(std::is_same
                        <ExpectedResultType, ActualResultType>::value, "");
        }
      }

      GIVEN("the optional is disengaged"){
        THEN("the resuling optional will be disengaged"){
          REQUIRE_FALSE(shacl::optional::map(callable, oa).has_value());
        }
      }

      GIVEN("the optional is engaged"){
        oa = Argument{};

        GIVEN("an mutable lvalue reference callable"){
          THEN("the resulting optional will be engaged"){
            auto oresult = shacl::optional::map(callable, oa);
            REQUIRE(oresult.has_value());
            REQUIRE(0 == oresult->value());
          }
        }

        GIVEN("an mutable rvalue reference callable"){
          THEN("the resulting optional will be engaged"){
            auto oresult = shacl::optional::map(std::move(callable), oa);
            REQUIRE(oresult.has_value());
            REQUIRE(1 == oresult->value());
          }
        }

        GIVEN("an constant lvalue reference callable"){
          const auto& ccallable = callable;

          THEN("the resulting optional will be engaged"){
            auto oresult = shacl::optional::map(ccallable, oa);
            REQUIRE(oresult.has_value());
            REQUIRE(2 == oresult->value());
          }
        }

        GIVEN("an constant rvalue reference callable"){
          const auto& ccallable = callable;

          THEN("the resulting optional will be engaged"){
            auto oresult = shacl::optional::map(std::move(ccallable), oa);
            REQUIRE(oresult.has_value());
            REQUIRE(3 == oresult->value());
          }
        }
      }
    }

    GIVEN("an optional containing an inappropriate argument type"){
      THEN("the map call is not defined"){
        static_assert(not shacl::trait::InvokeDefined_v
                          <shacl::optional::map_fn,
                           Callable,
                           shacl::Optional<Nonargument>>, "");
      }
    }

    WHEN("passed as a single argument to map"){
      auto liftedCallable = shacl::optional::map(callable);

      GIVEN("an optional parameterized on an appropriate argument type"){
        shacl::Optional<Argument> oa;

        THEN("the resulting callable accepts the optional as an argument"){
          static_assert(shacl::trait::InvokeDefined_v
                        <decltype(liftedCallable),
                         shacl::Optional<Argument>>, "");

          THEN("the lifted callable respects value categories"){
            GIVEN("an mutable callable"){
              GIVEN("an lvalue reference"){
                static_assert(std::is_same
                              <shacl::Optional<Result<0>>,
                               shacl::trait::InvokeResult_t
                               <decltype(liftedCallable)&,
                                shacl::Optional<Argument>>>::value, "");
              }

              GIVEN("an rvalue reference"){
                static_assert(std::is_same
                              <shacl::Optional<Result<1>>,
                               shacl::trait::InvokeResult_t
                               <decltype(liftedCallable)&&,
                                shacl::Optional<Argument>>>::value, "");
              }
            }

            GIVEN("an constant callable"){
              GIVEN("an lvalue reference"){
                static_assert(std::is_same
                              <shacl::Optional<Result<2>>,
                               shacl::trait::InvokeResult_t
                               <const decltype(liftedCallable)&,
                                shacl::Optional<Argument>>>::value, "");
              }

              GIVEN("an rvalue reference"){
                static_assert(std::is_same
                              <shacl::Optional<Result<3>>,
                               shacl::trait::InvokeResult_t
                               <const decltype(liftedCallable)&&,
                                shacl::Optional<Argument>>>::value, "");
              }
            }
          }
        }

        THEN("the optional can be 'piped' to the resulting callable"){
          static_assert(PipeDefined_v
                        <decltype(liftedCallable),
                         shacl::Optional<Argument>>, "");
        }

        THEN("the resulting callable results in an optional"){
          static_assert(shacl::optional::IsInstance_v
                        <shacl::trait::InvokeResult_t
                        <decltype(liftedCallable),
                         shacl::Optional<Argument>>>, "");
        }

        GIVEN("the optional is disengaged"){
          THEN("the resulting optional will be disengaged"){
            REQUIRE_FALSE(liftedCallable(oa).has_value());
          }

          THEN("pipeing arguments is equivalent to calling"){
            REQUIRE(liftedCallable(oa) == (oa | liftedCallable));
          }
        }

        GIVEN("the optional is engaged"){
          oa = Argument{};

          THEN("the resuling optional will be engaged"){
            auto oresult = liftedCallable(oa);
            REQUIRE(oresult.has_value());
            REQUIRE(0 == oresult->value());
          }

          THEN("pipeing arguments is equivalent to calling"){
            REQUIRE(liftedCallable(oa) == (oa | liftedCallable));
          }
        }
      }

      GIVEN("an optional containing an inappropriate argument type"){
        THEN("the resulting callable does not accept an"
             " optional of the argument type as an argument"){
          static_assert(not PipeDefined_v<decltype(liftedCallable),
                                          shacl::Optional<Nonargument>>, "");
        }
      }
    }
  }
}
