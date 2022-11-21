#pragma once
#include "manager.h"

namespace kplge {
class MemManager : public IManager {
 public:
  int initialize() override = 0;
  int finalize() override = 0;

  int tick() override = 0;
};
}  // namespace kplge