#pragma once
#include "CombineHash.hpp"

namespace loki::common {

/// \ingroup UTILS_COMBINEHASH
/// \brief Helper functor for hashing pairs
/// \tparam Pair the type of the std::pair
template <class Pair>
struct PairHash {
    /// \brief Hash operator
    /// \param val The pair to hash
    /// \return A hash of the pair (order matters)
    size_t operator()(const Pair& val) const {
        return combineHash(val.first, val.second);
    }
};

template <typename S, typename T>
using MakePairHash = PairHash<std::pair<S, T>>;

/// \ingroup UTILS_COMBINEHASH
/// \brief Helper functor for hashing pairs symetrically
/// \note This functor only makes sense if the arguments of the pair can compare equal to one another...
/// \tparam Pair the type of the std::pair
template <class Pair>
struct PairHashSym {
    /// \brief Symmetric hash operator
    /// \param val The pair to hash symmetrically
    /// \return A symmetric hash of the pair (order doesn't matter)
    size_t operator()(const Pair& val) const {
        return combineHashSym(val.first, val.second);
    }
};

template <typename S, typename T = S>
using MakePairHashSym = PairHashSym<std::pair<S, T>>;

/// \ingroup UTILS_COMBINEHASH
/// \brief Helper functor for comparing pairs where order of arguments doesn't matter
/// \warning This functor only exists for pairs where the two arguments can compare equal to one another !
/// \tparam Pair1 the type of the first std::pair
/// \tparam Pair2 the type of the second std::pair
template <class Pair1, class Pair2>
struct PairAreEqualSym {
    /// \brief No-order comparison operator
    /// \param lhs The left-hand side pair to compare
    /// \param rhs The right-hand side pair to compare
    /// \return `true` if both pair represent the same (mathematical) set, `false` otherwise
    bool operator()(const Pair1& lhs, const Pair2& rhs) const {
        return (lhs.first == rhs.first && lhs.second == rhs.second)
               || (lhs.first == rhs.second && lhs.second == rhs.first);
    }
};

template <typename S, typename T = S, typename U = S, typename V = T>
using MakePairAreEqualSym = PairAreEqualSym<std::pair<S, T>, std::pair<U, V>>;

} // end namespace loki::common
