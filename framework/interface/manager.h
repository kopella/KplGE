#pragma once
#include "runtime-module.h"

namespace kplge {
class IManager : public IRuntimeModule {
 public:
  ~IManager() override = default;

  int initialize() override = 0;
  int finalize() override = 0;

  int tick() override = 0;
};
}  // namespace kplge