#include "shacl/optional.hpp"
#include "catch2/catch.hpp"

namespace {

struct U {
  static int dtorCount;
  static int moveCount;
  static int swapCount;

  U() = default;
  U(U&&) { ++moveCount; }
  ~U() { ++dtorCount; }

  friend void swap(U&, U&) { ++swapCount; }
};

int U::dtorCount = 0;
int U::moveCount = 0;
int U::swapCount = 0;

template<bool Construction, bool Swap>
struct NoexceptMock {
  NoexceptMock(NoexceptMock&&) noexcept(Construction);
  NoexceptMock& operator=(NoexceptMock&&) noexcept(true);
  friend void swap(NoexceptMock&, NoexceptMock&) noexcept(Swap){}
};

struct Swapless {
  friend void swap(Swapless&, Swapless&) = delete;
};

template<typename T,
         typename = shacl::trait::void_t
         <decltype(std::declval<T&>().swap(std::declval<T&>()))>>
bool hasSwap(int){ return true; }

template<typename T>
bool hasSwap(...){ return false; }

template<typename T,
         typename = shacl::trait::void_t
         <decltype(std::declval<T&>().swap(std::declval<T&>()))>>
bool swapNoThrow(){
  return noexcept(std::declval<T&>().swap(std::declval<T&>()));
}

}

SCENARIO("swap"){
  GIVEN("a swappable type, T"){
    GIVEN("T is noexcept move constructible"){
      GIVEN("T is noexcept swappable"){
        using T = NoexceptMock<true, true>;

        REQUIRE(std::is_nothrow_move_constructible<T>::value);
        REQUIRE(shacl::trait::SwapNoThrow_v<T>);

        THEN("swap of optional::Type<T> is noexcept"){
          REQUIRE(hasSwap<shacl::Optional<T>>(1));
          REQUIRE(swapNoThrow<shacl::Optional<T>>());
          REQUIRE(shacl::trait::SwapNoThrow_v<shacl::Optional<T>>);
        }
      }

      GIVEN("T is noexcept(false) swappable"){
        using T = NoexceptMock<true, false>;

        REQUIRE(std::is_nothrow_move_constructible<T>::value);
        REQUIRE_FALSE(shacl::trait::SwapNoThrow_v<T>);

        THEN("swap of optional::Type<T> is noexcept(false)"){
          REQUIRE(hasSwap<shacl::Optional<T>>(1));
          REQUIRE_FALSE(swapNoThrow<shacl::Optional<T>>());
          REQUIRE_FALSE(shacl::trait::SwapNoThrow_v<shacl::Optional<T>>);
        }
      }
    }

    GIVEN("T is noexcept(false) move constructible"){
      GIVEN("T is noexcept swappable"){
        using T = NoexceptMock<false, true>;

        REQUIRE_FALSE(std::is_nothrow_move_constructible<T>::value);
        REQUIRE(shacl::trait::SwapNoThrow_v<T>);

        THEN("swap of optional::Type<T> is noexcept(false)"){
          REQUIRE(hasSwap<shacl::Optional<T>>(1));
          REQUIRE_FALSE(swapNoThrow<shacl::Optional<T>>());
          REQUIRE_FALSE(shacl::trait::SwapNoThrow_v<shacl::Optional<T>>);
        }
      }

      GIVEN("T is noexcept(false) swappable"){
        using T = NoexceptMock<false, false>;

        REQUIRE_FALSE(std::is_nothrow_move_constructible<T>::value);
        REQUIRE_FALSE(shacl::trait::SwapNoThrow_v<T>);

        THEN("swap of optional::Type<T> is noexcept(false)"){
          REQUIRE(hasSwap<shacl::Optional<T>>(1));
          REQUIRE_FALSE(swapNoThrow<shacl::Optional<T>>());
          REQUIRE_FALSE(shacl::trait::SwapNoThrow_v<shacl::Optional<T>>);
        }
      }
    }
  }

  GIVEN("a non-swappable type, T"){
    using T = Swapless;

    THEN("swap of optional::Type<T> is not defined"){
      REQUIRE_FALSE(hasSwap<shacl::Optional<T>>(1));
      REQUIRE(shacl::trait::SwapDefined_v<shacl::Optional<T>>); // yes, really
    }
  }

  using std::swap;

  GIVEN("an engaged left optional"){
    shacl::Optional<U> left = U{};

    GIVEN("an engaged right optional"){
      shacl::Optional<U> right = U{};

      THEN("the underlying type's swap is called"){
        U::dtorCount = 0;
        U::moveCount = 0;
        U::swapCount = 0;

        left.swap(right);
        REQUIRE(0 == U::dtorCount);
        REQUIRE(0 == U::moveCount);
        REQUIRE(1 == U::swapCount);
      }
    }

    GIVEN("an disengaged right optional"){
      shacl::Optional<U> right;

      THEN("the underlying type's move is called"){
        U::dtorCount = 0;
        U::moveCount = 0;
        U::swapCount = 0;

        left.swap(right);
        REQUIRE(1 == U::dtorCount);
        REQUIRE(1 == U::moveCount);
        REQUIRE(0 == U::swapCount);
      }
    }
  }

  GIVEN("an disengaged left optional"){
    shacl::Optional<U> left;

    GIVEN("an engaged right optional"){
      shacl::Optional<U> right = U{};

      THEN("the underlying type's move is called"){
        U::dtorCount = 0;
        U::moveCount = 0;
        U::swapCount = 0;

        left.swap(right);
        REQUIRE(1 == U::dtorCount);
        REQUIRE(1 == U::moveCount);
        REQUIRE(0 == U::swapCount);
      }
    }

    GIVEN("an disengaged right optional"){
      shacl::Optional<U> right;

      THEN("no work is done"){
        U::dtorCount = 0;
        U::moveCount = 0;
        U::swapCount = 0;

        left.swap(right);
        REQUIRE(0 == U::dtorCount);
        REQUIRE(0 == U::moveCount);
        REQUIRE(0 == U::swapCount);
      }
    }
  }
}
