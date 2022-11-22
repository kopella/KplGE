#pragma once
#include "kpl-config.h"

namespace kplge {
class IRuntimeModule {
 public:
  virtual ~IRuntimeModule() = default;

  virtual erroc initialize() = 0;
  virtual erroc finalize() = 0;

  virtual erroc tick() = 0;
};
}  // namespace kplge