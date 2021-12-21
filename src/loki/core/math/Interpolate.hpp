/*!
 * \file Interpolate.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <nlohmann/json.hpp>

namespace loki::common {

enum class InterpolationType { NONE = 0, LINEAR = 1, CUBIC = 3 };

NLOHMANN_JSON_SERIALIZE_ENUM(InterpolationType,
                             {
                                 {InterpolationType::NONE, "none"},
                                 {InterpolationType::LINEAR, "linear"},
                                 {InterpolationType::CUBIC, "cubic"},
                             })

template <typename In, typename Out>
class InterpolationBase {
 public:
  virtual ~InterpolationBase() = default;
  virtual Out interpolate(const In& x) const = 0;
  virtual Out operator()(const In& x) const final { return interpolate(x); }
};

template <typename In, typename Out>
class NoneInterpolation : public InterpolationBase<In, Out> {
 public:
  template <typename... Args>
  explicit NoneInterpolation(Args&&... args)
      : points(std::forward<Args>(args)...) {}
  ~NoneInterpolation() override = default;

  Out interpolate(const In& x) const override;

 private:
  std::vector<std::pair<In, Out>> points;
};

template <typename In, typename Out>
class LinearInterpolation : public InterpolationBase<In, Out> {
 public:
  template <typename... Args>
  explicit LinearInterpolation(Args&&... args)
      : points(std::forward<Args>(args)...) {}
  ~LinearInterpolation() = default;

  Out interpolate(const In& x) const override;

 private:
  std::vector<std::pair<In, Out>> points;
};

}  // namespace loki::common

#include "impl/Interpolate.hxx"
