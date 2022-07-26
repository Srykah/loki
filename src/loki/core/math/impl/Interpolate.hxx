/*!
 * \file Interpolate.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include <loki/core/utils/IterAdapters.hpp>
#include <loki/core/utils/TemplateHelpers.hpp>

namespace loki::math {

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
  if (points.empty()) {
    return Out{};
  }
  auto it = std::find_if(points.rbegin(), points.rend(),
                         [&x](const auto& p) { return p.first <= x; });
  if (it == points.rend()) {
    return points[0].second;
  }
  return it->second;
}

template <typename In, typename Out>
void from_json(const nlohmann::json& j, NoneInterpolation<In, Out>& ip) {
  ip.points.resize(j.size());
  for (auto&& [datum, point] : zip(j, ip.points)) {
    datum.at("t").get_to(point.first);
    datum.at("p").get_to(point.second);
  }
}

template <typename In, typename Out>
void to_json(nlohmann::json& j, const NoneInterpolation<In, Out>& ip) {
  j = nlohmann::json{ip.size()};
  for (auto&& [point, datum] : zip(ip.points, j)) {
    datum["t"] = point.first;
    datum["p"] = point.second;
  }
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
  if (points.empty()) {
    return Out{};
  }
  auto it = std::find_if(points.begin(), points.end(),
                         [&x](const auto& p) { return p.first > x; });
  if (it == points.begin()) {
    return points.front().second;
  }
  if (it == points.end()) {
    return points.back().second;
  }
  auto prev = it - 1;
  auto x1 = prev->first;
  auto x2 = it->first;
  auto y1 = prev->second;
  auto y2 = it->second;
  return ((x - x1) / (x2 - x1)) * (y2 - y1) + y1;
}

template <typename In, typename Out>
void from_json(const nlohmann::json& j, LinearInterpolation<In, Out>& ip) {
  ip.points.resize(j.size());
  for (auto&& [datum, point] : zip(j, ip.points)) {
    datum.at("t").get_to(point.first);
    datum.at("p").get_to(point.second);
  }
}

template <typename In, typename Out>
void to_json(nlohmann::json& j, const LinearInterpolation<In, Out>& ip) {
  j = nlohmann::json{ip.size()};
  for (auto&& [point, datum] : zip(ip.points, j)) {
    datum["t"] = point.first;
    datum["p"] = point.second;
  }
}

// Interpolation

template <typename In, typename Out>
Out interpolate(const Interpolation<In, Out>& ip, const In& x) {
  return std::visit(
      [&x](auto&& interpolation) { return interpolation.interpolate(x); }, ip);
}

}  // namespace loki::math
