class bad_access : public std::exception {
public:
  bad_access() = default;
  const char* what() const noexcept {
    return "Attempt to access value of a disengaged optional object";
  }
};
