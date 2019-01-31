template<typename... Args>
auto emplace(Args&&... args)
  -> std::enable_if_t<std::is_constructible<T, Args...>::value, T&>{
  *this = nullopt;
  this->construct(std::forward<Args>(args)...);
  return **this;
}

template<typename U, typename... Args>
auto emplace(std::initializer_list<U> list, Args&&... args)
  -> std::enable_if_t
  <std::is_constructible
   <T, std::initializer_list<U>&, Args...>::value, T&> {
  *this = nullopt;
  this->construct(list, std::forward<Args>(args)...);
  return **this;
}
