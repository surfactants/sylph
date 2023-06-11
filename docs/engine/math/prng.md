# prng
*header*
*engine/math/prng.hpp*

Pseudo-random number generator. All functions are provided within the namespace **prng**.

- T **number( *const T floor, const T ceil* ):** generates a random number between floor and ceil; integral or floating point.
- T **boolean( *float chance* ):** generates a random bool. *chance* is an optional parameter between 0-1; a parameterless overload is provided which uses 50%.
- T **iterator( *container* ):** TODO. generates a random iterator to the passed container.
- std::mt19937& **engine():** provides internal access to a static Mersenne-Twister engine