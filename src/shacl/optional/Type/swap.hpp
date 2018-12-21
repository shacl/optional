template<typename U = T,
         std::enable_if_t<trait::SwapDefined_v<U>, bool> = true>
void swap(Type& that)
  noexcept(std::is_nothrow_move_constructible<T>::value
           and trait::SwapNoThrow_v<T>) {
  if (this->has_value()) {
    if (that.has_value()) {
      using std::swap;
      swap(**this, *that);
    } else {
      new (std::addressof(that.data)) T{std::move(this->data)};
      this->resetData();
    }
  } else if (that.has_value()) {
    new (std::addressof(this->data)) T{std::move(that.data)};
    that.resetData();
  }
}
