/* comparison to left nullopt */
template<typename U>
constexpr bool
operator==(nullopt_t, const Type<U>& right) { return not right.has_value(); }

template<typename U>
constexpr bool
operator!=(nullopt_t, const Type<U>& right) { return right.has_value(); }

template<typename U>
constexpr bool
operator<(nullopt_t, const Type<U>& right) { return right.has_value(); }

template<typename U>
constexpr bool operator<=(nullopt_t, const Type<U>&) { return true; }

template<typename U>
constexpr bool operator>(nullopt_t, const Type<U>&) { return false; }

template<typename U>
constexpr bool
operator>=(nullopt_t, const Type<U>& right) { return not right.has_value(); }

/* comparison to left value */
template<typename T, typename U,
         std::enable_if_t
         <not IsInstance_v<T>
          and trait::EqualityDefined_v<const T&, const U&>
          and std::is_convertible
              <trait::EqualityResult_t<const T&, const U&>, bool>::value,
          bool> = true>
constexpr bool operator==(const T& left, const Type<U>& right) {
  return right.has_value() and static_cast<bool>(left == *right);
}

template<typename T, typename U,
         std::enable_if_t
         <not IsInstance_v<T>
          and trait::InequalityDefined_v<const T&, const U&>
          and std::is_convertible
              <trait::InequalityResult_t<const T&, const U&>, bool>::value,
          bool> = true>
constexpr bool operator!=(const T& left, const Type<U>& right) {
  return (not right.has_value()) or static_cast<bool>(left != *right);
}

template<typename T, typename U,
         std::enable_if_t
         <not IsInstance_v<T>
          and trait::LessThanDefined_v<const T&, const U&>
          and std::is_convertible
              <trait::LessThanResult_t<const T&, const U&>, bool>::value,
          bool> = true>
constexpr bool operator<(const T& left, const Type<U>& right) {
  return right.has_value() and static_cast<bool>(left < *right);
}

template<typename T, typename U,
         std::enable_if_t
         <not IsInstance_v<T>
          and trait::LessThanEqualDefined_v<const T&, const U&>
          and std::is_convertible
              <trait::LessThanEqualResult_t<const T&, const U&>, bool>::value,
          bool> = true>
constexpr bool operator<=(const T& left, const Type<U>& right) {
  return right.has_value() and static_cast<bool>(left <= *right);
}

template<typename T, typename U,
         std::enable_if_t
         <not IsInstance_v<T>
          and trait::GreaterThanDefined_v<const T&, const U&>
          and std::is_convertible
              <trait::GreaterThanResult_t<const T&, const U&>, bool>::value,
          bool> = true>
constexpr bool operator>(const T& left, const Type<U>& right) {
  return (not right.has_value()) or static_cast<bool>(left > *right);
}

template<typename T, typename U,
         std::enable_if_t
         <not IsInstance_v<T>
          and trait::GreaterThanEqualDefined_v<const T&, const U&>
          and std::is_convertible
              <trait::GreaterThanEqualResult_t
               <const T&, const U&>, bool>::value,
          bool> = true>
constexpr bool operator>=(const T& left, const Type<U>& right) {
  return (not right.has_value()) or static_cast<bool>(left >= *right);
}
