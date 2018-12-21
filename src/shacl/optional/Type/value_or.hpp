template<typename Arg>
constexpr auto value_or(Arg&& arg) const&
  -> std::enable_if_t
  <std::is_copy_constructible<T>::value
   and std::is_convertible<Arg&&, T>::value, T> {
  return this->has_value() ? **this : static_cast<T>(std::forward<Arg>(arg));
}

template<typename Arg>
constexpr auto value_or(Arg&& arg) &&
  -> std::enable_if_t
  <std::is_move_constructible<T>::value
   and std::is_convertible<Arg&&, T>::value, T> {
  return this->has_value() ? std::move(**this)
    : static_cast<T>(std::forward<Arg>(arg));
}
