template <class T>
struct Operations : Storage<T> {
  constexpr T& get() & noexcept { return this->data; }
  constexpr const T& get() const& noexcept { return this->data; }
  constexpr T&& get() && noexcept { return std::move(this->data); }
  constexpr const T&& get() const&& noexcept { return std::move(this->data); }

  constexpr void resetData() noexcept {
    this->data.~T();
    this->engaged = false;
  }

  template <typename... Args,
            std::enable_if_t
            <std::is_constructible<T, Args...>::value, bool> = true>
  constexpr void construct(Args &&... args)
    noexcept(std::is_nothrow_constructible<T, Args...>::value) {
    new (std::addressof(this->data)) T(std::forward<Args>(args)...);
    this->engaged = true;
  }

  template <typename Optional,
            typename Data = decltype(std::declval<Optional>().value()),
            std::enable_if_t
            <std::is_assignable<T, Data>::value
             and std::is_constructible<T, Data>::value, bool> = true>
  constexpr void assign(Optional&& that)
    noexcept(std::is_nothrow_assignable<T, Data>::value
             and std::is_nothrow_constructible<T, Data>::value) {
    if (this->has_value()) {
      if (that.has_value()) {
        this->data = std::forward<Optional>(that).get();
      } else {
        this->resetData();
      }
    } else if (that.has_value()) {
      this->construct(std::forward<Optional>(that).get());
    }
  }

  using Storage<T>::Storage;

  constexpr bool has_value() const noexcept { return this->engaged; }
};
