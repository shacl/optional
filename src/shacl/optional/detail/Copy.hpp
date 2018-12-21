template <class T, bool = ::std::is_trivially_copyable<T>::value>
struct Copy : Operations<T> {
  using Operations<T>::Operations;
};

template <class T>
struct Copy<T, false> : Operations<T> {
  using Operations<T>::Operations;

  Copy() = default;

  constexpr Copy(const Copy& that)
  noexcept(std::is_nothrow_constructible<T>::value) {
    if (that.has_value()) {
      this->construct(that.get());
    } else {
      this->engaged = false;
    }
  }

  Copy(Copy&&) = default;
  Copy& operator=(const Copy&) = default;
  Copy& operator=(Copy&&) = default;
};
