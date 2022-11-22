#pragma once
#include "runtime-module.h"

namespace kplge {
class IManager : public IRuntimeModule {
 public:
  ~IManager() override = default;

  erroc initialize() override = 0;
  erroc finalize() override = 0;

  erroc tick() override = 0;
};
}  // namespace kplge