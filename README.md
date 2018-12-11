shacl optional
==================

In the C++17 standard, a templated class called
[`std::optional`](https://en.cppreference.com/w/cpp/utility/optional) was
introduced to the standard library, which (effectively) adds a null state
to a parameter class. This class is often useful when implementing
multi-phase initialization.

This library provides:

+ additional and extended infrastructure for working with `std::optional`
+ a backport of `std::optional` when compiling with the C++14 standard
+ a unified interface to the C++17 `std::optional` and C++14 backport.

shacl::Optional Class Template and shacl::optional Namespace
------------------------------------------------------------------

At the center of this library is the `shacl::Optional` type alias template and
the `shacl::optional` namespace. When compiling against the C++17 standard, the
alias template refers to the `std::optional` class template. When compiling with
the C++14 standard, the standard library optional implementation is
unavailable. Rather than require C++17, this library rebases on a optional
implementation for C++14 shipped with the library. The `shacl::Optional` alias
and `shacl::optional` namespace shield library consumers from this dispatching
based on the C++ standard.

Standard Capabilities
------------------------

The standard library provides a number of facilities for working with option
types. These features are included in the `shacl::optional` namespace, albeit
under slightly different names in some cases.

+ `std::optional` => `shacl::Optional`
+ `std::bad_optional_access` => `shacl::optional::bad_access`
+ `std::in_place` => `shacl::optional::in_place`
+ `std::in_place_t` => `shacl::optional::in_place_t`
+ `std::nullopt` => `shacl::optional::nullopt`
+ `std::nullopt_t` => `shacl::optional::nullopt_t`

Note that the `in_place_t` class of the `shacl::optional` namespace is **NOT**
distinct from the `in_place_t` of the `shacl::variant` namespace in either
the C++17 or C++14 configurations.

Extended Capabilities
------------------------

In addition to the standard library facilities, this library provides a small
amount of additional functionality.

+ [shacl::optional::map](src/shacl/optional/map/README.md)
+ [shacl::optional::bind](src/shacl/optional/bind/README.md)

Build System
--------------

As a header-only library, `shacl::optional` has no compiled components.
Nevertheless, a [CMake](https://cmake.org/overview/) build system is provided to
allow easy testing, installation, and subproject composition on many platforms
and operating systems. CMake version 3.8 or later is required to configure and
build this library.

#### Compiler Support

The shacl::optional library is written in C++14, and makes considerable use of
generalized constant expressions and SFINAE. As such, a relatively robust C++
compiler supporting the C++14 standard is required. The following compilers are
explicitly supported.

+ GNU g++ version 6.0.0 or later
+ LLVM clang++ version 3.5 or later
+ Xcode version 6.3/Apple clang++ version 9.0.0 or later
+ Visual Studio 2017 Update 8 (version 15.8) or later

While the Intel documentation specifies the Intel C++ compiler `icpc` version 17
or later is conformant with the C++ 11 and 14 standards, even the latest version
available as of the time of writing (verion 18 update 4), fails to support
numerous C++11 features and has generally **very** poor support for the SFINAE.

The current IBM XLC++ compiler (16.1.1) supports only a subset of the C++ 14
standard. Of note, generalized constant expressions are currently unsupported.

#### Dependencies

The shacl::variant library is dependent on several other libraries.
Given an internet connection, by default, these libraries will be downloaded
(without any need for user intervention) during the CMake configuration step. If
this behavior is undesirable, users can opt to consume a local installation of
these libraries by setting the `git.submodule.packages` CMake option to `OFF`.
Non-standard installation roots to these packages can be specified using the
`CMAKE_PREFIX_PATH` environment variable or CMake option. See the CMake
[`find_package`](https://cmake.org/cmake/help/v3.0/command/find_package.html)
documentation for more information.

shacl::optional depends on two other shared component libraries (shacl)
libraries:

+ empty base optimization (ebo)
+ compile time type traits (trait)

When compiling in C++14 mode, the shacl::optional library is dependent on
Micheal Park's variant library, which provides an implementation of
`std::in_place_t`. This dependency ensures the `in_place_t` class provided by
shacl::optional and shacl::variant are consisent in the C++14 configuration,
as they are (as provided by the C++ standard library) in the C++17
configuration.

Beyond the requirements of the library itself, the tests depend on the Catch2
unit testing library.

#### Testing
The shacl::optional library is distributed with a small suite of tests.
When shacl::optional is configured as the highest level CMake project, this
suite of executables is built by default. These test executables are integrated
with the CMake test driver program,
[CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html).

CMake supports a number of backends for compilation and linking.

To use a static configuration build tool, such as GNU Make or Ninja:

```sh
cd <shacl::optional source directory>
mkdir build
cd build

# Configure the build
cmake -D CMAKE_BUILD_TYPE=<Debug | Release> \
      -G <"Unix Makefiles" | "Ninja"> ..

# build the tests
< make | ninja | cmake --build . >

# run the tests
< make test | ninja test | cmake --build . --target test | ctest >
```

To use a dynamic configuration build tool, such as Visual Studio or Xcode:

```sh
cd <shacl::optional source directory>
mkdir build
cd build

# Configure the build
cmake -G <"Visual Studio 14 2015 Win64" | "Xcode"> ..

# build the tests
cmake --build . --config <Debug | Release>

# run the tests via ctest...
ctest --build-config <Debug | Release>

# ... or via CMake build tool mode...
cmake --build . --config <Debug | Release> --target test
```

Of course the **build** and **test** steps can also be executed via the **all**
and **test** targets, respectively, from within the IDE after opening the
project file generated during the configuration step.

This testing is also configured to operate as a client to the
[CDash](https://www.cdash.org/) software quality dashboard application. Please
see the [Kitware documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)
for more information on this mode of operation.

#### Installation

The shacl::optional library build system provides an installation target and
support for downstream consumption via CMake's
[`find_package`](https://cmake.org/cmake/help/v3.0/command/find_package.html)
intrinsic function. CMake allows installation to an arbitrary location, which
may be specified by defining `CMAKE_INSTALL_PREFIX` at configure time.
In the absense of a user specification, CMake will install shacl::optional to
conventional location based on the platform operating system.

To use a static configuration build tool, such as GNU Make or Ninja:

```sh
cd <shacl::optional source directory>
mkdir build
cd build

# Configure the build
cmake [-D CMAKE_INSTALL_PREFIX="path/to/installation"] \
      [-D BUILD_TESTING=False]                         \
      [-D BOOST_ROOT="path/to/boost/installation"]     \
      -D CMAKE_BUILD_TYPE=Release                      \
      -G <"Unix Makefiles" | "Ninja"> ..

# install shacl::optional
<make install | ninja install | cmake --build . --target install>
```

To use a dynamic configuration build tool, such as Visual Studio or Xcode:

```sh
cd <shacl::optional source directory>
mkdir build
cd build

# Configure the project
cmake [-D CMAKE_INSTALL_PREFIX="path/to/installation"] \
      [-D BUILD_TESTING=False]                         \
      [-D BOOST_ROOT="path/to/boost/installation"]     \
      -G <"Visual Studio 14 2015 Win64" | "Xcode"> ..

# install shacl::optional
cmake --build . --config Release --target install
```

Note that the last command of the installation sequence may require administrator privileges (e.g. `sudo`) if the installation root directory lies outside your home directory.

This installation
+ copies the shacl::optional header files to the `include/shacl` subdirectory of the installation root
+ generates and copies several CMake configuration files to the `share/cmake/shacl/optional` subdirectory of the installation root

This latter step allows downstream CMake projects to consume shacl::optional via `find_package`, e.g.

```cmake
find_package( shacl REQUIRED COMPONENTS optional )
target_link_libraries( MyTarget PUBLIC shacl::optional )
```

If `shacl::optional` was installed to a non-conventional location, it may be necessary for downstream projects to specify the shacl installation root directory via either

+ the `CMAKE_PREFIX_PATH` configuration option,
+ the `CMAKE_PREFIX_PATH` environment variable, or
+ `shacl_DIR` environment variable.

Please see the [Kitware documentation](https://cmake.org/cmake/help/v3.0/command/find_package.html) for more information.

In addition, shacl::optional supports packaged relocatable installations via [CPack](https://cmake.org/cmake/help/latest/manual/cpack.1.html).
Following configuration, from the build directory, invoke cpack as follows to generate a packaged installation:

```sh
cpack -G <generator name> -C Release
```

The list of supported generators varies from platform to platform. See the output of `cpack --help` for a complete list of supported generators on your platform.

### Related Material

+ [Using Types Effectively](https://www.youtube.com/watch?v=ojZbFIQSdl8)
+ [The (Functional) Functor Pattern in C++](https://www.fpcomplete.com/blog/2012/07/the-functor-pattern-in-c)
