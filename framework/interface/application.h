#pragma once
#include "runtime-module.h"

namespace kplge {
class IApplication : public IRuntimeModule {
 public:
  erroc initialize() override = 0;
  erroc finalize() override = 0;

  erroc tick() override = 0;
};
}  // namespace kplge