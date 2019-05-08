inline constexpr bool all(){ return true; }

template<typename... Bool>
constexpr bool all(bool head, Bool... tail){
  return head && all(tail...);
}
