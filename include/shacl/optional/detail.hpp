namespace detail {

#include "shacl/optional/detail/all.hpp"
#ifdef SHACL_OPTIONAL_BACKPORT
#include "shacl/optional/detail/Storage.hpp"
#include "shacl/optional/detail/Operations.hpp"
#include "shacl/optional/detail/Copy.hpp"
#include "shacl/optional/detail/Move.hpp"
#include "shacl/optional/detail/CopyAssign.hpp"
#include "shacl/optional/detail/MoveAssign.hpp"
#include "shacl/optional/detail/Enabled.hpp"

template <typename T, typename U>
using enable_forward_value =
  std::enable_if_t
  <std::is_constructible<T, U&&>::value
   and not std::is_same<std::decay_t<U>, in_place_t>::value
   and not std::is_same<Type<T>, std::decay_t<U>>::value,
   bool>;

template <typename T, typename U, typename Other>
using enable_from_other =
  std::enable_if_t
  <std::is_constructible<T, Other>::value
   and not std::is_constructible<T, Type<U>&>::value
   and not std::is_constructible<T, Type<U>&&>::value
   and not std::is_constructible<T, const Type<U>&>::value
   and not std::is_constructible<T, const Type<U>&&>::value
   and not std::is_convertible<Type<U>&, T>::value
   and not std::is_convertible<Type<U>&&, T>::value
   and not std::is_convertible<const Type<U>&, T>::value
   and not std::is_convertible<const Type<U>&&, T>::value,
   bool>;

template <typename T, typename U>
using enable_assign_forward =
  std::enable_if_t
  <not std::is_same<Type<T>, std::decay_t<U>>::value
   and not trait::Conjunction_v
           <std::is_scalar<T>, std::is_same<T, std::decay_t<U>>>
   and std::is_constructible<T, U>::value
   and std::is_assignable<T&, U>::value,
   bool>;

template <typename T, typename U, typename Other>
using enable_assign_from_other =
  std::enable_if_t
  <std::is_constructible<T, Other>::value
   and std::is_assignable<T&, Other>::value
   and not std::is_constructible<T, Type<U>&>::value
   and not std::is_constructible<T, Type<U> &&>::value
   and not std::is_constructible<T, const Type<U>&>::value
   and not std::is_constructible<T, const Type<U>&&>::value
   and not std::is_convertible<Type<U>&, T>::value
   and not std::is_convertible<Type<U>&&, T>::value
   and not std::is_convertible<const Type<U>&, T>::value
   and not std::is_convertible<const Type<U>&&, T>::value
   and not std::is_assignable<T&, Type<U>&>::value
   and not std::is_assignable<T&, Type<U>&&>::value
   and not std::is_assignable<T&, const Type<U>&>::value
   and not std::is_assignable<T&, const Type<U>&&>::value,
   bool>;
#endif
}
