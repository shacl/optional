constexpr Type() noexcept = default;
constexpr Type(nullopt_t) noexcept {}

constexpr Type(Type&&) = default;
constexpr Type(const Type&) = default;

template<class... Args>
constexpr explicit Type
(std::enable_if_t
 <std::is_constructible<T, Args...>::value, in_place_t>, Args&&... args) :
  Implementation(in_place, std::forward<Args>(args)...) {}

template<class U, class... Args>
constexpr explicit Type
(std::enable_if_t
 <std::is_constructible
 <T, std::initializer_list<U>&, Args...>::value, in_place_t>,
 std::initializer_list<U> list, Args&&... args) :
  Implementation(in_place, list, std::forward<Args>(args)...) {}

template<typename Arg,
         std::enable_if_t
         <std::is_convertible<Arg&&, T>::value, bool> = true,
         detail::enable_forward_value<T, Arg> = true>
constexpr Type(Arg&& arg) : Implementation(in_place, std::forward<Arg>(arg)) {}

template<typename Arg,
         std::enable_if_t
         <not std::is_convertible<Arg&&, T>::value, bool> = true,
         detail::enable_forward_value<T, Arg> = true>
constexpr explicit Type(Arg&& arg) :
  Implementation(in_place, std::forward<Arg>(arg)) {}

template<typename U,
         std::enable_if_t
         <std::is_convertible<U&&, T>::value, bool> = true,
         detail::enable_from_other<T, U, U&&> = true>
constexpr Type(Type<U>&& arg) { this->construct(std::move(arg)); }

template<typename U,
         std::enable_if_t
         <not std::is_convertible<U&&, T>::value, bool> = true,
         detail::enable_from_other<T, U, U&&> = true>
constexpr explicit Type(Type<U>&& arg) { this->construct(std::move(arg)); }

template<typename U,
         std::enable_if_t
         <std::is_convertible<const U&, T>::value, bool> = true,
         detail::enable_from_other<T, U, const U&> = true>
constexpr Type(const Type<U>& arg) { this->construct(std::move(arg)); }

template<typename U,
         std::enable_if_t
         <not std::is_convertible<const U&, T>::value, bool> = true,
         detail::enable_from_other<T, U, const U&> = true>
constexpr explicit Type(Type<U>& arg) { this->construct(std::move(arg)); }
