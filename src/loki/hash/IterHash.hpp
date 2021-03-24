#pragma once
#include "CombineHash.hpp"

namespace loki::hash {

/// \ingroup UTILS_COMBINEHASH
/// \brief Hash specialization for Iterable types (like std::vector)
/// \tparam Iterable the type of the iterable
template <class Iterable>
struct IterHash {
    /// \brief Hash operator
    /// \param iterable The Iterable to hash
    /// \return A hash of the Iterable (order matters)
    size_t operator()(const Iterable& iterable) const {
        size_t seed = iterable.size();
        for (const auto& elem : iterable) {
            seed = loki::common::combineHash(seed, elem);
        }
        return seed;
    }
};

template <typename T>
using VectorHash = IterHash<std::vector<T>>;

}
