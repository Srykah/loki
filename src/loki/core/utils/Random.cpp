#include "Random.hpp"
#include <random>

namespace {

std::mt19937_64 engine{std::random_device{}()};

}

namespace loki::core {

bool roll0to100(int thres) {
  return std::bernoulli_distribution{thres / 100.0}(engine);
}

}  // namespace loki::core