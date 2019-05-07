constexpr bool operator==(nullopt_t) const { return (not this->has_value()); }
constexpr bool operator!=(nullopt_t) const { return this->has_value(); }
constexpr bool operator<(nullopt_t) const { return false; }
constexpr bool operator<=(nullopt_t) const { return not this->has_value(); }
constexpr bool operator>(nullopt_t) const { return this->has_value(); }
constexpr bool operator>=(nullopt_t) const { return true; }

template<typename U = T, typename V,
         std::enable_if_t
         <trait::EqualityDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::EqualityResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator==(const Type<V>& that) const {
  if(this->has_value() != that.has_value()){ return false; }
  return (not this->has_value()) or static_cast<bool>(**this == *that);
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::InequalityDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::InequalityResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator!=(const Type<V>& that) const {
  if(this->has_value() != that.has_value()){ return true; }
  return this->has_value() and static_cast<bool>(**this != *that);
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::LessThanDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::LessThanResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator<(const Type<V>& that) const {
  return
    that.has_value()
    and ((not this->has_value()) or static_cast<bool>(**this < *that));
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::LessThanEqualDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::LessThanEqualResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator<=(const Type<V>& that) const {
  return
    (not this->has_value())
    or (that.has_value() and static_cast<bool>(**this <= *that));
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::GreaterThanDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::GreaterThanResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator>(const Type<V>& that) const {
  return
    this->has_value()
    and (not that.has_value() or static_cast<bool>(**this > *that));
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::GreaterThanEqualDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::GreaterThanEqualResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator>=(const Type<V>& that) const {
  return
    (not that.has_value())
    or (this->has_value() and static_cast<bool>(**this >= *that));
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::EqualityDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::EqualityResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator==(const V& that) const {
  return this->has_value() and static_cast<bool>(**this == that);
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::InequalityDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::InequalityResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator!=(const V& that) const {
  return (not this->has_value()) or static_cast<bool>(**this != that);
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::LessThanDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::LessThanResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator<(const V& that) const {
  return (not this->has_value()) or static_cast<bool>(**this < that);
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::LessThanEqualDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::LessThanEqualResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator<=(const V& that) const {
  return (not this->has_value()) or (static_cast<bool>(**this <= that));
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::GreaterThanDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::GreaterThanResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator>(const V& that) const {
  return this->has_value() and static_cast<bool>(**this > that);
}

template<typename U = T, typename V,
         std::enable_if_t
         <trait::GreaterThanEqualDefined_v<const U&, const V&>
          and std::is_convertible
              <trait::GreaterThanEqualResult_t<const U&, const V&>, bool>::value,
          bool> = true>
constexpr bool operator>=(const V& that) const {
  return this->has_value() and static_cast<bool>(**this >= that);
}
