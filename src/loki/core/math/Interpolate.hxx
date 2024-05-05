#include <ranges>
#include <span>

namespace loki::core {

template <typename In, typename Out>
Out interpolateNone(const std::vector<std::pair<In, Out>>& points, const In& x) {
  assert(!points.empty());
  auto reverseView = points | std::views::reverse;
  auto it = std::ranges::find_if(reverseView, [&x](const auto& p) { return p.first <= x; });
  if (it == reverseView.end()) {
    return points[0].second;
  }
  return it->second;
}

template <typename In, typename Out>
Out interpolateLinear(const std::vector<std::pair<In, Out>>& points, const In& x) {
  assert(!points.empty());
  auto it = std::ranges::find_if(points, [&x](const auto& p) { return p.first > x; });
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
Out interpolate(const InterpolationData<In, Out>& data, const In& x) {
  assert(!data.points.empty());
  switch (data.type) {
    case InterpolationType::NONE:
      return interpolateNone(data.points, x);
    case InterpolationType::LINEAR:
      return interpolateLinear(data.points, x);
    default:
      throw std::runtime_error("invalid interpolation type!");
  }
}

}  // namespace loki::core
