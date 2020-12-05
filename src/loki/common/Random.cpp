/*!
 * \file Random.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */

#include <random>

namespace {

std::mt19937_64 engine { std::random_device {}() };

}

namespace loki::common {

bool roll0to100(int thres) {
  return std::bernoulli_distribution { thres / 100.0 }(engine);
}

}