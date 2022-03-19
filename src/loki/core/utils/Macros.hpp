/*!
 * \file Macros.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#define LOKI_CORE_EXPAND(x) x
#define LOKI_CORE_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, macro, ...) \
  macro

#define LOKI_CORE_REPEAT_1(macro, x1) macro(x1)
#define LOKI_CORE_REPEAT_2(macro, x1, x2) macro(x1) macro(x2)
#define LOKI_CORE_REPEAT_3(macro, x1, x2, x3) macro(x1) macro(x2) macro(x3)
#define LOKI_CORE_REPEAT_4(macro, x1, x2, x3, x4) \
  macro(x1) macro(x2) macro(x3) macro(x4)
#define LOKI_CORE_REPEAT_5(macro, x1, x2, x3, x4, x5) \
  macro(x1) macro(x2) macro(x3) macro(x4) macro(x5)
#define LOKI_CORE_REPEAT_6(macro, x1, x2, x3, x4, x5, x6) \
  LOKI_CORE_REPEAT_5(macro, x1, x2, x3, x4, x5) macro(x6)
#define LOKI_CORE_REPEAT_7(macro, x1, x2, x3, x4, x5, x6, x7) \
  LOKI_CORE_REPEAT_6(macro, x1, x2, x3, x4, x5, x6) macro(x7)
#define LOKI_CORE_REPEAT_8(macro, x1, x2, x3, x4, x5, x6, x7, x8) \
  LOKI_CORE_REPEAT_7(macro, x1, x2, x3, x4, x5, x6, x7) macro(x8)
#define LOKI_CORE_REPEAT_9(macro, x1, x2, x3, x4, x5, x6, x7, x8, x9) \
  LOKI_CORE_REPEAT_8(macro, x1, x2, x3, x4, x5, x6, x7, x8) macro(x9)

#define LOKI_CORE_REPEAT(macro, ...)                                           \
  LOKI_CORE_GET_MACRO(                                                         \
      __VA_ARGS__, LOKI_CORE_REPEAT_9, LOKI_CORE_REPEAT_8, LOKI_CORE_REPEAT_7, \
      LOKI_CORE_REPEAT_6, LOKI_CORE_REPEAT_5, LOKI_CORE_REPEAT_4,              \
      LOKI_CORE_REPEAT_3, LOKI_CORE_REPEAT_2, LOKI_CORE_REPEAT_1)              \
  (macro, __VA_ARGS__)
