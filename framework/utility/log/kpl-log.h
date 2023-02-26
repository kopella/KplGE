#pragma once
#include <cstdlib>
#include <cstdarg>
#include <cstdio>

#include "kpl-config.h"
#include "constants.h"

#ifdef KPL_DEBUG
#define runtime_info runtime_info_toc
#define debug_info debug_info_toc
#else
#define runtime_info runtime_info_tof
#define debug_info debug_info_tof
#endif

inline void runtime_info_toc(const char* format, ...) {
  printf(
      "["
      "\e[0;32m"
      "RUNTIME INFO"
      "\e[0m"
      "]: ");

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

inline void debug_info_toc(const char* format, ...) {
  printf(
      "["
      "\e[0;33m"
      "DEBUG INFO"
      "\e[0m"
      "]: ");

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}