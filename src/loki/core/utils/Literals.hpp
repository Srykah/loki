#pragma once

#include "Mixins.hpp"

#define LOKI_CREATE_CUSTOM_INTEGER_LITERAL(LiteralName, Suffix, ...)         \
  class LiteralName : loki::core::MixinCombine<LiteralName, ##__VA_ARGS__> { \
   public:                                                                   \
    explicit constexpr LiteralName(long long int _t) : t(_t) {}              \
    [[nodiscard]] constexpr long long int get() const { return t; }          \
                                                                             \
   private:                                                                  \
    long long int t;                                                         \
  };                                                                         \
  constexpr LiteralName operator"" Suffix(unsigned long long int x) {        \
    return LiteralName{static_cast<long long int>(x)};                       \
  }
