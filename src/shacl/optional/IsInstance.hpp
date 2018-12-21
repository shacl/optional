template<typename T>
struct IsInstance : std::false_type {};

template<typename T>
struct IsInstance<Type<T>> : std::true_type {};

template<typename T>
static constexpr bool IsInstance_v = IsInstance<T>::value;
