template <class T,
          bool = (::std::is_trivially_copy_constructible<T>::value
                  and ::std::is_trivially_copy_assignable<T>::value
                  and ::std::is_trivially_destructible<T>::value)>
struct CopyAssign : Move<T> {
  using Move<T>::Move;
};

template <class T>
struct CopyAssign<T, false> : Move<T> {
  using Move<T>::Move;

  CopyAssign() = default;

  CopyAssign(const CopyAssign&) = default;
  CopyAssign(CopyAssign&&) = default;

  CopyAssign& operator=(const CopyAssign& that){
    this->assign(that);
    return *this;
  }
  CopyAssign& operator=(CopyAssign&&) = default;
};
