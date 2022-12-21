#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

inline void info_to_console(const char* msg) {
  printf(
      "["
      "\e[0;32m"
      "info"
      "\e[0m"
      "]"
      ": %s"
      "\n",
      msg);
}

inline void error_to_console(const char* msg) {
  printf(
      "["
      "\e[0;31m"
      "error"
      "\e[0m"
      "]"
      ": %s"
      "\n",
      msg);
  exit(1);
}