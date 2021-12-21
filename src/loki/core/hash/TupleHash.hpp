#pragma once
#include "CombineHash.hpp"

namespace loki::hash {

/// \ingroup UTILS_COMBINEHASH
/// \brief Helper functor for hashing tuples
/// \tparam Tuple the type of the std::tuple
template <class Tuple>
struct TupleHash {
  /// \brief Hash operator
  /// \param val The tuple to hash
  /// \return A hash of the tuple (order matters)
  size_t operator()(const Tuple& val) const {
    return std::apply(
        [](auto&&... args) {
          return combineHash(std::forward<decltype(args)>(args)...);
        },
        val);
    // std::apply allows us to use combineHash with all values stored in the
    // tuple at once
  }
};

template <class... Args>
using MakeTupleHash = TupleHash<std::tuple<Args...>>;

/// \ingroup UTILS_COMBINEHASH
/// \brief Helper functor for hashing tuples symetrically
/// \note This functor only makes sense if all arguments of the tuple can
/// compare equal to one another... \tparam Tuple the type of the std::tuple
template <class Tuple>
struct TupleHashSym {
  /// \brief Symmetric hash operator
  /// \param val The tuple to hash symmetrically
  /// \return A symmetric tuple of the pair (order doesn't matter)
  size_t operator()(const Tuple& val) const {
    // return std::apply(combineHashSym, val);
    return std::apply(
        [](auto&&... args) {
          combineHash(std::forward<decltype(args)>(args)...);
        },
        val);
    // std::apply allows us to use combineHashSym with all values stored in the
    // tuple at once
  }
};

template <class... Args>
using MakeTupleHashSym = TupleHashSym<std::tuple<Args...>>;

/// \todo TupleAreEqualSym
/// Algorithm :
/// \code
/// {x0, ..., xN} == {y0, ..., yN} <=>
///    (x0 == y0 && {x1, ..., xN} == {y1, ..., yN})
/// || (x0 == y1 && {x1, ..., xN} == {y0, y2, ..., yN})
/// || ...
/// || (x0 == yN && {x1, ..., xN} == {y0, ..., yN-1})
/// \endcode

}  // namespace loki::hash
