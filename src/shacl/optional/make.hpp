struct make_fn {
  template<typename T, typename Result = Type<std::decay_t<T>>>
  constexpr auto operator()(T&& arg) const
    noexcept(std::is_nothrow_constructible<Result, T>::value) {
    return Result{std::forward<T>(arg)};
  }
};

static constexpr make_fn make{};
