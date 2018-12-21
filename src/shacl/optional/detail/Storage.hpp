struct Empty {};

template <class T, bool = ::std::is_trivially_destructible<T>::value>
struct Storage {
  constexpr Storage() noexcept : empty(), engaged(false) {}

  template <typename... Args,
            std::enable_if_t
            <std::is_constructible<T, Args...>::value, bool> = true>
  constexpr Storage(in_place_t, Args&&... args)
    noexcept(std::is_nothrow_constructible<T, Args...>::value) :
    data(std::forward<Args>(args)...), engaged(true) {}

  ~Storage() {
    if (this->engaged) {
      this->data.~T();
      this->engaged = false;
    }
  }

  union {
    Empty empty;
    T data;
  };

  bool engaged;
};

template <class T>
struct Storage<T, true> {
  constexpr Storage() noexcept : empty(), engaged(false) {}

  template <typename... Args,
            std::enable_if_t
            <std::is_constructible<T, Args...>::value, bool> = true>
  constexpr Storage(in_place_t, Args&&... args)
    noexcept(std::is_nothrow_constructible<T, Args...>::value) :
    data(std::forward<Args>(args)...), engaged(true) {}

  union {
    Empty empty;
    T data;
  };

  bool engaged = false;
};
