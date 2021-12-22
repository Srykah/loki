/*!
 * \file Random.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include "Random.hpp"
#include <chrono>

namespace loki::common {

std::seed_seq common::RandomEngine::getSeedSeq() {
  std::mt19937_64::result_type seeds[std::mt19937_64::state_size];
  seeds[0] = std::chrono::high_resolution_clock::now()
                 .time_since_epoch()
                 .count();  // fallback in case random_device is deterministic
  std::random_device device;
  std::uniform_int_distribution<typename std::mt19937_64::result_type> dist;
  std::generate(std::begin(seeds) + 1, std::end(seeds),
                [&] { return dist(device); });
  return {std::begin(seeds), std::end(seeds)};
}

int RandomEngine::uniformInt(int min, int includedMax) const {
  return std::uniform_int_distribution{min, includedMax}(engine);
}

float RandomEngine::uniformReal(float min, float excludedMax) const {
  return std::uniform_real_distribution{min, excludedMax}(engine);
}

bool RandomEngine::bernoulli(float p) const {
  return std::bernoulli_distribution{p}(engine);
}

int RandomEngine::binomial(int n, float p) const {
  return std::binomial_distribution{n, p}(engine);
}

int RandomEngine::negativeBinomial(int n, float p) const {
  return std::negative_binomial_distribution{n, p}(engine);
}

int RandomEngine::geometric(float p) const {
  return std::geometric_distribution{p}(engine);
}

int RandomEngine::poisson(float mu) const {
  return std::geometric_distribution{mu}(engine);
}
float RandomEngine::exponential(float lambda) const {
  return std::exponential_distribution{lambda}(engine);
}

float RandomEngine::gamma(float alpha, float beta) const {
  return std::gamma_distribution{alpha, beta}(engine);
}

float RandomEngine::weibull(float k, float lambda) const {
  return std::weibull_distribution{k, lambda}(engine);
}

float RandomEngine::extremeValue(float mu, float sigma) const {
  return std::extreme_value_distribution{mu, sigma}(engine);
}

float RandomEngine::normal(float mu, float sigma) const {
  return std::normal_distribution{mu, sigma}(engine);
}

float RandomEngine::lognormal(float mu, float sigma) const {
  return std::lognormal_distribution{mu, sigma}(engine);
}

float RandomEngine::chi2(float k) const {
  return std::chi_squared_distribution{k}(engine);
}

float RandomEngine::cauchy(float x0, float gamma) const {
  return std::cauchy_distribution{x0, gamma}(engine);
}

float RandomEngine::fisher(float m, float n) const {
  return std::fisher_f_distribution{m, n}(engine);
}

float RandomEngine::student(float n) const {
  return std::student_t_distribution{n}(engine);
}

int RandomEngine::discrete(std::initializer_list<double> weights) {
  return std::discrete_distribution{weights}(engine);
}

}  // namespace loki::common
