Type& operator=(const Type&) = default;
Type& operator=(Type&&) = default;

Type& operator=(nullopt_t) noexcept {
  if (this->has_value()) { this->resetData(); }
  return *this;
}

template<typename Arg = T, detail::enable_assign_forward<T, Arg> = true>
Type& operator=(Arg&& arg)
  noexcept(std::is_nothrow_assignable<T&, Arg>::value
           and std::is_nothrow_constructible<T, Arg>::value) {
  if (this->has_value()) {
    this->data = std::forward<Arg>(arg);
  } else {
    this->construct(std::forward<Arg>(arg));
  }
  return *this;
}

template<typename U, detail::enable_assign_from_other<T, U, const U&> = true>
Type& operator=(const Type<U>& arg)
  noexcept(std::is_nothrow_assignable<T, U&>::value
           and std::is_nothrow_constructible<T, U&>::value) {
  this->assign(arg);
  return *this;
}

template<typename U, detail::enable_assign_from_other<T, U, U&&> = true>
Type& operator=(Type<U>&& arg)
  noexcept(std::is_nothrow_assignable<T, U&&>::value
           and std::is_nothrow_constructible<T, U&&>::value) {
  this->assign(std::move(arg));
  return *this;
}
