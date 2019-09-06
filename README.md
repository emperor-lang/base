# Emperor Base Library

This is the Emperor base library, a minimal library to be included in all Emperor programs.

This differs from the standard library in that whereas most programs will rely on features of `std`, it is only functions which are present in this package, `base`, upon which the compiler may make assumptions.

This package provides:

- Lists
- Poison for C functions which pose a security threat
- Basic I/O functions on C strings
- A check to ensure that a favourable OS is being used to for compilation
- Macros to mark function parameters as unused
