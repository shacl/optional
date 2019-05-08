template <class T, bool = ::std::is_trivially_move_constructible<T>::value>
struct Move : Copy<T> {
  using Copy<T>::Copy;
};

template <class T>
struct Move<T, false> : Copy<T> {
  using Copy<T>::Copy;

  Move() = default;

  Move(const Move&) = default;
  constexpr Move(Move&& that)
  noexcept(std::is_nothrow_move_constructible<T>::value) {
    if (that.has_value()) {
      this->construct(std::move(that).get());
    } else {
      this->engaged = false;
    }
  }

  Move& operator=(const Move&) = default;
  Move& operator=(Move&&) = default;
};
