#pragma once
#include <cstdlib>
#include <cstdarg>
#include <cstdio>

#include "config.h"

#ifdef KPL_DEBUG
#define runtime_info runtime_info_toc
#define test_info test_info_toc
#else
#define runtime_info runtime_info_tof
#endif

inline void runtime_info_toc(const char* module, const char* format, ...) {
  printf(
      "["
      "\e[0;32m"
      "INFO"
      "\e[0m"
      "]");
  printf(
      "["
      "\e[0;32m"
      "%s"
      "\e[0m"
      "]: ",
      module);

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

inline void test_info_toc(const char* module, const char* format, ...) {
  printf(
      "["
      "\e[0;33m"
      "TEST"
      "\e[0m"
      "]");
  printf(
      "["
      "\e[0;33m"
      "%s"
      "\e[0m"
      "]: ",
      module);

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}