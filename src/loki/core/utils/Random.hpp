/*!
 * \file Random.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <algorithm>
#include <random>

namespace loki::common {

class RandomEngine {
 public:
  explicit RandomEngine(std::mt19937_64::result_type seed) : engine(seed) {}
  explicit RandomEngine(std::seed_seq seed) : engine(seed) {}
  explicit RandomEngine() : RandomEngine(getSeedSeq()) {}

  static std::seed_seq getSeedSeq();

  /// distributions
  [[nodiscard]] int uniformInt(int min, int includedMax) const;
  [[nodiscard]] float uniformReal(float min, float excludedMax) const;
  [[nodiscard]] bool bernoulli(float p) const;
  [[nodiscard]] int binomial(int n, float p) const;
  [[nodiscard]] int negativeBinomial(int n, float p) const;
  [[nodiscard]] int geometric(float p) const;
  [[nodiscard]] int poisson(float mu) const;
  [[nodiscard]] float exponential(float lambda) const;
  [[nodiscard]] float gamma(float alpha, float beta) const;
  [[nodiscard]] float weibull(float k, float lambda) const;
  [[nodiscard]] float extremeValue(float mu, float sigma) const;
  [[nodiscard]] float normal(float mu, float sigma) const;
  [[nodiscard]] float lognormal(float mu, float sigma) const;
  [[nodiscard]] float chi2(float k) const;
  [[nodiscard]] float cauchy(float x0, float gamma) const;
  [[nodiscard]] float fisher(float m, float n) const;
  [[nodiscard]] float student(float k) const;
  [[nodiscard]] int discrete(std::initializer_list<double> weights);
  template <class It>
  [[nodiscard]] int discrete(It weightsBegin, It weightsEnd);
  template <class Range>
  [[nodiscard]] int discrete(const Range& weights);
  template <class ItValues, class ItWeights>
  [[nodiscard]] int piecewiseConstant(ItValues valuesBegin,
                                      ItValues valuesEnd,
                                      ItWeights weightsBegin);
  template <class RangeValues, class RangeWeights>
  [[nodiscard]] int piecewiseConstant(const RangeValues& values,
                                      const RangeWeights& weights);
  template <class ItValues, class ItWeights>
  [[nodiscard]] int piecewiseLinear(ItValues valuesBegin,
                                    ItValues valuesEnd,
                                    ItWeights weightsBegin);
  template <class RangeValues, class RangeWeights>
  [[nodiscard]] int piecewiseLinear(const RangeValues& values,
                                    const RangeWeights& weights);

  /// algorithms
  template <class It>
  void shuffle(It begin, It end);
  template <class Range>
  void shuffle(Range& range);
  template <class ItIn, class ItOut>
  void sample(ItIn inBegin, ItIn inEnd, ItOut outBegin, std::size_t count);
  template <class RangeIn, class RangeOut>
  void sample(const RangeIn& rangeIn, RangeOut& rangeOut);

 private:
  std::mt19937_64 engine;
};

}  // namespace loki::common

#include "impl/Random.hxx"
