#ifndef SHACL_OPTIONAL_HPP
#define SHACL_OPTIONAL_HPP

#if __cplusplus < 201703L
#define SHACL_OPTIONAL_BACKPORT
#include "mpark/in_place.hpp"
#else
#include <optional>
#endif

#ifdef __GNUC__
  #define likely(x)     __builtin_expect((x),1)
  #define unlikely(x)   __builtin_expect((x),0)
#else
  #define likely(x)    (x)
  #define unlikely(x)  (x)
#endif

#include "shacl/ebo.hpp"
#include "shacl/trait.hpp"

namespace shacl {
namespace optional {

#ifdef SHACL_OPTIONAL_BACKPORT

using mpark::in_place_t;
using mpark::in_place;

struct nullopt_t {};
static constexpr nullopt_t nullopt{};

template<typename T>
class Type;

#include "shacl/optional/detail.hpp"
#include "shacl/optional/bad_access.hpp"
#include "shacl/optional/Type.hpp"

#else //SHACL_OPTIONAL_BACKPORT

using std::in_place_t;
using std::in_place;

using std::nullopt_t;
using std::nullopt;

using bad_access = std::bad_optional_access;

template<typename T>
using Type = std::optional<T>;

#endif //SHACL_OPTIONAL_BACKPORT

#include "shacl/optional/detail/Curry.hpp"

#include "shacl/optional/IsInstance.hpp"

#ifdef SHACL_OPTIONAL_BACKPORT
#include "shacl/optional/comparison.hpp"
#endif

#include "shacl/optional/make.hpp"
#include "shacl/optional/map.hpp"
#include "shacl/optional/bind.hpp"

}

template<typename... Ts>
using Optional = optional::Type<Ts...>;

}

#endif //SHACL_OPTIONAL_HPP
