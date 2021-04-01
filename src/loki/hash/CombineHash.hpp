#pragma once

#include <functional>
#include <type_traits>

namespace loki::hash {

constexpr std::size_t combineHashImpl(std::size_t seed) {
  return seed;
}

template <typename T, typename... Args>
std::size_t combineHashImpl(std::size_t seed, const T& val, const Args&... args) {
    return combineHashImpl(
      seed ^ std::hash<T>()(val) + 0x9E3779B97F4A7C15 + (seed << 6u) + (seed >> 2u),
      args...);
}

template <typename... Args>
std::size_t combineHash(const Args&... args) {
    return combineHashImpl(0ull, args...);
}
/*
/// \ingroup UTILS_COMBINEHASH
/// \brief Iinitializes the algorithm with the hash of the argument as seed
/// \tparam S The type of `val`
/// \param val The value to hash
/// \return A hash of `val`
template <typename T>
size_t combineHash(const T& val) {
    return std::hash<T>()(val);
}

/// \ingroup UTILS_COMBINEHASH
/// \brief Iinitializes the algorithm with the seed
///
/// Not __really__ necessary, but this way we don't hash seeds twice
/// \param seed The seed
/// \return the seed unchanged
size_t combineHash(std::size_t seed) {
    return seed;
}

/// \ingroup UTILS_COMBINEHASH
/// \brief Combines hash of `val` with `seed`
///
/// Not _really_ necessary, but this way we don't hash again the seed at each iteration
/// \tparam T The type of `val`
/// \param seed The seed of the hash
/// \param val The value to hash
/// \return A hash combination of `seed` and `val`
template <typename T>
size_t combineHash(size_t seed, const T& val) {
    return seed ^ std::hash<T>()(val) + 0x9E3779B97F4A7C15 + (seed << 6u) + (seed >> 2u);
}

/// \ingroup UTILS_COMBINEHASH
/// \brief Combines hashes of `val1` and `val2`
///
/// Iinitializes the algorithm with the hash of the first argument as seed
/// \tparam S The type of `val1`
/// \tparam T The type of `val2`
/// \param val1 The first value to hash
/// \param val2 The second value to hash
/// \return A hash combination of `val1` and `val2`
template <typename S, typename T>
size_t combineHash(const S& val1, const T& val2) {
    return combineHash(std::hash<S>()(val1), val2);
}

/// \ingroup UTILS_COMBINEHASH
/// \brief Combines hashes of all arguments
///
/// Combines the first two values, then recursively combines the result with the rest.
/// **Order is important !**
///
/// Internally, it will call the double-template form if no seed is provided,
/// then use the seeded form for the other iterations.
/// \tparam S The type of `val1`
/// \tparam T The type of `val2`
/// \tparam Args The type of `args`
/// \param val1 The first value to hash
/// \param val2 The second value to hash
/// \param args The other values to hash after `val1` and `val2`
/// \return A hash combination of `val1`, `val2` and `args`
template <typename S, typename T, typename... Args>
size_t combineHash(const S& val1, const T& val2, const Args& ... args) {
    return combineHash(combineHash(val1, val2), args...);
}
*/
/// \ingroup UTILS_COMBINEHASH
/// \brief Hashes all arguments and combines them symmetrically
///
/// In opposition to \ref combineHash, `combineHashSym` doesn't care about order between the arguments.
/// \tparam Args The type of `args`
/// \param args The values to hash
/// \return A hash combination of the arguments where order doesn't matter
template <typename... Args>
size_t combineHashSym(const Args& ... args) {
    return (std::hash<std::decay_t<decltype(args)>>()(args) + ...);
    /*
     * We use two advanced C++ techniques here :
     * + The first is std::decay_t<decltype(args)> which is used to determine the "true" type
     *   of the argument being treated (without const reference), so we can use the corresponding std::hash ;
     * + The second is a fold operation (xxx + ...), which is a way to apply the addition operator + to
     *   all hashes two-by-two.
     * This way we ensure the operation is symmetrical in regards to the arguments given.
     */
}

} // end namespace loki::hash

/**
 * \defgroup UTILS_COMBINEHASH Hash combination functions
 * \ingroup UTILS
 * \brief Hash combination helper functions
 *
 * Helper functions designed to be able to easily combine hashes.
 * You can simply hash a bunch of values together like so :
 * \code
 * int x = 42;
 * char y = 'B';
 * float z = 3.1415f;
 * std::complex<double> t = -1i;
 * size_t hash1 = combineHash(x, y, z, t);
 * size_t hash2 = combineHash(t, x, y, z);
 * size_t hashSym1 = combineHashSym(x, y, z, t);
 * size_t hashSym2 = combineHashSym(t, x, y, z);
 * \endcode
 *
 * \note For the normal version, **order is important :** `hash1` will most likely differ from `hash2`.
 * If you need to hash values so that order doesn't matter, use combineHashSym() (%zwj;l`hashSym1 == hashSym2` here).
 *
 * This header also defines functors for hashing `std::pair` and `std::tuple`,
 * so you can easiy use them as keys in `std::unordered_map` for example.
 */
