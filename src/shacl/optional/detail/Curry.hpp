namespace detail {

template<typename Fn, typename Host, template<typename...> typename Result >
class Curry : ebo::Type<Fn> {
  using Parent = ebo::Type<Fn>;

public:
  using ebo::Type<Fn>::Type;

  template<typename... Args>
  constexpr auto operator()(Args&&... args) &
    noexcept(trait::InvokeNoThrow_v<Host, Fn&, Args...>)
    -> Result<Fn&, Args...> {
    return Host{}(Parent::get(ebo::index<0>), std::forward<Args>(args)...);
  }

  template<typename... Args>
  constexpr auto operator()(Args&&... args) const &
    noexcept(trait::InvokeNoThrow_v<Host, const Fn&, Args...>)
    -> Result<const Fn&, Args...> {
    return Host{}(Parent::get(ebo::index<0>), std::forward<Args>(args)...);
  }

  template<typename... Args>
  auto operator()(Args&&... args) &&
    noexcept(trait::InvokeNoThrow_v<Host, Fn&&, Args...>)
    -> Result<Fn&&, Args...> {
    return Host{}(std::move(Parent::get(ebo::index<0>)),
                  std::forward<Args>(args)...);
  }

  template<typename... Args>
  auto operator()(Args&&... args) const &&
    noexcept(trait::InvokeNoThrow_v<Host, const Fn&&, Args...>)
    -> Result<const Fn&&, Args...> {
    return Host{}(std::move(Parent::get(ebo::index<0>)),
                  std::forward<Args>(args)...);
  }
};

}