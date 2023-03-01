#pragma once
#include "runtime-module.h"

namespace kplge {
class IApplication : public IRuntimeModule {
 public:
  ~IApplication() override = default;

  erroc Initialize() override = 0;
  erroc Finalize() override = 0;
  erroc Tick() override = 0;
};
}  // namespace kplge