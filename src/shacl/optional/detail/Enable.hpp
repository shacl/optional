template <class T, bool = ::std::is_copy_constructible<T>::value>
struct DeleteCopy<T> : MoveAssign<T> {
};

template <class T>
struct DeleteCopy<T, true> : MoveAssign<T> {
  DeleteCopy(DeleteCopy&)
};
