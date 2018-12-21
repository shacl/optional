template <class T,
          bool = (::std::is_trivially_move_constructible<T>::value
                  and ::std::is_trivially_move_assignable<T>::value
                  and ::std::is_trivially_destructible<T>::value)>
struct MoveAssign : CopyAssign<T> {
  using CopyAssign<T>::CopyAssign;
};

template <class T>
struct MoveAssign<T, false> : CopyAssign<T> {
  using CopyAssign<T>::CopyAssign;

  MoveAssign() = default;

  MoveAssign(const MoveAssign&) = default;
  MoveAssign(MoveAssign&&) = default;

  MoveAssign& operator=(const MoveAssign&) = default;
  MoveAssign& operator=(MoveAssign&& that)
    noexcept(std::is_nothrow_move_assignable<T>::value
             and std::is_nothrow_move_constructible<T>::value) {
    this->assign(std::move(that));
    return *this;
  }
};
