class map_fn {
  template<typename Fn, typename... Args>
  using Result = Type<trait::InvokeResult_t
                      <Fn, decltype(std::declval<Args>.value())...>>;

  template<typename Fn>
  using Curry = detail::Curry<Fn, map_fn, Result>;

public:
  template<typename Fn>
  constexpr auto operator()(Fn&& fn) const {
    return Curry<std::decay_t<Fn>>{std::forward<Fn>(fn)};
  }

  template<typename Fn, typename Arg, typename... Args,
           std::enable_if_t
           <detail::all
            (IsInstance_v<std::decay_t<Arg>>,
             IsInstance_v<std::decay_t<Args>>...), bool> = true>
  constexpr auto operator()(Fn&& fn, Arg&& arg, Args&&... args) const
    noexcept(trait::InvokeNoThrow_v
             <Fn, decltype(std::declval<Arg>().value()),
              decltype(std::declval<Args>().value())...>)
    -> Result<Fn, Arg, Args...> {
    return detail::all(bool(arg), bool(args)...)
      ? trait::detail::INVOKE(std::forward<Fn>(fn),
                              *std::forward<Arg>(arg),
                              *std::forward<Args>(args)...)
      : nullopt;
  }
};

template<typename... Args>
auto map(Args&&... args) noexcept(trait::InvokeNoThrow_v<map_fn, Args...>)
  -> trait::InvokeResult_t<map_fn, Args...> {
  return map_fn{}(std::forward<Args>(args)...);
}
