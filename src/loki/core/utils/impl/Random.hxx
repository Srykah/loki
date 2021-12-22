/*!
 * \file Random.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::common {

template <class It>
int RandomEngine::discrete(It weightsBegin, It weightsEnd) {
  return std::discrete_distribution{weightsBegin, weightsEnd}(engine);
}

template <class Range>
[[nodiscard]] int RandomEngine::discrete(const Range& weights) {
  return std::discrete_distribution{std::begin(weights),
                                    std::end(weights)}(engine);
}

template <class ItValues, class ItWeights>
int RandomEngine::piecewiseConstant(ItValues valuesBegin,
                                    ItValues valuesEnd,
                                    ItWeights weightsBegin) {
  return std::piecewise_constant_distribution{valuesBegin, valuesEnd,
                                              weightsBegin}(engine);
}

template <class RangeValues, class RangeWeights>
[[nodiscard]] int RandomEngine::piecewiseConstant(const RangeValues& values,
                                                  const RangeWeights& weights) {
  return std::piecewise_constant_distribution{
      std::begin(values), std::end(values), std::begin(weights)}(engine);
}

template <class ItValues, class ItWeights>
int RandomEngine::piecewiseLinear(ItValues valuesBegin,
                                  ItValues valuesEnd,
                                  ItWeights weightsBegin) {
  return std::piecewise_linear_distribution{valuesBegin, valuesEnd,
                                            weightsBegin}(engine);
}

template <class RangeValues, class RangeWeights>
[[nodiscard]] int RandomEngine::piecewiseLinear(const RangeValues& values,
                                                const RangeWeights& weights) {
  return std::piecewise_linear_distribution{
      std::begin(values), std::end(values), std::begin(weights)}(engine);
}

template <class It>
void RandomEngine::shuffle(It begin, It end) {
  std::shuffle(begin, end, engine);
}

template <class Range>
void RandomEngine::shuffle(Range& range) {
  std::shuffle(std::begin(range), std::end(range), engine);
}

template <class ItIn, class ItOut>
void RandomEngine::sample(ItIn inBegin,
                          ItIn inEnd,
                          ItOut outBegin,
                          std::size_t count) {
  std::sample(inBegin, inEnd, outBegin, count, engine);
}

template <class RangeIn, class RangeOut>
void RandomEngine::sample(const RangeIn& rangeIn, RangeOut& rangeOut) {
  return std::sample(std::begin(rangeIn), std::end(rangeIn),
                     std::begin(rangeOut), std::size(rangeOut), engine);
}

}  // namespace loki::common
