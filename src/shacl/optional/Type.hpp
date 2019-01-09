template<typename T>
class Type : detail::MoveAssign<T>, detail::Enabled<T> {
  static_assert(not std::is_same<T, in_place_t>::value,
                "Parameterization of shacl::Optional on"
                " shacl::optional::in_place_t is ill-formed");

  static_assert(not std::is_same<T, nullopt_t>::value,
                "Parameterization of shacl::Optional on"
                " shacl::optional::nullopt_t is ill-formed");

  using Implementation = detail::MoveAssign<T>;

  template<typename U>
  friend struct detail::Operations;

public:
  using value_type = T;

  #include "shacl/optional/Type/ctor.hpp"
  #include "shacl/optional/Type/assignment.hpp"
  #include "shacl/optional/Type/swap.hpp"
  #include "shacl/optional/Type/emplace.hpp"
  #include "shacl/optional/Type/value.hpp"
  #include "shacl/optional/Type/value_or.hpp"
  #include "shacl/optional/Type/comparison.hpp"

  ~Type() = default;

  constexpr T* operator->() { return std::addressof(this->data); }
  constexpr const T* operator->() const { return std::addressof(this->data); }

  constexpr T& operator*() & { return this->data; }
  constexpr const T& operator*() const& { return this->data; }
  constexpr T&& operator*() && { return std::move(this->data); }
  constexpr const T&& operator*() const&& { return std::move(this->data); }

  constexpr bool has_value() const noexcept { return this->engaged; }
  constexpr explicit operator bool() const noexcept { return this->engaged; }
  void reset() noexcept { if (this->has_value()) { this->resetData(); } }

  template<typename U = Type,
           typename = shacl::trait::void_t
           <decltype(std::declval<U&>().swap(std::declval<U&>()))>>
  friend void swap(Type& left, Type& right)
    noexcept(noexcept(std::declval<U&>().swap(std::declval<U&>()))){
    left.swap(right);
  }
};
