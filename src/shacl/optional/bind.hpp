class bind_fn {
  template<typename Fn, typename... Args>
  using Result =
    trait::InvokeResult_t<Fn, decltype(std::declval<Args>.value())...>;

  template<typename Fn>
  using Curry = detail::Curry<Fn, bind_fn, Result>;

public:
  template<typename Fn>
  constexpr auto operator()(Fn&& fn) const {
    return Curry<std::decay_t<Fn>>{std::forward<Fn>(fn)};
  }

  template<typename Fn, typename Arg, typename... Args,
           typename Result_t = Result<Fn, Arg, Args...>,
           std::enable_if_t
           <detail::all
            (IsInstance_v<Result_t>,
             IsInstance_v<std::decay_t<Arg>>,
             IsInstance_v<std::decay_t<Args>>...), bool> = true>
  constexpr auto operator()(Fn&& fn, Arg&& arg, Args&&... args) const
    noexcept(trait::InvokeNoThrow_v
             <Fn, decltype(std::declval<Arg>().value()),
              decltype(std::declval<Args>().value())...>)
    -> Result_t {
    return detail::all(bool(arg), bool(args)...)
      ? trait::detail::INVOKE(std::forward<Fn>(fn),
                              *std::forward<Arg>(arg),
                              *std::forward<Args>(args)...)
      : nullopt;
  }
};

template<typename... Args>
auto bind(Args&&... args) noexcept(trait::InvokeNoThrow_v<bind_fn, Args...>)
  -> trait::InvokeResult_t<bind_fn, Args...> {
  return bind_fn{}(std::forward<Args>(args)...);
}
