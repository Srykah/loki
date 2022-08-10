/*!
 * \file TemplateHelpers.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki {
inline namespace utils {

struct true_type {
  static constexpr bool value = true;
};

struct false_type {
  static constexpr bool value = false;
};

template <class... T>
constexpr bool always_false = false;

template <typename T>
struct identity_type {
  using type = T;
};

struct nonesuch {
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

#include "impl/is_detected.hxx"

template <template <class...> class Op, class... Args>
constexpr bool is_detected = impl::detector<void, Op, Args...>::value;

template <template <class...> class Op, class... Args>
using detected_t = typename impl::detector<void, Op, Args...>::type;

template <template <class...> class Op, class... Args>
constexpr bool is_detected_as_true =
    std::conjunction_v<impl::detector<void, Op, Args...>,
                       detected_t<Op, Args...> >;

}  // namespace utils
}  // namespace loki
