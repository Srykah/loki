/*!
 * \file Interpolate.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

namespace loki::common {

// helper types
template <class Iter>
using FirstPointedType =
    typename std::iterator_traits<Iter>::value_type::first_type;

template <class Iter>
using SecondPointedType =
    typename std::iterator_traits<Iter>::value_type::second_type;

template <class Container>
using FirstContainedType = FirstPointedType<decltype(std::begin(
    std::declval<std::decay<Container>>()))>;

template <class Container>
using SecondContainedType = SecondPointedType<decltype(std::begin(
    std::declval<std::decay<Container>>()))>;

// NoneInterpolation

// additional deduction guides
template <class Iter>
NoneInterpolation(Iter, Iter)
    -> NoneInterpolation<FirstPointedType<Iter>, SecondPointedType<Iter>>;

template <class Container>
NoneInterpolation(Container)
    -> NoneInterpolation<FirstContainedType<Container>,
                         SecondContainedType<Container>>;

template <typename In, typename Out>
Out NoneInterpolation<In, Out>::interpolate(const In& x) const {
  auto it = std::find_if(points.rbegin(), points.rend(),
                         [&x](const auto& p) { return p.first <= x; });
  if (it == points.rend()) {
    return Out{};
  }
  return it->second;
}

// LinearInterpolation

// additional deduction guides
template <class Iter>
LinearInterpolation(Iter, Iter)
    -> LinearInterpolation<FirstPointedType<Iter>, SecondPointedType<Iter>>;

template <class Container>
LinearInterpolation(Container)
    -> LinearInterpolation<FirstContainedType<Container>,
                           SecondContainedType<Container>>;

template <typename In, typename Out>
Out LinearInterpolation<In, Out>::interpolate(const In& x) const {
  auto it = std::find_if(points.begin(), points.end(),
                         [&x](const auto& p) { return p.first > x; });
  if (it == points.end() || it == points.begin()) {
    return Out{};
  }
  auto prev = it - 1;
  auto x1 = prev->first;
  auto x2 = it->first;
  auto y1 = prev->second;
  auto y2 = it->second;
  return (y2 - y1) * (x - x1) / (x2 - x1) + y1;
}

}  // namespace loki::common
