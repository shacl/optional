constexpr T& value() & {
  if (unlikely(not this->has_value())){ throw bad_access{}; }
  return this->data;
}

constexpr const T& value() const& {
  if (unlikely(not this->has_value())){ throw bad_access{}; }
  return this->data;
}

constexpr T&& value() && {
  if (unlikely(not this->has_value())){ throw bad_access{}; }
  return std::move(this->data);
}

constexpr const T&& value() const&& {
  if (unlikely(not this->has_value())){ throw bad_access{}; }
  return std::move(this->data);
}
