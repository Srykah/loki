#pragma once

#include <variant>

#include <nlohmann/json.hpp>

#include <loki/core/json/Variant.hpp>

namespace loki::core {

//
#if 0
enum class InterpolationType {
  NONE = 0,
  LINEAR = 1,
  CUBIC = 3  ///< not implemented yet
};

NLOHMANN_JSON_SERIALIZE_ENUM(InterpolationType,
                             {
                                 {InterpolationType::NONE, "none"},
                                 {InterpolationType::LINEAR, "linear"},
                                 {InterpolationType::CUBIC, "cubic"},
                             })
#endif

/// Order 0 interpolation
template <typename In, typename Out>
class NoneInterpolation;
template <typename In, typename Out>
void from_json(const nlohmann::json& j, NoneInterpolation<In, Out>& ip);
template <typename In, typename Out>
void to_json(nlohmann::json& j, const NoneInterpolation<In, Out>& ip);

template <typename In, typename Out>
class NoneInterpolation {
 public:
  NoneInterpolation() = default;
  explicit NoneInterpolation(std::vector<std::pair<In, Out>>&& points)
      : points(std::move(points)) {}

  Out interpolate(const In& x) const;

 private:
  std::vector<std::pair<In, Out>> points;

  friend void from_json<>(const nlohmann::json& j, NoneInterpolation& ip);
  friend void to_json<>(nlohmann::json& j, const NoneInterpolation& ip);
};

/// Order 1 interpolation
template <typename In, typename Out>
class LinearInterpolation;
template <typename In, typename Out>
void from_json(const nlohmann::json& j, LinearInterpolation<In, Out>& ip);
template <typename In, typename Out>
void to_json(nlohmann::json& j, const LinearInterpolation<In, Out>& ip);

template <typename In, typename Out>
class LinearInterpolation {
 public:
  LinearInterpolation() = default;
  explicit LinearInterpolation(std::vector<std::pair<In, Out>>&& points)
      : points(std::move(points)) {}
  ~LinearInterpolation() = default;

  Out interpolate(const In& x) const;

 private:
  std::vector<std::pair<In, Out>> points;

  friend void from_json<>(const nlohmann::json& j, LinearInterpolation& ip);
  friend void to_json<>(nlohmann::json& j, const LinearInterpolation& ip);
};

/// Common type for all interpolations
template <typename In, typename Out>
using Interpolation =
    std::variant<NoneInterpolation<In, Out>, LinearInterpolation<In, Out>>;

template <typename In, typename Out>
Out interpolate(const Interpolation<In, Out>& ip, const In& x);

}  // namespace loki::core

#include "Interpolate.hxx"
