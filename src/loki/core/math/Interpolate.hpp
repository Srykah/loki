#pragma once

#include <vector>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/enumMacros.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>

namespace loki::core {
enum class InterpolationType : short {
  NONE = 0,
  LINEAR = 1,
};

template <typename In, typename Out>
struct InterpolationData {
  InterpolationType type;
  std::vector<std::pair<In, Out>> points;

  LOKI_REFLECTION_CLASS_DECLARE(InterpolationData<In, Out>)
};

template <typename In, typename Out>
Out interpolate(const InterpolationData<In, Out>& data, const In& x);

}  // namespace loki::core

LOKI_REFLECTION_ENUM_BEGIN(loki::core::InterpolationType)
LOKI_REFLECTION_ENUMERATOR(loki::core::InterpolationType, NONE)
LOKI_REFLECTION_ENUMERATOR(loki::core::InterpolationType, LINEAR)
LOKI_REFLECTION_ENUM_END()

LOKI_REFLECTION_TEMPLATE_2_CLASS_BEGIN(loki::core::InterpolationData)
LOKI_REFLECTION_TEMPLATE_2_CLASS_FIELD(loki::core::InterpolationData, type)
LOKI_REFLECTION_TEMPLATE_2_CLASS_FIELD(loki::core::InterpolationData, points)
LOKI_REFLECTION_TEMPLATE_2_CLASS_END()

#include "Interpolate.hxx"
