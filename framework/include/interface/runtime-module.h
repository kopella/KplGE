#pragma once

#include "../config.h"
#include "../constants.h"

namespace kplge {
class IRuntimeModule {
 public:
  virtual ~IRuntimeModule() = default;

  virtual erroc Initialize() = 0;
  virtual erroc Finalize() = 0;

  virtual erroc Tick() = 0;
};
}  // namespace kplge