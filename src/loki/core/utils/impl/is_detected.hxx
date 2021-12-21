/*!
 * \file is_detected.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

namespace impl {

template <class, template <class...> class, class...>
struct detector : public false_type, public identity_type<nonesuch> {};

template <template <class...> class Op, class... Args>
struct detector<std::void_t<Op<Args...>>, Op, Args...>
    : public true_type, public identity_type<Op<Args...>> {};

}  // namespace impl
