### optional::map ###

`shacl::optional::map`, a function template providing a functor interface (in
the category theory sense) to `shacl::Optional`.

----------------------------

#### Example:

Consider how we might apply a function to the value held by an optional. Of
course an optional very well may be empty. In that sense, the function may not
be applicable. This circumstance is captured nicely by returning an optional
representing the result of calling to the function on the stored value, if it
existed, or `shacl::optional::nullopt` otherwise. This might be implemented
using the standard library interface as follows:

```cpp
#include "shacl/optional.hpp"

#include <iostream>
#include <string>

int main(){
  shacl::Optional<int> oi = 10;

  shacl::Optional<std::string> os =
    oi ? shacl::optional::make(std::to_string(*oi))
       : shacl::optional::nullopt;

  std::cout << os.value() << std::endl;
}
```

The output of this program is:

```
10
```

This pattern of occurs frequently, with the `Optional` class template and more
generally. The sequence of operations goes something like this:

+ unwrap a value from 'container'
+ apply a transformation
+ wrap the result of the transformation in a 'container'

This sequence of operations is known as a functor mapping. The `optional`
namespace defines a higher-order function called `map`, which given a callable
object representing a transformation, applies functor mapping to one or more
`shacl::Optional` instantiation object. Let's consider how the program we wrote
previously could be rewritten in terms of `optional::map`.

```cpp
#include "shacl/optional.hpp"

#include <iostream>
#include <string>

struct to_string_fn {
  template<typename T>
  std::string operator()(T t) const { return std::to_string(t); }
};

constexpr const to_string_fn to_string{};

int main(){
  shacl::Optional<int> oi = 10;

  shacl::Optional<std::string> os = shacl::optional::map(to_string, oi);
  // or more concisely:
  // auto os = shacl::optional::map(to_string, oi);

  std::cout << os.value() << std::endl;
}
```

For more information regarding this functor pattern, please see the *Related
Material* at the end of this README.

-----------------------

Just as `shacl::optional::map` supports a form of partial evaluation which
effectively 'lifts' an argument callable to produce a new callable applying
functor mapping.

-----------------------

#### Example:

The unary `map` overload, which 'lifts' a callable to apply functor mapping,
is convenient when working with collections of optional instances.

```cpp
#include "shacl/optional.hpp"

#include <iostream>
#include <iterator>
#include <transform>
#include <vector>

struct to_string {
  template<typename T>
  std::string operator()(T t) const { return std::to_string(t); }
};

int main(){
  std::vector<shacl::Optional<int>> voi;

  voi.emplace_back(1);
  voi.emplace_back(2);
  voi.emplace_back(shacl::optional::nullopt);
  voi.emplace_back(4);

  std::vector<shacl::Optional<std::string>> vos;

  auto lift = shacl::optional::map(to_string);
  // lift is instance of a new class which inspects and transforms an argument
  // optional. If the optional holds a value, the value is forwarded to
  // `to_string::operator()` and the result is wrapped in an optional.
  // If the argument optional is empty, an empty optional is returned.

  std::transform(voi.begin(), voi.end(), std::back_inserter(vos), lift);

  for(const auto& o : vos){
     if (o){
       std::cout << *o << std::endl;
     } else {
       std::cout << "empty!" << std::endl;
     }
  });
}
```

The output of this program is:

```
1
2
empty!
4
```

------------------------------

#### Example:

The callable returned by the unary `map` overload is also 'pipeable', providing
a convenient syntax for chaining operations returning optional values.

```cpp
#include "shacl/optional.hpp"

#include <cassert>
#include <iostream>
#include <string>

struct safe_sqrt_fn {
  std::optional<int> operator()(float f) const {
    return f >= 0 ? shacl::optional::make(std::sqrt(f))
                  : shacl::optional::nullopt;
  }
};

constexpr const safe_sqrt_fn safe_sqrt{};

struct floor_fn {
  int operator()(float f) const {
    return std::floor(f);
  }
};

constexpr const floor_fn floor{};

struct to_string_fn {
  template<typename T>
  std::string operator()(T t) const { return std::to_string(t); }
};

constexpr const to_string_fn to_string{};

int main(){
  shacl::Optional<std::string> safe_string =
    safe_sqrt(38.0f)
    | shacl::optional::map(floor)
    | shacl::optional::map(to_string);

  assert(safe_string.has_value())
  std::cout << safe_string.value() << std::endl;

  shacl::Optional<std::string> unsafe_string =
    safe_sqrt(-10.0f)
    | shacl::optional::map(floor)
    | shacl::optional::map(to_string);

  assert(not unsafe_string.has_value())
  std::cout << "no value!" << std::endl;
}
```

The output of this program is:

```
6
no value!
```

### Related Material

+ [Using Types Effectively](https://www.youtube.com/watch?v=ojZbFIQSdl8)
+ [The (Functional) Functor Pattern in C++](https://www.fpcomplete.com/blog/2012/07/the-functor-pattern-in-c)
