#pragma once
#include "runtime-module.h"

namespace kplge {
class IManager : public IRuntimeModule {
 public:
  ~IManager() override = default;

  erroc Initialize() override = 0;
  erroc Finalize() override = 0;

  erroc Tick() override = 0;
};
}  // namespace kplge