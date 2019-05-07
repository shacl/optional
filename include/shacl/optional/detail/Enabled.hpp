template <class T,
          bool = ::std::is_move_constructible<T>::value,
          bool = ::std::is_copy_constructible<T>::value,
          bool = ::std::is_move_assignable<T>::value,
          bool = ::std::is_copy_assignable<T>::value>
struct Enabled;

template <class T>
struct Enabled<T, true, true, true, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, true, true, true, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = delete;
};

template <class T>
struct Enabled<T, true, true, false, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, true, true, false, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = delete;
};

template <class T>
struct Enabled<T, true, false, true, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, true, false, true, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = delete;
};

template <class T>
struct Enabled<T, true, false, false, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, true, false, false, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = default;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = delete;
};

template <class T>
struct Enabled<T, false, true, true, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, false, true, true, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = delete;
};

template <class T>
struct Enabled<T, false, true, false, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, false, true, false, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = default;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = delete;
};

template <class T>
struct Enabled<T, false, false, true, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, false, false, true, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = default;
  Enabled& operator=(const Enabled&) = delete;
};

template <class T>
struct Enabled<T, false, false, false, true> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = default;
};

template <class T>
struct Enabled<T, false, false, false, false> {
  Enabled() = default;
  Enabled(Enabled&&) noexcept = delete;
  Enabled(const Enabled&) = delete;
  Enabled& operator=(Enabled&&) noexcept = delete;
  Enabled& operator=(const Enabled&) = delete;
};

