#pragma once
#include "spdlog/spdlog.h"

enum Level { info, debug, warn, error, critical };

template <typename... Args>
inline void log_to_console(enum Level level, Args&&... args) {
  switch (level) {
    case info:
      spdlog::info(std::forward<Args>(args)...);
      break;
    case debug:
      spdlog::debug(std::forward<Args>(args)...);
      break;
    case warn:
      spdlog::warn(std::forward<Args>(args)...);
      break;
    case error:
      spdlog::error(std::forward<Args>(args)...);
      break;
    case critical:
      spdlog::critical(std::forward<Args>(args)...);
      break;
  }
}